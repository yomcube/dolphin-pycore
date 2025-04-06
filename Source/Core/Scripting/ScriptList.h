// Copyright 2023 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include "Scripting/ScriptingEngine.h"

#include <unordered_map>
#include <list>

namespace Scripts
{

void StartPendingScripts();
void StopAllScripts();

// extern so that different translation units can access a global instance of these vars
// i.e. DolphinLib needs to access these variables even though they're housed in the Scripting unit
extern std::unordered_map<std::string, Scripting::ScriptingBackend*> g_scripts;
extern bool g_scripts_started;
extern std::list<std::string> g_scripts_to_start;
extern std::list<std::string> g_scripts_to_stop;
}
