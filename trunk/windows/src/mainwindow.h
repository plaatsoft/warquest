/**
 *  @file
 *  @brief The file contain the mainwindow class
 *  @author wplaat
 *
 *  Copyright (C) 2008-2013 PlaatSoft
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QtNetwork>
/**
 *  @file
 *  @brief The file contain the proxy class
 *  @author wplaat
 *
 *  Copyright (C) 2008-2014 PlaatSoft
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

#include "proxy.h"
#include "about.h"

namespace Ui {
    class MainWindow;
}

enum
{
    STATE_IDLE=0,
    STATE_VERSION_CHECK=1,
    STATE_REQUEST_DATA=2,
    STATE_RELEASE_NOTES=3
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

     // User action methods
     void doAbout();
     void doProxy();
     void doReload();
     void setProgress(int p);
     void finishLoading(bool);
     void download(const QNetworkRequest &);

     // HTTP related methods
     void fetchVersion();
     void replyFinished(QNetworkReply*);
     void linkClickedSlot( QUrl url );

private:
   Ui::MainWindow *ui;

   int progress;
   int newAccount;
   int startup;

   QGraphicsScene *scene;
   QAction *aboutAct;
   QAction *proxyAct;
   QAction *reloadAct;

   QStandardItemModel *issues;

   // HTTP related variables
   int stateMachine;
   QAction *fetchAct;
   QNetworkAccessManager *manager;

   // Other child windows
   About about;
   Proxy proxy;

   void initNetwork(void);
   void parseVersion(QString response);
   void setProxy();
   void closeEvent(QCloseEvent *event);
   void readSettings();
   void writeSettings();
   void contextMenuEvent(QContextMenuEvent *event);
   void adjustTitle();
};

#endif // MAINWINDOW_H
