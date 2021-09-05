#include<iostream>
#include<Windows.h>

using namespace std;

int main(int argc, char **argv)
{
  if(argc != 2)
  	return -1;

  void *lla;
  char *strdll;
  HMODULE dllHandle;
  HANDLE thrHandle;
  HANDLE pHandle;
  LPVOID pMem;

  pid = atoi(argv[1]);
  const size_t sstrdll = strlen(argv[2])+1;
  strdll = argv[2];

  pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if(pHandle==NULL)
  	return -1;

  pMem = VirtualAllocEx(pHandle, NULL, strdll, MEM_COMMIT, PAGE_READWRITE);

  if(pMem)
  {
    if(WriteProcessMemory(pHandle, pMem, strdll, sstrdll))
    {
      dllHandle = GetModuleHandle("Kernel32.dll");
      if(dllHandle)
      {
      	lla = GetProcAddress(dllHandle, "LoadLibraryA");
      	if(lla)
      	{
      	  DWORD dwThrId=0;
      	  thrHandle = CreateRemoteThread(pHandle, NULL, 0, (LPTHREAD_START_ROUTINE)lla, pMem, 0, &dwThrId);
      	}
      }
    }
  }
}
