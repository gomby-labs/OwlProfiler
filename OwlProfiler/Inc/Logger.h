#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <windows.h>
#include <string>
#include <sstream>
#include "corprof.h"

using namespace std;

#define CODEFILE (LPWSTR)_bstr_t(__FILE__)
#define CODELINE (LPWSTR)_bstr_t(__LINE__)


namespace OwlProfiler
{
	class Logger
	{
	public:
		Logger();
		~Logger();

		static bool initialize();
		static void terminate();

		static void info(const wchar_t * msg);
	};
}

#endif //__LOGGER_H__ 
