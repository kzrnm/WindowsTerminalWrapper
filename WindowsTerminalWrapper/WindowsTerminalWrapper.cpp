#include<windows.h>

int WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{

	wchar_t envLocalAppData[1024] = { '\0' };
	DWORD envLocalAppDataSize = GetEnvironmentVariable(L"LOCALAPPDATA", envLocalAppData, sizeof(envLocalAppData) / sizeof(envLocalAppData[0]));
	if (envLocalAppDataSize == 0)
	{
		return 2;
	}

	wchar_t CurrentDir[1024] = { '\0' };
	DWORD CurrentDirSize = GetCurrentDirectory(sizeof(CurrentDir) / sizeof(CurrentDir[0]), CurrentDir);
	if (envLocalAppDataSize == 0)
	{
		return 2;
	}

	wchar_t commandLine[2048] = { '\0' };
	wsprintf(commandLine, L"\"%s\\Microsoft\\WindowsApps\\wt.exe\" -d \"%s\"", envLocalAppData, CurrentDir);

	STARTUPINFO si{};
	PROCESS_INFORMATION pi{};

	si.cb = sizeof(si);

	if (CreateProcess(nullptr, commandLine, nullptr, nullptr, false, 0, nullptr, nullptr, &si, &pi))
	{
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		return 1;
	}

	return 0;
}