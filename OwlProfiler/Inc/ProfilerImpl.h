#ifndef _ProfilerImpl_h
#define _ProfilerImpl_h

#include "resource.h"
#include "stdafx.h"
#include <map>
#include "ModuleData.h"

_COM_SMARTPTR_TYPEDEF(ICorProfilerInfo3, __uuidof(ICorProfilerInfo3));

// IProfilerImpl
[
	object,
	uuid("B1D61CCF-1A72-4B01-A45A-AB167E52BA41"),
	helpstring("IProfilerImpl Interface"),
	pointer_default(unique)
]
__interface IProfilerImpl : IUnknown
{
};

namespace OwlProfiler
{
	typedef std::map<ModuleID, ModuleData *> ModuleDataMap;

// CProfilerImpl
[
	coclass,
	threading(both),
	vi_progid("OwlProfiler.ProfilerImpl"),
	progid("OwlProfiler.ProfilerImpl.1"),
	version(1.0),
	uuid("82580D05-BAB8-518B-A137-13FCC3BA8BF5"),
  default(IProfilerImpl),
  helpstring("ProfilerImpl Class")
]
class ATL_NO_VTABLE CProfilerImpl : public IProfilerImpl, public ICorProfilerCallback3
{
public:
	CProfilerImpl();
	virtual ~CProfilerImpl();

  // Methods from ICorProfilerCallback

	virtual HRESULT STDMETHODCALLTYPE Initialize(IUnknown *pICorProfilerInfoUnk);
	virtual HRESULT STDMETHODCALLTYPE Shutdown();

	// APPLICATION DOMAIN EVENTS
	virtual HRESULT STDMETHODCALLTYPE AppDomainCreationStarted( /* [in] */ AppDomainID appDomainId);


	virtual HRESULT STDMETHODCALLTYPE AppDomainCreationFinished( /* [in] */ AppDomainID appDomainId,
																 /* [in] */ HRESULT hrStatus);


	virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownStarted( /* [in] */ AppDomainID appDomainId);


	virtual HRESULT STDMETHODCALLTYPE AppDomainShutdownFinished( /* [in] */ AppDomainID appDomainId,
																/* [in] */ HRESULT hrStatus);


	// ASSEMBLY EVENTS
	virtual HRESULT STDMETHODCALLTYPE AssemblyLoadStarted( /* [in] */ AssemblyID assemblyId);


	virtual HRESULT STDMETHODCALLTYPE AssemblyLoadFinished( /* [in] */ AssemblyID assemblyId,
															/* [in] */ HRESULT hrStatus);


	virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadStarted( /* [in] */ AssemblyID assemblyId);

	virtual HRESULT STDMETHODCALLTYPE AssemblyUnloadFinished( /* [in] */ AssemblyID assemblyId,
															 /* [in] */ HRESULT hrStatus);


	// MODULE EVENTS
	virtual HRESULT STDMETHODCALLTYPE ModuleLoadStarted( /* [in] */ ModuleID moduleId);


	virtual HRESULT STDMETHODCALLTYPE ModuleLoadFinished( /* [in] */ ModuleID moduleId,
														  /* [in] */ HRESULT hrStatus);

	virtual HRESULT STDMETHODCALLTYPE ModuleUnloadStarted( /* [in] */ ModuleID moduleId);


	virtual HRESULT STDMETHODCALLTYPE ModuleUnloadFinished( /* [in] */ ModuleID moduleId,
															/* [in] */ HRESULT hrStatus);


	virtual HRESULT STDMETHODCALLTYPE ModuleAttachedToAssembly( /* [in] */ ModuleID moduleID,
																/* [in] */ AssemblyID assemblyID);

	// CLASS EVENTS
	virtual HRESULT STDMETHODCALLTYPE ClassLoadStarted( /* [in] */ ClassID classId);

	virtual HRESULT STDMETHODCALLTYPE ClassLoadFinished( /* [in] */ ClassID classId,
														 /* [in] */ HRESULT hrStatus);

	virtual HRESULT STDMETHODCALLTYPE ClassUnloadStarted( /* [in] */ ClassID classId);

	virtual HRESULT STDMETHODCALLTYPE ClassUnloadFinished( /* [in] */ ClassID classId,
														   /* [in] */ HRESULT hrStatus);


	virtual HRESULT STDMETHODCALLTYPE FunctionUnloadStarted( /* [in] */ FunctionID functionId);

	// JIT EVENTS
	virtual HRESULT STDMETHODCALLTYPE JITCompilationStarted( /* [in] */ FunctionID functionID,
															 /* [in] */ BOOL fIsSafeToBlock);


