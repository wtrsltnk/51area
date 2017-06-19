#include "definitions.h"

void GetSetting(Setting &setting)
{
	HKEY hKey;
	LONG lResult;
	DWORD dwDisposition;

	hKey = HKEY_LOCAL_MACHINE;

	lResult = RegCreateKeyEx (hKey, setting.lpKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);


	if (lResult == ERROR_SUCCESS)
	{
		if (dwDisposition != REG_CREATED_NEW_KEY)
		{
			RegQueryValueEx(hKey, setting.lpValueName, NULL, &setting.dwType, (unsigned char *)&setting.dwValue, &setting.dwSize);
		}
	}
	
	RegCloseKey (HKEY_LOCAL_MACHINE);
}

void SetSetting(Setting &setting)
{
	HKEY hKey;
	LONG lResult;
	DWORD dwDisposition;

	hKey = HKEY_LOCAL_MACHINE;

	lResult = RegCreateKeyEx (hKey, setting.lpKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition);


	if (lResult == ERROR_SUCCESS)
	{
		if (dwDisposition != REG_CREATED_NEW_KEY)
		{
			RegSetValueEx(hKey, setting.lpValueName, 0, setting.dwType, (unsigned char *)&setting.dwValue, setting.dwSize);
		}
	}
	
	RegCloseKey (HKEY_LOCAL_MACHINE);
}