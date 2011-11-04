/*
 *	engine/core/util/ManagedVector.cpp generated by engine3 IDL compiler 0.60
 */

#include "ManagedVector.h"


// Imported class dependencies

#include "engine/core/ManagedObject.h"

#include "engine/core/ObjectUpdateToDatabaseTask.h"

#include "system/io/ObjectInputStream.h"

#include "system/io/ObjectOutputStream.h"

#include "system/thread/Lockable.h"

/*
 *	ManagedVectorStub
 */

ManagedVector::ManagedVector(DummyConstructorParameter* param) : ManagedObject(param) {
}

ManagedVector::~ManagedVector() {
}


bool ManagedVector::_isCurrentVersion(ManagedObjectImplementation* servant) {

	return header->isCurrentVersion(servant);
}


DistributedObjectServant* ManagedVector::_getImplementation() {

	_updated = true;
	return dynamic_cast<DistributedObjectServant*>(header->getForUpdate());}

void ManagedVector::_setImplementation(DistributedObjectServant* servant) {
	header = new TransactionalObjectHeader<ManagedObjectImplementation*>(dynamic_cast<ManagedObjectImplementation*>(servant));
}

/*
 *	ManagedVectorImplementation
 */

ManagedVectorImplementation::ManagedVectorImplementation() : ManagedObjectImplementation() {
	_initializeImplementation();
}

ManagedVectorImplementation::ManagedVectorImplementation(DummyConstructorParameter* param) : ManagedObjectImplementation(param) {
	_initializeImplementation();
}


ManagedVectorImplementation::~ManagedVectorImplementation() {
}


void ManagedVectorImplementation::finalize() {
}

void ManagedVectorImplementation::_initializeImplementation() {
	_setClassHelper(ManagedVectorHelper::instance());

	_this = NULL;

	_serializationHelperMethod();
}

void ManagedVectorImplementation::_setStub(DistributedObjectStub* stub) {
	_this = static_cast<ManagedVector*>(stub);
	ManagedObjectImplementation::_setStub(stub);
}

DistributedObjectStub* ManagedVectorImplementation::_getStub() {
	return _this;
}

ManagedVectorImplementation::operator const ManagedVector*() {
	return _this;
}

Object* ManagedVectorImplementation::clone() {
	return ObjectCloner<ManagedVectorImplementation>::clone(this);
}


Object* ManagedVectorImplementation::clone(void* object) {
	return TransactionalObjectCloner<ManagedVectorImplementation>::clone(this);
}


void ManagedVectorImplementation::free() {
	TransactionalMemoryManager::instance()->destroy(this);
}


void ManagedVectorImplementation::lock(bool doLock) {
}

void ManagedVectorImplementation::lock(ManagedObject* obj) {
}

void ManagedVectorImplementation::rlock(bool doLock) {
}

void ManagedVectorImplementation::wlock(bool doLock) {
}

void ManagedVectorImplementation::wlock(ManagedObject* obj) {
}

void ManagedVectorImplementation::unlock(bool doLock) {
}

void ManagedVectorImplementation::runlock(bool doLock) {
}

void ManagedVectorImplementation::_serializationHelperMethod() {
	ManagedObjectImplementation::_serializationHelperMethod();

	_setClassName("ManagedVector");

}

void ManagedVectorImplementation::readObject(ObjectInputStream* stream) {
	uint16 _varCount = stream->readShort();
	for (int i = 0; i < _varCount; ++i) {
		String _name;
		_name.parseFromBinaryStream(stream);

		uint16 _varSize = stream->readShort();

		int _currentOffset = stream->getOffset();

		if(ManagedVectorImplementation::readObjectMember(stream, _name)) {
		}

		stream->setOffset(_currentOffset + _varSize);
	}

	initializeTransientMembers();
}

bool ManagedVectorImplementation::readObjectMember(ObjectInputStream* stream, const String& _name) {
	if (ManagedObjectImplementation::readObjectMember(stream, _name))
		return true;


	return false;
}

void ManagedVectorImplementation::writeObject(ObjectOutputStream* stream) {
	int _currentOffset = stream->getOffset();
	stream->writeShort(0);
	int _varCount = ManagedVectorImplementation::writeObjectMembers(stream);
	stream->writeShort(_currentOffset, _varCount);
}

int ManagedVectorImplementation::writeObjectMembers(ObjectOutputStream* stream) {
	String _name;
	int _offset;
	uint16 _totalSize;

	return 0 + ManagedObjectImplementation::writeObjectMembers(stream);
}

/*
 *	ManagedVectorAdapter
 */

ManagedVectorAdapter::ManagedVectorAdapter(ManagedVectorImplementation* obj) : ManagedObjectAdapter(obj) {
}

Packet* ManagedVectorAdapter::invokeMethod(uint32 methid, DistributedMethod* inv) {
	Packet* resp = new MethodReturnMessage(0);

	switch (methid) {
	default:
		return NULL;
	}

	return resp;
}

/*
 *	ManagedVectorHelper
 */

ManagedVectorHelper* ManagedVectorHelper::staticInitializer = ManagedVectorHelper::instance();

ManagedVectorHelper::ManagedVectorHelper() {
	className = "ManagedVector";

	Core::getObjectBroker()->registerClass(className, this);
}

void ManagedVectorHelper::finalizeHelper() {
	ManagedVectorHelper::finalize();
}

DistributedObject* ManagedVectorHelper::instantiateObject() {
	return new ManagedVector(DummyConstructorParameter::instance());
}

DistributedObjectServant* ManagedVectorHelper::instantiateServant() {
	return new ManagedVectorImplementation(DummyConstructorParameter::instance());
}

DistributedObjectAdapter* ManagedVectorHelper::createAdapter(DistributedObjectStub* obj) {
	DistributedObjectAdapter* adapter = new ManagedVectorAdapter(static_cast<ManagedVectorImplementation*>(obj->_getImplementation()));

	obj->_setClassName(className);
	obj->_setClassHelper(this);

	adapter->setStub(obj);

	return adapter;
}