	virtual HRESULT STDMETHODCALLTYPE JITCompilationFinished( /* [in] */ FunctionID functionId,
															  /* [in] */ HRESULT hrStatus,
															  /* [in] */ BOOL fIsSafeToBlock);

	virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchStarted( /* [in] */ FunctionID functionId,
																	  /* [out] */ BOOL *pbUseCachedFunction);


	virtual HRESULT STDMETHODCALLTYPE JITCachedFunctionSearchFinished( /* [in] */ FunctionID functionId,
																	   /* [in] */ COR_PRF_JIT_CACHE result);

	virtual HRESULT STDMETHODCALLTYPE JITFunctionPitched( /* [in] */ FunctionID functionId);


	virtual HRESULT STDMETHODCALLTYPE JITInlining( /* [in] */ FunctionID callerId,
												   /* [in] */ FunctionID calleeId,
												   /* [out] */ BOOL *pfShouldInline);


	// THREAD EVENTS
	virtual HRESULT STDMETHODCALLTYPE ThreadCreated( /* [in] */ ThreadID threadId);


	virtual HRESULT STDMETHODCALLTYPE ThreadDestroyed( /* [in] */ ThreadID threadId);


	virtual HRESULT STDMETHODCALLTYPE ThreadAssignedToOSThread( /* [in] */ ThreadID managedThreadId,
															    /* [in] */ DWORD osThreadId);

	// REMOTING EVENTS - Client-side events
	virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationStarted(void);


	virtual HRESULT STDMETHODCALLTYPE RemotingClientSendingMessage( /* [in] */ GUID *pCookie,
																	/* [in] */ BOOL fIsAsync);


	virtual HRESULT STDMETHODCALLTYPE RemotingClientReceivingReply( /* [in] */ GUID *pCookie,
																	/* [in] */ BOOL fIsAsync);


	virtual HRESULT STDMETHODCALLTYPE RemotingClientInvocationFinished(void);

	virtual HRESULT STDMETHODCALLTYPE RemotingServerReceivingMessage( /* [in] */ GUID *pCookie,
																	  /* [in] */ BOOL fIsAsync);

	virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationStarted(void);


	virtual HRESULT STDMETHODCALLTYPE RemotingServerInvocationReturned(void);

	virtual HRESULT STDMETHODCALLTYPE RemotingServerSendingReply( /* [in] */ GUID *pCookie,
																  /* [in] */ BOOL fIsAsync);


	virtual HRESULT STDMETHODCALLTYPE UnmanagedToManagedTransition( /* [in] */ FunctionID functionId,
																	/* [in] */ COR_PRF_TRANSITION_REASON reason);


	virtual HRESULT STDMETHODCALLTYPE ManagedToUnmanagedTransition( /* [in] */ FunctionID functionId,
																    /* [in] */ COR_PRF_TRANSITION_REASON reason);


	// SUSPENSION EVENTS
	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendStarted( /* [in] */ COR_PRF_SUSPEND_REASON suspendReason);

	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendFinished(void);

	virtual HRESULT STDMETHODCALLTYPE RuntimeSuspendAborted(void);

	virtual HRESULT STDMETHODCALLTYPE RuntimeResumeStarted(void);

	virtual HRESULT STDMETHODCALLTYPE RuntimeResumeFinished(void);

	virtual HRESULT STDMETHODCALLTYPE RuntimeThreadSuspended(/* [in] */ ThreadID threadId);

	virtual HRESULT STDMETHODCALLTYPE RuntimeThreadResumed( /* [in] */ ThreadID threadId);

	// GC EVENTS
	virtual HRESULT STDMETHODCALLTYPE MovedReferences( /* [in] */ ULONG cMovedObjectIDRanges,
													   /* [size_is][in] */ ObjectID oldObjectIDRangeStart[  ],
													   /* [size_is][in] */ ObjectID newObjectIDRangeStart[  ],
													   /* [size_is][in] */ ULONG cObjectIDRangeLength[  ]);

	virtual HRESULT STDMETHODCALLTYPE ObjectAllocated( /* [in] */ ObjectID objectId,
													   /* [in] */ ClassID classId);


	virtual HRESULT STDMETHODCALLTYPE ObjectsAllocatedByClass( /* [in] */ ULONG cClassCount,
															   /* [size_is][in] */ ClassID classIds[  ],
															   /* [size_is][in] */ ULONG cObjects[  ]);


	virtual HRESULT STDMETHODCALLTYPE ObjectReferences( /* [in] */ ObjectID objectId,
														/* [in] */ ClassID classId,
														/* [in] */ ULONG cObjectRefs,
														/* [size_is][in] */ ObjectID objectRefIds[  ]);

