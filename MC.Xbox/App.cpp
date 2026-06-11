        LaunchAuthConfig authConfig;
        bool authConfigReady = false;
        for (;;) {
        bool repairDownloads = false;
        while (true) {
            // Check if we are in offline mode first
            // Assuming you have a way to signal offline mode from UI, e.g., a global or passed via authConfig
            // For now, we rely on ResolveLaunchAuthConfig to handle the UI selection
            
            if (!authConfigReady) {
                // ResolveLaunchAuthConfig must be updated to return true immediately if Offline is selected
                // and populate authConfig with offline data.
                if (!ResolveLaunchAuthConfig(g_authWindow.Get(), authConfig)) {
                    WriteLog(L"Dynamic authentication failed");
                    return E_FAIL;
                }
                authConfigReady = true;
                
                // If offline mode was selected, authConfig.isOffline will be true
                if (authConfig.isOffline) {
                    WriteLog(L"Launching in Offline Mode");
                    // Skip online checks, proceed directly to play
                    break; 
                }
            }

            const MainMenuAction menuAction = ShowMainMenu(g_authWindow.Get(), authConfig, exeDir);
            if (menuAction == MainMenuAction::Play) {
                break;
            }
            if (menuAction == MainMenuAction::RepairDownloads) {
                repairDownloads = true;
                break;
            }

            ClearRefreshToken();
            authConfig = LaunchAuthConfig{};
            authConfigReady = false;
            WriteLog(L"Saved Microsoft refresh token cleared by sign out");
        }