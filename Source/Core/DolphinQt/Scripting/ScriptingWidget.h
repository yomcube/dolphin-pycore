// Copyright 2018 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <QDockWidget>
#include <QFileSystemModel>
#include <QGroupBox>
#include <QPushButton>
#include <QTableView>
#include <QTreeView>

#include <mutex>
#include <string>

#include "DolphinQt/Scripting/ScriptsListModel.h"

class ScriptingWidget : public QDockWidget
{
public:
  ScriptingWidget(QWidget* parent = nullptr);
  ~ScriptingWidget();
  void UpdateIcons();
  void AddNewScript();
  void RestartSelectedScripts();
  void ToggleSelectedScripts();
  void ToggleScriptIndex(QModelIndex index);
  void SetScriptState(std::string file_path, bool activate);
  void UpdatePendingScripts();

protected:
  void closeEvent(QCloseEvent*) override;

private:
  void OnEmulationStateChanged(Core::State state);
  void OnDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight,
                     const QList<int>& roles);
  
  void OpenScriptsFolder();
  void LoadSettings();
  void SaveSettings();

  QPushButton* m_button_add_new;
  QPushButton* m_button_reload_selected;
  QPushButton* m_button_open_folder;
  QGroupBox* m_scripts_group;

  ScriptsFileSystemModel* m_scripts_model;
  QTreeView* m_tree;
};
