/**
 *  @file
 *  @brief The file contain the proxy window
 *  @author wplaat
 *
 *  Copyright (C) 2008-2012 PlaatSoft
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 2.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <QtGui>

#include "proxy.h"
#include "general.h"
#include "ui_proxy.h"


Proxy::Proxy(QWidget *parent) : QWidget(parent), ui(new Ui::Proxy)
{
    ui->setupUi(this);

    // Set fix windows form size.
    setMinimumSize(400,249);
    setMaximumSize(400,249);

    readSettings();

    updateScreen();

    setWindowTitle("Settings");
}

Proxy::~Proxy()
{
    delete ui;
}

/**
 * Encrypt QString (Very easy but unsafe approach)
 */
QString Proxy::encrypt(QString in) {
  QChar* data = in.data();
  int i=0;
  while (!data[i].isNull()) {
     char tmp =data[i].toAscii();
     tmp+=(i+1);
     data[i]=tmp;
     ++data;
  }
  return in;
}

/**
 * Decrypt QString (Very easy but unsafe approach)
 */
QString Proxy::decrypt(QString in) {
  QChar* data = in.data();
  int i=0;
  while (!data[i].isNull()) {
     char tmp =data[i].toAscii();
     tmp-=(i+1);
     data[i]=tmp;
     ++data;
  }
  return in;
}

/**
 * Read settings from Registry
 */
void Proxy::readSettings()
{
    // Fetch configuration
    QSettings settings("PlaatSoft",  APPL_NAME);

    ui->LoginNameEdit->setText(settings.value("loginName","").toString());
    ui->passwordEdit->setText( decrypt(settings.value("password","").toString()));
    ui->proxyAddressEdit->setText( settings.value("proxyAddress","").toString());
    ui->proxyPortEdit->setText( settings.value("proxyPort","").toString());
    ui->enabledCheckBox->setChecked(settings.value("proxyEnabled",false).toBool());

    ui->username2->setText(settings.value("token1","").toString());
    ui->password2->setText(settings.value("token2","").toString());
}

/**
 * Save settings to Registry
 */
void Proxy::writeSettings()
{
    // Store configuration
    QSettings settings("PlaatSoft",  APPL_NAME);

    settings.setValue("loginName", ui->LoginNameEdit->text());
    settings.setValue("password", encrypt(ui->passwordEdit->text()));
    settings.setValue("proxyAddress", ui->proxyAddressEdit->text());
    settings.setValue("proxyPort", ui->proxyPortEdit->text());
    settings.setValue("proxyEnabled", ui->enabledCheckBox->isChecked());

    settings.setValue("token1", ui->username2->text());
    settings.setValue("token2", ui->password2->text());
}

/**
 * Update screen components
 */
void Proxy::updateScreen()
{
    if (ui->enabledCheckBox->isChecked())
    {
        ui->LoginNameEdit->setEnabled(true);
        ui->passwordEdit->setEnabled(true);
        ui->proxyAddressEdit->setEnabled(true);
        ui->proxyPortEdit->setEnabled(true);
    }
    else
    {
        ui->LoginNameEdit->setEnabled(false);
        ui->passwordEdit->setEnabled(false);
        ui->proxyAddressEdit->setEnabled(false);
        ui->proxyPortEdit->setEnabled(false);
    }
}

// ************************************
// Button & Menu events
// ************************************

void Proxy::on_cancelButton_pressed()
{
   readSettings();
   close();
}

void Proxy::on_OkButton_pressed()
{
   writeSettings();

   QMessageBox msgBox;
   msgBox.setText("Please restart WarQuest to activate the new settings.");
   msgBox.exec();

   close();
}

void Proxy::on_enabledCheckBox_clicked()
{
   updateScreen();
}

// ************************************
// The end
// ************************************
