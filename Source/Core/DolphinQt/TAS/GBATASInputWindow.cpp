// Copyright 2022 Dolphin Emulator Project
// SPDX-License-Identifier: GPL-2.0-or-later

#include "DolphinQt/TAS/GBATASInputWindow.h"

#include <QCheckBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QSpinBox>
#include <QVBoxLayout>

#include "Common/CommonTypes.h"

#include "Core/HW/GBAPad.h"
#include "Core/HW/GBAPadEmu.h"

#include "DolphinQt/TAS/TASCheckBox.h"

#include "InputCommon/ControllerEmu/ControllerEmu.h"
#include "InputCommon/InputConfig.h"

GBATASInputWindow::GBATASInputWindow(QWidget* parent, int controller_id)
    : TASInputWindow(parent), m_controller_id(controller_id)
{
  setWindowTitle(tr("GBA TAS Input %1").arg(controller_id + 1));

  m_b_button =
      CreateButton(QStringLiteral("&B"));
  m_a_button =
      CreateButton(QStringLiteral("&A"));
  m_l_button =
      CreateButton(QStringLiteral("&L"));
  m_r_button =
      CreateButton(QStringLiteral("&R"));
  m_select_button = CreateButton(QStringLiteral("SELE&CT"));
  m_start_button = CreateButton(QStringLiteral("&START"));

  m_left_button =
      CreateButton(QStringLiteral("L&eft"));
  m_up_button = CreateButton(QStringLiteral("&Up"));
  m_down_button =
      CreateButton(QStringLiteral("&Down"));
  m_right_button =
      CreateButton(QStringLiteral("R&ight"));

  auto* buttons_layout = new QGridLayout;

  buttons_layout->addWidget(m_left_button, 0, 0);
  buttons_layout->addWidget(m_up_button, 0, 1);
  buttons_layout->addWidget(m_down_button, 0, 2);
  buttons_layout->addWidget(m_right_button, 0, 3);

  buttons_layout->addWidget(m_l_button, 1, 0);
  buttons_layout->addWidget(m_r_button, 1, 1);
  buttons_layout->addWidget(m_b_button, 1, 2);
  buttons_layout->addWidget(m_a_button, 1, 3);

  buttons_layout->addWidget(m_select_button, 2, 0, 1, 2);
  buttons_layout->addWidget(m_start_button, 2, 2, 1, 2);

  buttons_layout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding), 0, 4);

  QGroupBox* buttons_box = new QGroupBox(tr("Buttons"));
  buttons_box->setLayout(buttons_layout);

  auto* layout = new QVBoxLayout;
  layout->addWidget(buttons_box);
  layout->addWidget(m_settings_box);

  setLayout(layout);
}

void GBATASInputWindow::hideEvent(QHideEvent* event)
{
  Pad::GetGBAConfig()->GetController(m_controller_id)->ClearInputOverrideFunction();
}

void GBATASInputWindow::showEvent(QShowEvent* event)
{
  Pad::GetGBAConfig()
      ->GetController(m_controller_id)
      ->SetInputOverrideFunction(m_overrider.GetInputOverrideFunction());
}
