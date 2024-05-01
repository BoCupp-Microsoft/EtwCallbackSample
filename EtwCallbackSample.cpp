#include <bitset>
#include <conio.h>
#include <iostream>

#include <windows.h> // Definitions required by TraceLoggingProvider.h
#include <TraceLoggingProvider.h> // The C/C++ TraceLogging API

using namespace std;

// Define a handle to a TraceLogging provider
TRACELOGGING_DEFINE_PROVIDER(
  g_hMyComponentProvider,
  "EtwCallbackSample",
  // {0205c222-cf97-5c11-9756-56a2cee02cb0}
  (0x0205c222, 0xcf97, 0x5c11, 0x97, 0x56, 0x56, 0xa2, 0xce, 0xe0, 0x2c, 0xb0));

// This callback is invoked by Windows every time the ETW tracing status is changed for this application.
void WINAPI ETWEnableCallback(LPCGUID /* source_id */, ULONG is_enabled,
  UCHAR level, ULONGLONG match_any_keyword,
  ULONGLONG match_all_keyword,
  PEVENT_FILTER_DESCRIPTOR filter_data,
  PVOID /* callback_context */)
{
  cout
    << "is_enabled:" << (void*)is_enabled
    << "; level:" << (void*)level
    << "; match_any_keyword:" << (void*)match_any_keyword
    << "; match_all_keyword:" << (void*)match_all_keyword
    << "; filter_data:" << (void*)filter_data
    << endl
  ;
}

void LoopUntilQ()
{
  cout << "Type 'q' when you want to quit." << endl;

  char c;
  
  while (true) {
    c = _getch();
    if (c == 'q') {
      break;
    }
  }
}

int main()
{
  cout << "Calling TraceLoggingRegisterEx." << endl;
  TraceLoggingRegisterEx(g_hMyComponentProvider, ETWEnableCallback, nullptr);
  cout << "TraceLoggingRegisterEx returned." << endl << endl;

  LoopUntilQ();

  cout << endl << "Calling TraceLoggingUnregister." << endl;
  TraceLoggingUnregister(g_hMyComponentProvider);
  cout << "TraceLoggingUnregister returned." << endl;
}
