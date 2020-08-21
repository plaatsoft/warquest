/**
 *  @file
 *  @brief The file contain the proxy class
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
 
#ifndef PROXY_H
#define PROXY_H

#include <QWidget>

namespace Ui {
    class Proxy;
}

class Proxy : public QWidget
{
    Q_OBJECT

public:
    explicit Proxy(QWidget *parent = 0);
    ~Proxy();

    QString encrypt(QString in);
    QString decrypt(QString in);
    void readSettings();

private:
    Ui::Proxy *ui;


    void writeSettings();
    void updateScreen();

private slots:
    void on_enabledCheckBox_clicked();
    void on_OkButton_pressed();
    void on_cancelButton_pressed();
};

#endif // PROXY_H