	virtual HRESULT STDMETHODCALLTYPE RootReferences( /* [in] */ ULONG cRootRefs,
													  /* [size_is][in] */ ObjectID rootRefIds[  ]);


	// EXCEPTION EVENTS - Exception creation
	virtual HRESULT STDMETHODCALLTYPE ExceptionThrown( /* [in] */ ObjectID thrownObjectId);

	// EXCEPTION EVENTS - Search phase
	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionEnter( /* [in] */ FunctionID functionId);

	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFunctionLeave(void);


	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterEnter( /* [in] */ FunctionID functionId);


	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchFilterLeave(void);


	virtual HRESULT STDMETHODCALLTYPE ExceptionSearchCatcherFound( /* [in] */ FunctionID functionId);


	virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherFound(void);


	virtual HRESULT STDMETHODCALLTYPE ExceptionCLRCatcherExecute(void);

	virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerEnter( /* [in] */ UINT_PTR __unused);


	virtual HRESULT STDMETHODCALLTYPE ExceptionOSHandlerLeave( /* [in] */ UINT_PTR __unused);


	// EXCEPTION EVENTS - Unwind phase
	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionEnter( /* [in] */ FunctionID functionId);


	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFunctionLeave(void);


	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyEnter( /* [in] */ FunctionID functionId);


	virtual HRESULT STDMETHODCALLTYPE ExceptionUnwindFinallyLeave(void);


	virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherEnter( /* [in] */ FunctionID functionId,
															 /* [in] */ ObjectID objectId);


	virtual HRESULT STDMETHODCALLTYPE ExceptionCatcherLeave(void);

	virtual HRESULT STDMETHODCALLTYPE COMClassicVTableCreated( /* [in] */ ClassID wrappedClassId,
															   /* [in] */ REFGUID implementedIID,
															   /* [in] */ void *pVTable,
															   /* [in] */ ULONG cSlots);


	virtual HRESULT STDMETHODCALLTYPE COMClassicVTableDestroyed( /* [in] */ ClassID wrappedClassId,
																 /* [in] */ REFGUID implementedIID,
																 /* [in] */ void *pVTable);
	
	//
	// Methods from ICorProfilerCallback2
	//

	virtual HRESULT STDMETHODCALLTYPE ThreadNameChanged( /* [in] */ ThreadID threadId,
														 /* [in] */ ULONG cchName,
														 /* [in] */ WCHAR name[  ])	;

	virtual HRESULT STDMETHODCALLTYPE GarbageCollectionStarted( /* [in] */ int cGenerations,
															    /* [length_is][size_is][in] */ BOOL generationCollected[  ],
																/* [in] */ COR_PRF_GC_REASON reason);

	virtual HRESULT STDMETHODCALLTYPE SurvivingReferences( /* [in] */ ULONG cSurvivingObjectIDRanges,
														   /* [size_is][in] */ ObjectID objectIDRangeStart[  ],
														   /* [size_is][in] */ ULONG cObjectIDRangeLength[  ]);

	virtual HRESULT STDMETHODCALLTYPE GarbageCollectionFinished(void);

	virtual HRESULT STDMETHODCALLTYPE FinalizeableObjectQueued( /* [in] */ DWORD finalizerFlags,
																/* [in] */ ObjectID objectID);

	virtual HRESULT STDMETHODCALLTYPE RootReferences2(/* [in] */ ULONG cRootRefs,
													  /* [size_is][in] */ ObjectID rootRefIds[  ],
													  /* [size_is][in] */ COR_PRF_GC_ROOT_KIND rootKinds[  ],
													  /* [size_is][in] */ COR_PRF_GC_ROOT_FLAGS rootFlags[  ],
													  /* [size_is][in] */ UINT_PTR rootIds[  ]);


	virtual HRESULT STDMETHODCALLTYPE HandleCreated( /* [in] */ GCHandleID handleId,
													/* [in] */ ObjectID initialObjectId);


	virtual HRESULT STDMETHODCALLTYPE HandleDestroyed( /* [in] */ GCHandleID handleId);


	//
	// Methods from ICorProfilerCallback3
	//

  virtual HRESULT STDMETHODCALLTYPE InitializeForAttach( 
      /* [in] */ IUnknown *pCorProfilerInfoUnk,
      /* [in] */ void *pvClientData,
      /* [in] */ UINT cbClientData);
  
  virtual HRESULT STDMETHODCALLTYPE ProfilerAttachComplete();
  
  virtual HRESULT STDMETHODCALLTYPE ProfilerDetachSucceeded();

private:
	bool mIsEnabled;

	ModuleDataMap		mModuleDataMap;
};
}

#endif
