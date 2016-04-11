// IECacheCleaner.cpp : 定义控制台应用程序的入口点。
//

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>

#include <Windows.h>

#include <wininet.h>
#pragma comment(lib,"wininet.lib")

#define URLCACHE_FIND_ALL 0x0031003d

int wmain(int argc, _TCHAR* argv[])
{
	GROUPID GroupID = NULL;

	HANDLE hGroupFind = FindFirstUrlCacheGroup(
		0, CACHEGROUP_SEARCH_ALL, nullptr, 0, &GroupID, nullptr);

	if (NULL != hGroupFind)
	{
		do
		{
			DeleteUrlCacheGroup(GroupID, CACHEGROUP_FLAG_FLUSHURL_ONDELETE, nullptr);
		} while (FindNextUrlCacheGroup(hGroupFind, &GroupID, nullptr));
		FindCloseUrlCache(hGroupFind);
	}

	DWORD dwBufSize = 0;
	LPINTERNET_CACHE_ENTRY_INFOW lpEntryInfo = nullptr;

	FindFirstUrlCacheEntryExW(
		nullptr, 0, URLCACHE_FIND_ALL, 0, nullptr, &dwBufSize,
		nullptr, nullptr, nullptr);

	lpEntryInfo = (LPINTERNET_CACHE_ENTRY_INFOW)malloc(dwBufSize);
	if (lpEntryInfo)
	{
		HANDLE hEntryFind = FindFirstUrlCacheEntryExW(
			nullptr, 0, URLCACHE_FIND_ALL, 0, lpEntryInfo, &dwBufSize,
			nullptr, nullptr, nullptr);

		if (NULL != hEntryFind)
		{
			do
			{		
				DeleteUrlCacheEntryW(lpEntryInfo->lpszSourceUrlName);
				free(lpEntryInfo);
				lpEntryInfo = nullptr;

				FindNextUrlCacheEntryExW(
					hEntryFind, nullptr, &dwBufSize, nullptr, nullptr, nullptr);

				lpEntryInfo = (LPINTERNET_CACHE_ENTRY_INFOW)malloc(dwBufSize);
				if (!lpEntryInfo) break;

			} while (FindNextUrlCacheEntryExW(
				hEntryFind, lpEntryInfo, &dwBufSize, nullptr, nullptr, nullptr));
			FindCloseUrlCache(hEntryFind);
		}
	}
	return 0;
}