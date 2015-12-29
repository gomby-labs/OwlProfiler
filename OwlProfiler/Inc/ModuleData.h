#ifndef __MODULEDATA_H__
#define __MODULEDATA_H__

#include <windows.h>
#include <string>
#include <sstream>
#include "corprof.h"

_COM_SMARTPTR_TYPEDEF(IMetaDataAssemblyImport,IID_IMetaDataAssemblyImport);

namespace OwlProfiler
{
	class ModuleData
	{
	public:
		ModuleData(ModuleID moduleId);
		~ModuleData();

		bool Initialize();
		void Terminate();

	private:
		IMetaDataAssemblyImportPtr	mMetaDataAssemblyImport;
		ModuleID mModuleId;
	};
}

#endif //__MODULEDATA_H__ 
