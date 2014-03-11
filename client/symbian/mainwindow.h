#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <qsystemdeviceinfo.h>

QTM_USE_NAMESPACE

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    // Note that this will only have an effect on Symbian and Fremantle.
    void setOrientation(ScreenOrientation orientation);

    void showExpanded();

private slots:

     // User action methods
     void setProgress(int p);
     void finishLoading(bool);

private:
    Ui::MainWindow *ui;
    QSystemDeviceInfo* deviceInfo;
    QGraphicsScene *scene;
    int progress;
    int startup;

    void adjustTitle();
};

#endif // MAINWINDOW_H
