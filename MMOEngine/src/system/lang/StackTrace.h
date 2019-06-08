/*
** Copyright (C) 2007-2019 SWGEmu
** See file COPYING for copying conditions.
*/

#ifndef STACKTRACE_H_
#define STACKTRACE_H_

#include "system/platform.h"
#include "system/lang/String.h"

#ifdef PLATFORM_UNIX
	#include <execinfo.h>
#elif defined PLATFORM_CYGWIN
	extern "C" void cygwin_stackdump(void);
#endif

#ifdef TRACE_REFERENCING
	#define LINE_TRACING
#endif

/*#ifdef PLATFORM_MAC
	#undef LINE_TRACING
#endif*/

namespace sys {
  namespace lang {

	class StackTrace {
		void* symbols[25];

		int count;

		static String binaryName;

	public:
		StackTrace();
		StackTrace(const StackTrace& c);

		StackTrace& operator=(const StackTrace& c);

		~StackTrace();

		void print() const ;

		void getStackTrace(String& trace) const;

		static void printStackTrace();

		bool equals(const StackTrace& trace) const;

		static void setBinaryName(const String& name) {
			binaryName = name;
		}

		static const String& getBinaryName() {
			return binaryName;
		}
	};

  } // namespace lang
} // namespace sys

using namespace sys::lang;

#endif /*STACKTRACE_H_*/
