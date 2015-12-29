#include "stdafx.h"
#include "Logger.h"
#include "CorProfilerInfoManager.h"
#include <comutil.h>

using namespace OwlProfiler;


ICorProfilerInfo3Ptr CorProfilerInfoManager::mCorProfilerInfo;


//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
CorProfilerInfoManager::CorProfilerInfoManager()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
CorProfilerInfoManager::~CorProfilerInfoManager()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
void CorProfilerInfoManager::initialize(ICorProfilerInfo3Ptr corProfilerInfo)
{ 
	mCorProfilerInfo = corProfilerInfo;
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
void CorProfilerInfoManager::terminate()
{
	mCorProfilerInfo = NULL;
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
ModuleID CorProfilerInfoManager::GetModuleIDAndName(AssemblyID assemblyID, std::wstring& assemblyName)
{
	wchar_t			assemblyNameStr[128];
	ULONG				assemblyNameSize = 0;
	AppDomainID appDomainId;
	ModuleID		moduleId;

	HRESULT hr = mCorProfilerInfo->GetAssemblyInfo(	assemblyID,
																									128,
																									&assemblyNameSize,
																									assemblyNameStr,
																									&appDomainId,
																									&moduleId);

	assemblyNameStr[assemblyNameSize] = L'\0';
	assemblyName = assemblyNameStr;

	return moduleId;
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
IMetaDataAssemblyImport * CorProfilerInfoManager::GetModuleMetaData(ModuleID moduleId)
{
	IMetaDataAssemblyImport * metaDataAssemblyImport = NULL;

	HRESULT hr = mCorProfilerInfo->GetModuleMetaData(
														moduleId,
														ofRead,
														IID_IMetaDataAssemblyImport,
														(IUnknown **)&metaDataAssemblyImport);

	if (FAILED(hr))
	{
		metaDataAssemblyImport = NULL;
	}

	return metaDataAssemblyImport;
}


