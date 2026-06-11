#pragma once

#include <Windows.h>
#include <string>
#include "minecraft_auth.h"

// Resolves the launch authentication config, showing auth UI if needed
// Returns true if auth was successful (either online or offline), false otherwise
bool ResolveLaunchAuthConfig(ICoreWindow* window, LaunchAuthConfig& outConfig);
