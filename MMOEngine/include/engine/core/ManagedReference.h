/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef MANAGEDREFERENCE_H_
#define MANAGEDREFERENCE_H_

#include "system/lang.h"

#include "engine/stm/TransactionalMemoryManager.h"

#include "ManagedObject.h"

#include "engine/orb/DistributedObjectBroker.h"

namespace engine {
  namespace core {

	template<class O> class ManagedReference : public Reference<O> {
		TransactionalObjectHeader<O>* header;

	public:
		ManagedReference() : Reference<O>() {
			header = NULL;
		}

		ManagedReference(const ManagedReference& ref) : Reference<O>(ref) {
			header = ref.header;
		}

		ManagedReference(O* obj) : Reference<O>(obj) {
			header = new TransactionalObjectHeader<O>(obj);
		}

		~ManagedReference() {
			if (header != NULL) {
				delete header;
				header = NULL;
			}
		}

		ManagedReference& operator=(const ManagedReference& ref) {
			if (this == &ref)
				return *this;

			Reference<O>::updateObject(ref.object);

			updateHeader(ref.header);

			return *this;
		}

		O* operator=(O* obj) {
			Reference<O>::updateObject(obj);

			updateHeader(obj);

			return obj;
		}

		O* operator->() const {
			return getForUpdate();
		}

		operator O*() const {
			return getForUpdate();
		}

		O* get() const {
			if (header != NULL)
				return header->get();
			else
				return NULL;
		}

		O* getForUpdate() const {
			if (header != NULL)
				return header->getForUpdate();
			else
				return NULL;
		}

		int compareTo(const ManagedReference& ref) const {
			if (Reference<O>::object->_getObjectID() < ref.Reference<O>::object->_getObjectID())
				return 1;
			else if (Reference<O>::object->_getObjectID() > ref.Reference<O>::object->_getObjectID())
				return -1;
			else
				return 0;
		}

		bool toString(String& str) {
			if (Reference<O>::get() != NULL)
				str = String::valueOf((Reference<O>::get())->_getObjectID());
			else
				str = String::valueOf(0);

			return true;
		}

		bool parseFromString(const String& str, int version = 0) {
			DistributedObject* obj = DistributedObjectBroker::instance()->lookUp(UnsignedLong::valueOf(str));

			Reference<O>::updateObject((O*) obj);

			if (obj == NULL)
				return false;

			return true;
		}

		bool toBinaryStream(ObjectOutputStream* stream) {
			O* object = Reference<O>::get();

			if (object != NULL)
				stream->writeLong(object->_getObjectID());
			else
				stream->writeLong(0);

			return true;
		}

		bool parseFromBinaryStream(ObjectInputStream* stream) {
			uint64 oid = stream->readLong();

			O* obj = (O*) DistributedObjectBroker::instance()->lookUp(oid);
			*this = obj;

			if (obj == NULL)
				return false;

			return true;
		}

	protected:
		void updateHeader(O* obj) {
			if (header != NULL)
				delete header;

			header = new TransactionalObjectHeader<O>(obj);
		}

		void updateHeader(TransactionalObjectHeader<O>* hdr) {
			if (header != NULL)
				delete header;

			header = new TransactionalObjectHeader<O>(hdr);
		}
};

  } // namespace core
} // namespace engine

using namespace engine::core;

#endif /*MANAGEDREFERENCE_H_*/
