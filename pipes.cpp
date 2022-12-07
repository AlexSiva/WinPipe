
#include <windows.h>

#include <iostream>

struct ProcessInfo {
  HANDLE input, output;
};

std::string CalculateProcess(std::wstring name, std::string data) {
  SECURITY_ATTRIBUTES sa;          
  sa.lpSecurityDescriptor = NULL;  
  sa.nLength = sizeof(SECURITY_ATTRIBUTES);
  sa.bInheritHandle = true;  

  ProcessInfo To, From;

  CreatePipe(&From.output, &To.input, &sa,
             0);
  CreatePipe(&To.output, &From.input, &sa,
             0);

  STARTUPINFO si;
  ZeroMemory(&si, sizeof(STARTUPINFO));
  si.dwFlags = STARTF_USESTDHANDLES;
  si.wShowWindow = SW_HIDE; 
  si.hStdOutput = From.input;
  si.hStdError = From.input;
  si.hStdInput = From.output;

  PROCESS_INFORMATION pi;

  CreateProcess(name.c_str(), NULL, NULL, NULL, TRUE,
                ABOVE_NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi); 
  DWORD num = 1024;  
  char buffer[1024];  
  int sz = data.size();

  WriteFile(To.input, data.c_str(), sz + 1, &num, NULL);
  std::cout << "Transfer: " << data << std::endl;
  CloseHandle(To.input);
  ReadFile(To.output, buffer, 1023, &num, NULL);
  std::cout << "Reading: " << buffer << std::endl;
  CloseHandle(From.output);
  CloseHandle(From.input);
  CloseHandle(To.output);
  TerminateProcess(pi.hProcess, 0);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return std::string(buffer);
}

int main() {
  CalculateProcess( L"../x64/Debug/S.exe",
      CalculateProcess(L"../x64/Debug/M.exe",
          CalculateProcess(L"../x64/Debug/P.exe",
              CalculateProcess(L"../x64/Debug/A.exe", "2 2 8 69 322 "))));
  return 0;
}

