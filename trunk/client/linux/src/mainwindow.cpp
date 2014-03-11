/**
 *  @file
 *  @brief The file contain the mainwindow window
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
 
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "general.h"
#include "proxy.h"

#include <QtGui>
#include <QtNetwork>


/**
 * Constructor
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qWarning("WarQuest Starting %s", APPL_VERSION);

    ui->setupUi(this);

    ui->webView->setVisible(false);

    readSettings();

    int height = QApplication::desktop()->screenGeometry().height();
    height -= 75;

    // Set fix windows form size.
    setMinimumSize(SCREEN_WIDTH+2,height+2);
    setMaximumSize(SCREEN_WIDTH+2,height+2);

    // Set Windows Title
    char tmp[128];
    sprintf(tmp,"%s",APPL_NAME);
    setWindowTitle(tmp);

    // Add background image.
    scene = new QGraphicsScene();
    scene->addPixmap(QPixmap(":/images/background2.jpg"));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(0,0, SCREEN_WIDTH+2, 1200);

    startup=1;

    // Set proxy if needed
    setProxy();

    // Create webkit container.
    QPalette palette = ui->webView->palette();
    palette.setBrush(QPalette::Base, Qt::transparent);

    ui->webView->page()->setPalette(palette);
    // ui->webView->page()->setForwardUnsupportedContent(true);
    ui->webView->setAttribute(Qt::WA_OpaquePaintEvent, false);
    ui->webView->setGeometry(0,0,SCREEN_WIDTH+2,height+2);
    ui->webView->setContextMenuPolicy(Qt::NoContextMenu);

    //Handle link clicks by yourself
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    // Get direct sign-on information from registry.
    QSettings qSettings("PlaatSoft", APPL_NAME);
    QString token1 = qSettings.value("token1", "NULL").toString();
    QString token2 = qSettings.value("token2", "").toString();
    QString eventId;

    if (token1 == "NULL" ) {

       // Create unique token.
       QDateTime now = QDateTime::currentDateTime();
       token1 = now.toString("yyyyMMddhhmmssz");
       token2 = token1;

       // Save tokens in windows registry
       qSettings.setValue("token1",  token1);
       qSettings.setValue("token2",  token2);

       // Set Register and Login event
       eventId = "2";

       newAccount=1;

   } else if ((token1.length()!=0) && (token2.length()!=0)) {

       // Login directly
       eventId = "1";
        newAccount=0;
   }

    //qDebug() << "token1=" << token1;
    //qDebug() << "token2=" << token2;
    //qDebug() << "eventId=" << eventId;
    //qDebug() << "version=" << APPL_VERSION;

    // Send html request to warquest website.
    QNetworkRequest request(QUrl(APPL_URL));
    request.setRawHeader("username", token1.toAscii());
    request.setRawHeader("password", token2.toAscii());
    request.setRawHeader("eid", eventId.toAscii());
    request.setRawHeader("version", APPL_VERSION);
    ui->webView->load(request, QNetworkAccessManager::PostOperation);

    // Create popup menu
    QPixmap reloadpix(":/images/reload.gif");

    reloadAct = new QAction(reloadpix, tr("&Reload"), this);
    connect(reloadAct, SIGNAL(triggered()), this, SLOT(doReload()));

    QPixmap settingpix(":/images/settings.png");
    proxyAct = new QAction(settingpix, tr("&Settings"), this);
    connect(proxyAct, SIGNAL(triggered()), this, SLOT(doProxy()));

    QPixmap aboutpix(":/images/about.png");
    aboutAct = new QAction(aboutpix, tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(doAbout()));

    connect(ui->webView, SIGNAL(linkClicked(QUrl)), this, SLOT( linkClickedSlot( QUrl ) ) );
    connect(ui->webView, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    /* Not next two signals do not work, bug in QT framework */
    //connect(ui->webView, SIGNAL(unsupportedContent(QNetworkRequest)),this, SLOT(download(QNetworkRequest)));
    //connect(ui->webView, SIGNAL(downloadRequested(QNetworkRequest)),this, SLOT(download(QNetworkRequest)));

    initNetwork();

    qWarning("WarQuest Compiled with Qt Version %s", QT_VERSION_STR);

    /*QList<QByteArray> list = QImageReader::supportedImageFormats();

    QList<QByteArray>::iterator i;
    for (i = list.begin(); i != list.end(); ++i) {
        qWarning(*i);
    }*/

    qWarning("WarQuest Started %s", APPL_VERSION);
}

void MainWindow::linkClickedSlot( QUrl url )
{
    qDebug() << "url=" << url;

    QDesktopServices::openUrl( url );
}

void MainWindow::adjustTitle()
{
    // qDebug() << "progress = " << progress;

    if (progress <= 0 || progress >= 100) {
         setWindowTitle(ui->webView->title());

         if (startup==1) {

              ui->progressBar->setValue(progress);

             // Add background image.
             scene = new QGraphicsScene();
             scene->addPixmap(QPixmap(":/images/background1.jpg"));
             ui->graphicsView->setScene(scene);
             ui->graphicsView->setGeometry(0,0, SCREEN_WIDTH+2, 1200);

             ui->progressBar->setVisible(false);
             ui->webView->setVisible(true);

             startup=0;
         }
     } else {
         setWindowTitle(QString("%1 (%2%)").arg(ui->webView->title()).arg(progress));

         if (startup==1) {
               ui->progressBar->setValue(progress);
         }
     }
 }

 void MainWindow::setProgress(int p)
 {
     progress = p;
     adjustTitle();
 }

 void MainWindow::finishLoading(bool)
 {
     progress = 100;
     adjustTitle();
 }

