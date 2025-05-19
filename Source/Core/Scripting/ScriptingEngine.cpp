// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#include "ScriptingEngine.h"

#include "Core/API/Events.h"
#include "Core/API/Gui.h"
#include "Core/Core.h"
#include "Core/System.h"
#include "Common/Logging/Log.h"
#include "Python/PyScriptingBackend.h"

namespace Scripting
{

ScriptingBackend::ScriptingBackend(std::filesystem::path script_filepath)
{
  INFO_LOG_FMT(SCRIPTING, "Initializing scripting engine...");
  // There is only support for python right now.
  // If there was support for multiple backend, a fitting one could be
  // detected based on the script file's extension for example.

  // This must be done on the CPU thread to prevent deadlock if CPU is currently running,
  // as we may attempt to obtain the CPU lock to read memory.
  Core::RunOnCPUThread(Core::System::GetInstance(),
      [this, script_filepath]() {
        m_state = new PyScripting::PyScriptingBackend(
            script_filepath, API::GetEventHub(), API::GetGui(), API::GetGCManip(),
            API::GetWiiButtonsManip(), API::GetWiiIRManip(), API::GetNunchuckButtonsManip());
      },
      true);
}

ScriptingBackend::~ScriptingBackend() {
  if (m_state != nullptr)
  {
    PyScripting::PyScriptingBackend* backend = static_cast<PyScripting::PyScriptingBackend*>(m_state);
    int id = backend->GetScriptId();
    API::GetEventHub().EmitEvent(API::Events::ScriptEnd{id});
    INFO_LOG_FMT(SCRIPTING, "Shutting down scripting engine...");
    delete (PyScripting::PyScriptingBackend*)m_state;
    m_state = nullptr;
  }
}

bool ScriptingBackend::s_disable_python_subinterpreters = false;
void ScriptingBackend::DisablePythonSubinterpreters()
{
  s_disable_python_subinterpreters = true;
}
bool ScriptingBackend::PythonSubinterpretersDisabled()
{
  return s_disable_python_subinterpreters;
}

ScriptingBackend::ScriptingBackend(ScriptingBackend&& other)
{
  m_state = other.m_state;
  other.m_state = nullptr;
}

ScriptingBackend& ScriptingBackend::operator=(ScriptingBackend&& other)
{
  std::swap(m_state, other.m_state);
  return *this;
}

}  // namespace Scripting
