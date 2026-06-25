#include <windows.h>
#include <iostream>

typedef int (*GetCurrentDesktopNumber_t)();

int main()
{
  HMODULE dll = LoadLibraryA("VirtualDesktopAccessor.dll");

  if (!dll)
  {
    std::cout << "Failed to load DLL" << std::endl;
    return 1;
  }

  auto GetCurrentDesktopNumber =
    (GetCurrentDesktopNumber_t)GetProcAddress(
      dll,
      "GetCurrentDesktopNumber");

  if (!GetCurrentDesktopNumber)
  {
    std::cout << "Failed to get function" << std::endl;
    return 2;
  }

  std::cout << "Monitoring virtual desktop...\n";

  int last_desktop = -1;
  int last_monitor_count = -1;

  while (true)
  {
    int current_desktop = GetCurrentDesktopNumber();
    if (current_desktop != last_desktop)
    {
      last_desktop = current_desktop;
      std::cout << "Active desktop: " << current_desktop << std::endl;
    }

    int current_monitor_count = GetSystemMetrics(SM_CMONITORS);
    if (current_monitor_count != last_monitor_count)
    {
      last_monitor_count = current_monitor_count;
      std::cout << "Number of monitors: " << current_monitor_count << std::endl;
    }

    Sleep(1000);
  }

  return 0;
}