/**
 * Destructor
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * Create popup menu
 */
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(reloadAct);
    menu.addAction(proxyAct);
    menu.addAction(aboutAct);
    menu.exec(event->globalPos());
}

/**
 * Close Window
 */
void MainWindow::closeEvent(QCloseEvent *event) {
   // Store current window position
   writeSettings();
}

/**
 * Setup proxy if enabled
 */
void MainWindow::setProxy()
{
    QSettings qSettings("PlaatSoft", APPL_NAME);

    // Proxy support
    bool enabled = qSettings.value("proxyEnabled",false).toBool();
    QNetworkProxy proxy1;
    if (enabled)
    {
        qDebug() << "Proxy enabled";
        bool ok;
        proxy1.setUser(qSettings.value("loginName","").toString());
        proxy1.setPassword(proxy.decrypt(qSettings.value("password","").toString()));
        proxy1.setPort(qSettings.value("proxyPort","").toString().toInt(&ok, 10));
        proxy1.setHostName(qSettings.value("proxyAddress","").toString());
        proxy1.setType(QNetworkProxy::HttpProxy);
    } else {
        qDebug() << "Proxy disabled";
        proxy1.setType(QNetworkProxy::NoProxy);
    }

    QNetworkProxy::setApplicationProxy(proxy1);
}


/**
 * Read windows position out registry
 */
void MainWindow::readSettings()
{
    // Fetch previous window position
    QSettings settings("PlaatSoft", APPL_NAME);
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    move(pos);
}

/**
 * Write windos position to registry
 */
void MainWindow::writeSettings()
{
    // Store current window position
    QSettings settings("PlaatSoft", APPL_NAME);
    settings.setValue("pos", pos());
}

// ************************************
// User actions
// ************************************

/**
 * About menu event
 */
void  MainWindow::doAbout()
{
    // Set window position related to Main window.
    QPoint position = QPoint(pos());
    position.setX(position.x()+20);
    position.setY(position.y()+350);
    about.move(position);

    // Make about window visible
    about.show();
}

/**
 * Proxy menu event
 */
void  MainWindow::doProxy()
{
    // Set window position related to Main window.
    QPoint position = QPoint(pos());
    position.setX(position.x()+80);
    position.setY(position.y()+350);
    proxy.move(position);
    proxy.readSettings();

    // Make proxy window visible
    proxy.show();
}

/**
 * Reload event
 */
void  MainWindow::doReload()
{
    ui->webView->reload();
    qDebug() << "reload";
}

/**
 * Download event (is not working. Looks like a QT frameware bug)
 */
void MainWindow::download(const QNetworkRequest &request) {
    qDebug() << "download" ;
}

// ------------------------------
// Network
// ------------------------------

/**
 * Start network
 */
void MainWindow::initNetwork(void)
{
   manager = new QNetworkAccessManager(this);

   connect( manager,
         SIGNAL(finished(QNetworkReply*)),
         this,
         SLOT(replyFinished(QNetworkReply*)) );

   fetchVersion();
}

/**
 * Create http request for version data.
 */
void MainWindow::fetchVersion()
{
    qDebug() << "fetchVersion enter";

    QNetworkRequest request;
    request.setUrl(QUrl("http://www.plaatsoft.nl/service/warquest-linux.html"));

    manager->get(request);
    stateMachine=STATE_VERSION_CHECK;

    qDebug() << "fetchVersion leave ";
}

/**
 * Process incoming http response
 */
void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString bytesCount = QString::number( reply->bytesAvailable());
    QString result = reply->readAll();

    qDebug() << bytesCount << "Bytes received ";

   // qDebug() << result;

    switch (stateMachine)
    {
        case STATE_VERSION_CHECK:
        {
            parseVersion(result);
        }
        break;
    }
}

/**
 * Parse data for version information
 */
void MainWindow::parseVersion(QString response)
{
   //qDebug() << response;

   QString text;
   int pos = response.indexOf("Version ");
   if (pos>0) {
        QString version = response.mid(pos+8,4).simplified();
        if ((version.size()>0) && (version.compare(APPL_VERSION)!=0)) {
            text="New version ";
            text+=version;
            text+=" of WarQuest for Windows is available!<br>";
            text+="Check out http://www.plaatsoft.nl for more information";

            QMessageBox::information(this, tr("Software update"),text);
        }
    } else {

        if (newAccount == 1 ) {

            qDebug() << "Remove registry account";

            QSettings qSettings("PlaatSoft", APPL_NAME);
            qSettings.remove("token1");
            qSettings.remove("token2");
        }

        text = "No internet available!";
        QMessageBox::warning(this, tr("Warning"),text);

    }
}

// ************************************
// The end
// ************************************
