#include "stdafx.h"
#include "resource.h"
#include <memory>

// The module attribute causes DllMain, DllRegisterServer and DllUnregisterServer to be automatically implemented for you
[ module(dll, uuid = "{F7A8AF12-A2E9-322A-5415-A12B03B67BCA}", 
		 name = "OwlProfiler", 
		 helpstring = "OwlProfiler 1.0 Type Library",
		 resource_name = "IDR_OWLPROFILER") ]
class COwlProfilerModule
{
public:

	// Override CAtlDllModuleT members
	BOOL WINAPI DllMain(DWORD dwReason, LPVOID lpReserved) throw()
	{
		BOOL result = __super::DllMain(dwReason,lpReserved);

		if(dwReason == DLL_PROCESS_DETACH)
		{
		}
		else if(dwReason == DLL_PROCESS_ATTACH)
		{
		}  
		return result;    
	}
};


