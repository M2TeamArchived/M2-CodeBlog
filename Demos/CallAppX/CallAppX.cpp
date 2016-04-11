// CallAppX.cpp : 定义控制台应用程序的入口点。
//

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <objbase.h>
#include <atlbase.h>
#include <string>

/*++

Routine Description:

This routine launches your app using IApplicationActivationManager.

Arguments:

strAppUserModelID - AppUserModelID of the app to launch.
pdwProcessId - Output argument that receives the process id of the launched app.

Return value:

HRESULT indicating success/failure

--*/
HRESULT LaunchApp(const std::wstring& strAppUserModelId, PDWORD pdwProcessId)
{
	CComPtr<IApplicationActivationManager> spAppActivationManager;
	HRESULT hrResult = E_INVALIDARG;
	if (!strAppUserModelId.empty())
	{
		// Instantiate IApplicationActivationManager
		hrResult = CoCreateInstance(
			CLSID_ApplicationActivationManager,
			NULL,
			CLSCTX_LOCAL_SERVER,
			IID_IApplicationActivationManager,
			(LPVOID*)&spAppActivationManager);

		if (SUCCEEDED(hrResult))
		{
			// This call ensures that the app is launched as the foreground window
			hrResult = CoAllowSetForegroundWindow(spAppActivationManager, NULL);

			// Launch the app
			if (SUCCEEDED(hrResult))
			{
				hrResult = spAppActivationManager->ActivateApplication(
					strAppUserModelId.c_str(),
					NULL,
					AO_NONE,
					pdwProcessId);
			}
		}
	}

	return hrResult;
}
/*
Microsoft.AAD.BrokerPlugin_cw5n1h2txyewy!App
Microsoft.BioEnrollment_cw5n1h2txyewy!App
Microsoft.Windows.CloudExperienceHost_cw5n1h2txyewy!App
Microsoft.Windows.ShellExperienceHost_cw5n1h2txyewy!App
windows.immersivecontrolpanel_cw5n1h2txyewy!microsoft.windows.immersivecontrolpanel
Microsoft.Windows.Cortana_cw5n1h2txyewy!CortanaUI
Microsoft.AccountsControl_cw5n1h2txyewy!App
Microsoft.LockApp_cw5n1h2txyewy!WindowsDefaultLockScreen
Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge
Microsoft.Windows.AssignedAccessLockApp_cw5n1h2txyewy!App
Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy!App
Microsoft.Windows.ParentalControls_cw5n1h2txyewy!App
Microsoft.Windows.SecondaryTileExperience_cw5n1h2txyewy!App
Microsoft.WindowsFeedback_cw5n1h2txyewy!App
Microsoft.XboxGameCallableUI_cw5n1h2txyewy!Microsoft.XboxGameCallableUI
Microsoft.XboxIdentityProvider_cw5n1h2txyewy!Microsoft.XboxIdentityProvider
Windows.ContactSupport_cw5n1h2txyewy!App
Windows.MiracastView_cw5n1h2txyewy!Microsoft.Windows.MiracastView
Windows.PrintDialog_cw5n1h2txyewy!Microsoft.Windows.PrintDialog
Windows.PurchaseDialog_cw5n1h2txyewy!Microsoft.Windows.PurchaseDialog
Microsoft.ZuneMusic_8wekyb3d8bbwe!Microsoft.ZuneMusic
windows.devicesflow_cw5n1h2txyewy!microsoft.windows.devicesflow
Microsoft.SkypeApp_kzf8qxf38zg5c!App
Microsoft.Appconnector_8wekyb3d8bbwe!App
Microsoft.WindowsPhone_8wekyb3d8bbwe!CompanionApp.App
Microsoft.ConnectivityStore_8wekyb3d8bbwe!App
Microsoft.3DBuilder_8wekyb3d8bbwe!App
Microsoft.People_8wekyb3d8bbwe!x4c7a3b7dy2188y46d4ya362y19ac5a5805e5x
Microsoft.WindowsSoundRecorder_8wekyb3d8bbwe!App
Microsoft.WindowsAlarms_8wekyb3d8bbwe!App
microsoft.windowscommunicationsapps_8wekyb3d8bbwe!microsoft.windowslive.mail
microsoft.windowscommunicationsapps_8wekyb3d8bbwe!microsoft.windowslive.calendar
Microsoft.CommsPhone_8wekyb3d8bbwe!App
Microsoft.Getstarted_8wekyb3d8bbwe!App
Microsoft.XboxApp_8wekyb3d8bbwe!Microsoft.XboxApp
Microsoft.WindowsCamera_8wekyb3d8bbwe!App
Microsoft.MicrosoftSolitaireCollection_8wekyb3d8bbwe!App
Microsoft.WindowsMaps_8wekyb3d8bbwe!App
Microsoft.WindowsCalculator_8wekyb3d8bbwe!App
Microsoft.Messaging_8wekyb3d8bbwe!x27e26f40ye031y48a6yb130yd1f20388991ax
Microsoft.Messaging_8wekyb3d8bbwe!SkypeName
Microsoft.Messaging_8wekyb3d8bbwe!App
Microsoft.BingFinance_8wekyb3d8bbwe!AppexFinance
Microsoft.BingNews_8wekyb3d8bbwe!AppexNews
Microsoft.BingSports_8wekyb3d8bbwe!AppexSports
Microsoft.BingWeather_8wekyb3d8bbwe!App
Microsoft.Windows.Photos_8wekyb3d8bbwe!App
Microsoft.WindowsStore_8wekyb3d8bbwe!App
Microsoft.Office.OneNote_8wekyb3d8bbwe!microsoft.onenoteim
Microsoft.ZuneVideo_8wekyb3d8bbwe!Microsoft.ZuneVideo
Microsoft.MicrosoftOfficeHub_8wekyb3d8bbwe!Microsoft.MicrosoftOfficeHub
Microsoft.Office.Sway_8wekyb3d8bbwe!Microsoft.Sway
*/

int wmain(int argc, _TCHAR* argv[])
{
	HRESULT hrResult = S_OK;
	if (SUCCEEDED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED)))
	{
		DWORD dwProcessId = 0;
		//explorer.exe "shell:AppsFolder\Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge"
		hrResult = LaunchApp(L"Microsoft.MicrosoftEdge_8wekyb3d8bbwe!MicrosoftEdge", &dwProcessId);

		CoUninitialize();
	}

	return hrResult;
}

