#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>


#define IMAGEBASEPRERUN 0x140000000
#define NUMBEROFGHOST_RVA 0x140156F80 - IMAGEBASEPRERUN
#define GMUTEXDONE_RVA 0x140156F94  - IMAGEBASEPRERUN
#define GNUMBERDONE_RVA  0x140156F7C - IMAGEBASEPRERUN

#define TARGETNUMBEROFGHOST 100000

// Chương trình kiểm tra 2 điều kiện
// - Phase 1: Số ghost được lưu ở biến global, có thể lấy từ API TextOutA  <-- có thể thay đổi biến bằng WriteProcessMemory
// - Phase 2: Số lượng Mutex dạng GHOST_%d, sao cho đủ từ 0 -> 100000 mutex  <-- có thể tự tạo


// Return the Image Base Address of a process given its handle
LPVOID GetProcessImageBase(HANDLE hProcess) {
    if (!hProcess) return NULL;
    
    DWORD pid = GetProcessId(hProcess);
    if (!pid) return NULL;
    
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);
    if (hSnap == INVALID_HANDLE_VALUE) return NULL;

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);
    
    LPVOID baseAddr = NULL;
    if (Module32First(hSnap, &me32)) {
        // First module is always the main executable -> image base
        baseAddr = me32.modBaseAddr;
    }
    
    CloseHandle(hSnap);
    return baseAddr;
}


// Hàm này tìm process id của tiến trình summon.exe, có thể hardcode luôn PID để tiết kiệm thời gian
DWORD GetProcId(const wchar_t ProcName[]){
    DWORD ProcId = 0;
    PROCESSENTRY32W ProcEntry = {0};
    ProcEntry.dwSize = sizeof(ProcEntry);

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(hSnap){
        if(Process32FirstW(hSnap, &ProcEntry)){
            do{
                if(!wcsicmp(ProcEntry.szExeFile, ProcName)){
                    ProcId = ProcEntry.th32ProcessID;
                    break;
                }
            }
            while(Process32NextW(hSnap, &ProcEntry));
        }
    }
    return ProcId;
}

DWORD WINAPI SolvePhase1(LPVOID lParam){
    DWORD ProcessId = *(DWORD*)lParam;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
    DWORD TargetNumberOfGhost = TARGETNUMBEROFGHOST;
    DWORD TargetMutexDone = 1;
    DWORD TargetNumberDone = 1;
    DWORD CurrentNumberOfGhost = 0;
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);


    if(!hProcess){
        printf("Cannot obtain process handle with error code: %ld\n", GetLastError());
        ExitProcess(0);
    }

    LPVOID TargetProcessImageBase = GetProcessImageBase(hProcess);
    printf("[+](PHASE 1) Image Base Address: 0x%p\n", TargetProcessImageBase);

    // 3 value being check within the process
    LPVOID TargetNumberOfGhostVA = TargetProcessImageBase + NUMBEROFGHOST_RVA;
    LPVOID TargetMutexDoneVA = TargetProcessImageBase + GMUTEXDONE_RVA;
    LPVOID TargetNumberDoneVA = TargetProcessImageBase + GNUMBERDONE_RVA;
    

    printf("[+](PHASE 1) Overwriting global variable at address...: 0x%p\n", TargetNumberOfGhostVA);
    // Need read write permission to overwrite 
    // DWORD SizeOfGlobalTargetNumberOfGhostInTargetProcess = sizeof(DWORD);
    // need this so we can rollback
    DWORD OldProtect;

    // Overwrite du lieu kiem so so luong
    VirtualProtectEx(hProcess, TargetNumberOfGhostVA, sizeof(DWORD), PAGE_READWRITE, &OldProtect);
    VirtualProtectEx(hProcess, TargetMutexDoneVA, sizeof(DWORD), PAGE_READWRITE, &OldProtect);
    VirtualProtectEx(hProcess, TargetNumberDoneVA, sizeof(DWORD), PAGE_READWRITE, &OldProtect);
    
    // ReadProcessMemory(hProcess, TargetNumberOfGhostVA, &CurrentNumberOfGhost, sizeof(DWORD), NULL);
    // printf("[+](PHASE 1) Old number of ghost: %ld\n", CurrentNumberOfGhost);
    
    
    
    // yea... the program continuously check for this value, so we write it continuously :v
    // Overwrite global val with our TargetNumberOfGhost
    
    WriteProcessMemory(hProcess, TargetNumberOfGhostVA, &TargetNumberOfGhost, sizeof(DWORD), NULL);
    WriteProcessMemory(hProcess, TargetMutexDoneVA, &TargetMutexDone, sizeof(DWORD), NULL);
    WriteProcessMemory(hProcess, TargetNumberDoneVA, &TargetNumberDone, sizeof(DWORD), NULL);
        
    
    printf("[+] (PHASE 1) Successfully overwrite process data\n");


    CloseHandle(hProcess);
    return 0;
}

// tu tao mutex
DWORD WINAPI SolvePhase2(LPVOID lParam){
    char MutexName[MAX_PATH];
    for (int i = 0; i < TARGETNUMBEROFGHOST - 1; i++){
        ZeroMemory(MutexName, 0);
        sprintf(MutexName, "GHOST_%d", i);
        CreateMutexA(NULL, FALSE, MutexName);
    }

    printf("[+] (PHASE 2) Successfully creating %d Mutex\n", TARGETNUMBEROFGHOST);
    return 0;
}



int main(){
    DWORD TargetProcessId = GetProcId(L"summon.exe");
    if(!TargetProcessId){
        printf("Cannot find summon.exe process");
        ExitProcess(0);
    }

    printf("PID: %ld, creating thread...\n", TargetProcessId);

    HANDLE hPhase[2];
    hPhase[0] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SolvePhase1, &TargetProcessId, 0, NULL);
    hPhase[1] = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SolvePhase2, NULL, 0, NULL);

    WaitForMultipleObjects(2, hPhase, TRUE, INFINITE);

    return 0;
}