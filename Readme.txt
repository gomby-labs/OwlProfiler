This code show how to use Microsoft Profiler API to view assemblies being loaded into the process.
The data is being written to OutputDebugString and can be viewed with WinDbg.

After you build it you have to:
1. Register the DLL with regsvr32 utility
2. Set two environment variables that the process can access:
COR_ENABLE_PROFILING=0x1
COR_PROFILER={82580D05-BAB8-518B-A137-13FCC3BA8BF5}

