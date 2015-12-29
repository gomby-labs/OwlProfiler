#include "stdafx.h"
#include <Psapi.h>
#include "ProfilerImpl.h"
#include <algorithm>
#include "Logger.h"
#include "CorProfilerInfoManager.h"

namespace OwlProfiler
{
	CProfilerImpl::CProfilerImpl():
												mIsEnabled(true)
{
}

CProfilerImpl::~CProfilerImpl()
{
}

//
// Methods from ICoreProfilerCallback
//
HRESULT STDMETHODCALLTYPE CProfilerImpl::Initialize(IUnknown *pICorProfilerInfoUnk)
{
  try
  {
 		ICorProfilerInfo3 * corProfilerInfo		= NULL;
		corProfilerInfo = (ICorProfilerInfo3*)pICorProfilerInfoUnk;

		CorProfilerInfoManager::initialize(corProfilerInfo);

		DWORD events = COR_PRF_MONITOR_CLASS_LOADS 
								| COR_PRF_MONITOR_ASSEMBLY_LOADS 
								| COR_PRF_MONITOR_MODULE_LOADS
								| COR_PRF_MONITOR_THREADS
								| COR_PRF_USE_PROFILE_IMAGES
							 ;

		events = events | COR_PRF_DISABLE_INLINING;

		/* all events: 
					COR_PRF_MONITOR_CLASS_LOADS
				| COR_PRF_MONITOR_MODULE_LOADS
				| COR_PRF_MONITOR_ASSEMBLY_LOADS
				| COR_PRF_MONITOR_APPDOMAIN_LOADS
				| COR_PRF_MONITOR_JIT_COMPILATION
				| COR_PRF_MONITOR_EXCEPTIONS
				| COR_PRF_MONITOR_THREADS
				| COR_PRF_MONITOR_CODE_TRANSITIONS
				| COR_PRF_MONITOR_ENTERLEAVE
				| COR_PRF_MONITOR_CACHE_SEARCHES
				| COR_PRF_DISABLE_INLINING
		*/
		
		corProfilerInfo->SetEventMask(events);
  }
  catch(...)
  {
		mIsEnabled = false;
  }

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::Shutdown()
{
	return S_OK;
}

// APPLICATION DOMAIN EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::AppDomainCreationStarted( /* [in] */ AppDomainID appDomainId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::AppDomainCreationFinished(/* [in] */ AppDomainID appDomainId,
																  /* [in] */ HRESULT hrStatus)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::AppDomainShutdownStarted( /* [in] */ AppDomainID appDomainId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::AppDomainShutdownFinished( /* [in] */ AppDomainID appDomainId,
																   /* [in] */ HRESULT hrStatus)
{
	return E_NOTIMPL;
}


// ASSEMBLY EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::AssemblyLoadStarted(/* [in] */ AssemblyID assemblyId)
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::AssemblyLoadFinished(/* [in] */ AssemblyID assemblyId,
															 /* [in] */ HRESULT hrStatus)
{
	if(!mIsEnabled)
		return S_OK;

	std::wstring logMsg;

	// Assembly may have several modules
	std::wstring assemblyName;
	ModuleID moduleId = CorProfilerInfoManager::GetModuleIDAndName(assemblyId, assemblyName);

	logMsg = L"CProfilerImpl::AssemblyLoadFinished - assembly: ";
	logMsg+= assemblyName;
	Logger::info(logMsg.c_str());

	ModuleData * moduleData = new ModuleData(moduleId);
	moduleData->Initialize();
	mModuleDataMap[moduleId] = moduleData;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::AssemblyUnloadStarted( /* [in] */ AssemblyID assemblyId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::AssemblyUnloadFinished(/* [in] */ AssemblyID assemblyId,
															   /* [in] */ HRESULT hrStatus)
{
	return E_NOTIMPL;
}


// MODULE EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::ModuleLoadStarted( /* [in] */ ModuleID moduleId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ModuleLoadFinished( /* [in] */ ModuleID moduleId,
															/* [in] */ HRESULT hrStatus)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ModuleUnloadStarted( /* [in] */ ModuleID moduleId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ModuleUnloadFinished( /* [in] */ ModuleID moduleId,
															  /* [in] */ HRESULT hrStatus)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ModuleAttachedToAssembly(/* [in] */ ModuleID moduleID,
																 /* [in] */ AssemblyID assemblyID)
{
	return S_OK;
}


// CLASS EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::ClassLoadStarted(/* [in] */ ClassID classId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ClassLoadFinished(/* [in] */ ClassID classId,
														  /* [in] */ HRESULT hrStatus)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ClassUnloadStarted(/* [in] */ ClassID classId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ClassUnloadFinished(/* [in] */ ClassID classId,
															/* [in] */ HRESULT hrStatus)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::FunctionUnloadStarted(/* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


// JIT EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::JITCompilationStarted(/* [in] */ FunctionID functionID,
															  /* [in] */ BOOL fIsSafeToBlock)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::JITCompilationFinished( /* [in] */ FunctionID functionId,
																/* [in] */ HRESULT hrStatus,
																/* [in] */ BOOL fIsSafeToBlock)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::JITCachedFunctionSearchStarted( /* [in] */ FunctionID functionId,
																		/* [out] */ BOOL *pbUseCachedFunction)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::JITCachedFunctionSearchFinished( /* [in] */ FunctionID functionId,
																		 /* [in] */ COR_PRF_JIT_CACHE result)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::JITFunctionPitched(/* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::JITInlining( /* [in] */ FunctionID callerId,
													 /* [in] */ FunctionID calleeId,
													 /* [out] */ BOOL *pfShouldInline)
{
	return E_NOTIMPL;
}


// THREAD EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::ThreadCreated( /* [in] */ ThreadID threadId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ThreadDestroyed( /* [in] */ ThreadID threadId)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ThreadAssignedToOSThread( /* [in] */ ThreadID managedThreadId,
																  /* [in] */ DWORD osThreadId)
{
	return S_OK;
}


// REMOTING EVENTS - Client-side events
HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingClientInvocationStarted(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingClientSendingMessage( /* [in] */ GUID *pCookie,
																	  /* [in] */ BOOL fIsAsync)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingClientReceivingReply( /* [in] */ GUID *pCookie,
																	  /* [in] */ BOOL fIsAsync)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingClientInvocationFinished(void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingServerReceivingMessage( /* [in] */ GUID *pCookie,
																	    /* [in] */ BOOL fIsAsync)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingServerInvocationStarted(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingServerInvocationReturned(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RemotingServerSendingReply( /* [in] */ GUID *pCookie,
																	/* [in] */ BOOL fIsAsync)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::UnmanagedToManagedTransition( /* [in] */ FunctionID functionId,
																      /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ManagedToUnmanagedTransition( /* [in] */ FunctionID functionId,
													 				 /* [in] */ COR_PRF_TRANSITION_REASON reason)
{
	return E_NOTIMPL;
}


// SUSPENSION EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeSuspendStarted( /* [in] */ COR_PRF_SUSPEND_REASON suspendReason)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeSuspendFinished(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeSuspendAborted(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeResumeStarted(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeResumeFinished(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeThreadSuspended(/* [in] */ ThreadID threadId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RuntimeThreadResumed(/* [in] */ ThreadID threadId)
{
	return E_NOTIMPL;
}


// GC EVENTS
HRESULT STDMETHODCALLTYPE CProfilerImpl::MovedReferences( /* [in] */ ULONG cMovedObjectIDRanges,
													     /* [size_is][in] */ ObjectID oldObjectIDRangeStart[  ],
														 /* [size_is][in] */ ObjectID newObjectIDRangeStart[  ],
														 /* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ObjectAllocated( /* [in] */ ObjectID objectId,
														 /* [in] */ ClassID classId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ObjectsAllocatedByClass( /* [in] */ ULONG cClassCount,
																 /* [size_is][in] */ ClassID classIds[  ],
																 /* [size_is][in] */ ULONG cObjects[  ])
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ObjectReferences( /* [in] */ ObjectID objectId,
														  /* [in] */ ClassID classId,
														  /* [in] */ ULONG cObjectRefs,
														  /* [size_is][in] */ ObjectID objectRefIds[  ])
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::RootReferences( /* [in] */ ULONG cRootRefs,
													    /* [size_is][in] */ ObjectID rootRefIds[  ])
{
	return E_NOTIMPL;
}


// EXCEPTION EVENTS - Exception creation
HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionThrown( /* [in] */ ObjectID thrownObjectId)
{
	return E_NOTIMPL;
}


// EXCEPTION EVENTS - Search phase
HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionSearchFunctionEnter( /* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionSearchFunctionLeave(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionSearchFilterEnter( /* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionSearchFilterLeave(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionSearchCatcherFound( /* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionCLRCatcherFound(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionCLRCatcherExecute(void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionOSHandlerEnter( /* [in] */ UINT_PTR __unused)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionOSHandlerLeave( /* [in] */ UINT_PTR __unused)
{
	return E_NOTIMPL;
}


// EXCEPTION EVENTS - Unwind phase
HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionUnwindFunctionEnter( /* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionUnwindFunctionLeave(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionUnwindFinallyEnter( /* [in] */ FunctionID functionId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionUnwindFinallyLeave(void)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionCatcherEnter( /* [in] */ FunctionID functionId,
															   /* [in] */ ObjectID objectId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::ExceptionCatcherLeave(void)
{
	return E_NOTIMPL;
}



HRESULT STDMETHODCALLTYPE CProfilerImpl::COMClassicVTableCreated( /* [in] */ ClassID wrappedClassId,
																 /* [in] */ REFGUID implementedIID,
																 /* [in] */ void *pVTable,
																 /* [in] */ ULONG cSlots)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::COMClassicVTableDestroyed( /* [in] */ ClassID wrappedClassId,
																   /* [in] */ REFGUID implementedIID,
																   /* [in] */ void *pVTable)
{
	return E_NOTIMPL;
}


//
// Methods from ICorProfilerCallback2
//

HRESULT STDMETHODCALLTYPE CProfilerImpl::ThreadNameChanged(
	/* [in] */ ThreadID threadId,
	/* [in] */ ULONG cchName,
	/* [in] */ WCHAR name[  ])
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::GarbageCollectionStarted(
	/* [in] */ int cGenerations,
	/* [length_is][size_is][in] */ BOOL generationCollected[  ],
	/* [in] */ COR_PRF_GC_REASON reason)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::SurvivingReferences(
	/* [in] */ ULONG cSurvivingObjectIDRanges,
	/* [size_is][in] */ ObjectID objectIDRangeStart[  ],
	/* [size_is][in] */ ULONG cObjectIDRangeLength[  ])
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::GarbageCollectionFinished(void)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::FinalizeableObjectQueued(/* [in] */ DWORD finalizerFlags,
																 /* [in] */ ObjectID objectID)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::RootReferences2(/* [in] */ ULONG cRootRefs,
												        /* [size_is][in] */ ObjectID rootRefIds[  ],
													    /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[  ],
														/* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[  ],
														/* [size_is][in] */ UINT_PTR rootIds[  ])
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::HandleCreated( /* [in] */ GCHandleID handleId,
													   /* [in] */ ObjectID initialObjectId)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CProfilerImpl::HandleDestroyed(/* [in] */ GCHandleID handleId)
{
	return E_NOTIMPL;
}

//
// Methods from ICorProfilerCallback3
//

HRESULT STDMETHODCALLTYPE CProfilerImpl::InitializeForAttach(
																   /* [in] */ IUnknown *pCorProfilerInfoUnk,
																   /* [in] */ void *pvClientData,
																   /* [in] */ UINT cbClientData)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::ProfilerAttachComplete()
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CProfilerImpl::ProfilerDetachSucceeded()
{
	return E_NOTIMPL;
}

}
