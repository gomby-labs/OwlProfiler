#include "stdafx.h"
#include "Logger.h"
#include "ProfilerImpl.h"
#include <comutil.h>


using namespace OwlProfiler;

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
Logger::Logger()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
Logger::~Logger()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
bool Logger::initialize()
{ 
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
void Logger::terminate()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
void Logger::info(const wchar_t * msg)
{
	OutputDebugString(msg);
}




