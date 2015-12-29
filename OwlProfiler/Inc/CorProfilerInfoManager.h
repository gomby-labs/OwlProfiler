#ifndef __CORPROFILERINFOMANAGER_H__
#define __CORPROFILERINFOMANAGER_H__

#include <windows.h>
#include <string>
#include <sstream>
#include "corprof.h"

_COM_SMARTPTR_TYPEDEF(ICorProfilerInfo3, __uuidof(ICorProfilerInfo3));

namespace OwlProfiler
{
	class CorProfilerInfoManager
	{
	public:
		CorProfilerInfoManager();
		~CorProfilerInfoManager();

		static void initialize(ICorProfilerInfo3Ptr corProfilerInfo);
		static void terminate();

		static ModuleID GetModuleIDAndName(AssemblyID assemblyID, std::wstring& assemblyName);

		static IMetaDataAssemblyImport * GetModuleMetaData(ModuleID moduleId);

	private:
		static ICorProfilerInfo3Ptr	mCorProfilerInfo;
	};
}

#endif //__CORPROFILERINFOMANAGER_H__ 
