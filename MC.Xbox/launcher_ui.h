#pragma once

#include <Windows.h>
#include <string>
#include "minecraft_auth.h"

enum class MainMenuAction {
    Play,
    Mods,
    RemoteFiles,
    RepairDownloads,
    SignOut,
    PlayOffline
};

struct MainMenuState {
    bool showMainMenu = false;
    int selectedMenuIndex = 0;
    std::wstring status;
    bool isError = false;
    std::wstring detail;
};

// Renders the main menu and returns the user's selection
MainMenuAction ShowMainMenu(ICoreWindow* window, const LaunchAuthConfig& authConfig, const std::wstring& runtimeRoot);
