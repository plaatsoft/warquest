#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>
#include <QtGui>
#include <QtNetwork>

#define APPL_NAME             "WarQuest"
#define APPL_VERSION          "1.0"
#define APPL_URL              "http://www.warquest.nl/"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Screen correct screen size */
    QRect rect =  geometry();

    rect.setTop(-2);    
    rect.setLeft(-2);
    rect.setWidth(rect.width()+2);
    rect.setHeight(rect.height()+2);

    // Add background screen
    scene = new QGraphicsScene();
    QPixmap image = QPixmap(":/images/background.jpg");
    scene->addPixmap(image);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setGeometry(rect);

    ui->progressBar->setValue(0);

    ui->webView->setContextMenuPolicy(Qt::NoContextMenu);
    ui->webView->setVisible(false);
    ui->title->setVisible(false);

    QFont font = ui->title->font();
    font.setPixelSize(14);
    ui->title->setFont(font);
    startup=1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif

    /* Screen correct screen size */
    QRect rect = geometry();
    rect.setTop(-2);
    rect.setBottom(30);
    ui->title->setGeometry(rect);

    rect = geometry();
    rect.setTop(30);
    rect.setHeight(rect.height());

    float factor;
    switch (rect.width()) {

        case 480: factor = 0.88;
                  break;

        case 360: factor = 0.64;
                  break;

        default:  factor = geometry().width()/540.0;
                  break;
    }

    qDebug( "factor = %f", factor );
    qDebug( "top = %d", geometry().top() );

    ui->webView->setZoomFactor(factor);
    ui->webView->setGeometry(rect);
    ui->webView->settings()->setAttribute(QWebSettings::JavascriptEnabled, true);

    // Get direct sign-on information from registry.
    QSettings qSettings("PlaatSoft", APPL_NAME);
    QString token1 = qSettings.value("token1", "").toString();
    QString token2 = qSettings.value("token2", "").toString();
    QString eventId;

    qDebug() << "URL=" << QUrl(APPL_URL);

    qDebug() << "IMEI=" << deviceInfo->imei();
    qDebug() << "IMSI=" << deviceInfo->imsi();
    qDebug() << "MODEL=" << deviceInfo->model();

    if (token1.length()==0 ) {

       // Create unique token.
       QDateTime now = QDateTime::currentDateTime();
       token1 = now.toString("yyyyMMddhhmmssz");
       token1 = deviceInfo->imei();
       token2 = token1;

       // Save tokens in windows registry
       qSettings.setValue("token1",  token1);
       qSettings.setValue("token2",  token2);

       // Set Register and Login event
       eventId = "2";

    } else if ((token1.length()!=0) && (token2.length()!=0)) {

       // Login directly
       eventId = "1";
    }

    qDebug() << "applName =" << APPL_NAME;
    qDebug() << "version =" << APPL_VERSION;
    qDebug() << "token1 =" << token1;
    qDebug() << "token2 =" << token2;
    qDebug() << "eventId =" << eventId;

    // Send html request to warquest website.
    QNetworkRequest request(QUrl(APPL_URL));
    request.setRawHeader("username", token1.toAscii());
    request.setRawHeader("password", token2.toAscii());
    request.setRawHeader("eid", eventId.toAscii());
    request.setRawHeader("version", APPL_VERSION);
    ui->webView->load(request, QNetworkAccessManager::PostOperation);

    connect(ui->webView, SIGNAL(loadProgress(int)), SLOT(setProgress(int)));
    connect(ui->webView, SIGNAL(loadFinished(bool)), SLOT(finishLoading(bool)));

    ui->title->setText(APPL_NAME);
}

void MainWindow::adjustTitle()
{
    if (progress <= 0 || progress >= 100) {

        ui->title->setText(ui->webView->title());

        if (startup==1) {

            ui->progressBar->setValue(100);
            ui->progressBar->setVisible(false);
            ui->webView->setVisible(true);
            ui->title->setVisible(true);
            ui->graphicsView->setVisible(false);

            startup=0;
        }
       } else {
        if (ui->webView->title().length()>0) {
           ui->title->setText(QString("%1 (%2%)").arg(ui->webView->title()).arg(progress));
        } else {
            ui->title->setText(QString("%1 (%2%)").arg(APPL_NAME).arg(progress));
        }
        ui->progressBar->setValue(progress);
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
