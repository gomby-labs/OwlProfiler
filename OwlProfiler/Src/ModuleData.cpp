#include "stdafx.h"
#include "Logger.h"
#include "ModuleData.h"
#include "CorProfilerInfoManager.h"

using namespace OwlProfiler;


//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
ModuleData::ModuleData(ModuleID moduleId):
								mMetaDataAssemblyImport(NULL),
								mModuleId(moduleId)
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
ModuleData::~ModuleData()
{
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
bool ModuleData::Initialize()
{
	mMetaDataAssemblyImport = CorProfilerInfoManager::GetModuleMetaData(mModuleId);

	if (mMetaDataAssemblyImport)
		return TRUE;

	return FALSE;
}

//-------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------
void ModuleData::Terminate()
{
	mMetaDataAssemblyImport = NULL;
}





