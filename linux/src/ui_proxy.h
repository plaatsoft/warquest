/********************************************************************************
** Form generated from reading UI file 'proxy.ui'
**
** Created: Sun Jun 3 21:17:41 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROXY_H
#define UI_PROXY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Proxy
{
public:
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *LoginNameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *proxyAddressEdit;
    QLineEdit *proxyPortEdit;
    QCheckBox *enabledCheckBox;
    QPushButton *cancelButton;
    QPushButton *OkButton;
    QGroupBox *groupBox;
    QLineEdit *username2;
    QLabel *label_11;
    QLineEdit *password2;
    QLabel *label_12;
    QLabel *label;

    void setupUi(QWidget *Proxy)
    {
        if (Proxy->objectName().isEmpty())
            Proxy->setObjectName(QString::fromUtf8("Proxy"));
        Proxy->resize(400, 249);
        groupBox_2 = new QGroupBox(Proxy);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 110, 381, 111));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 20, 161, 16));
        QFont font;
        font.setPointSize(10);
        label_3->setFont(font);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 60, 161, 16));
        label_4->setFont(font);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(200, 20, 161, 16));
        label_5->setFont(font);
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(200, 60, 151, 16));
        label_6->setFont(font);
        LoginNameEdit = new QLineEdit(groupBox_2);
        LoginNameEdit->setObjectName(QString::fromUtf8("LoginNameEdit"));
        LoginNameEdit->setGeometry(QRect(10, 40, 169, 20));
        LoginNameEdit->setMaxLength(20);
        passwordEdit = new QLineEdit(groupBox_2);
        passwordEdit->setObjectName(QString::fromUtf8("passwordEdit"));
        passwordEdit->setGeometry(QRect(10, 80, 168, 20));
        passwordEdit->setMaxLength(20);
        passwordEdit->setEchoMode(QLineEdit::Password);
        proxyAddressEdit = new QLineEdit(groupBox_2);
        proxyAddressEdit->setObjectName(QString::fromUtf8("proxyAddressEdit"));
        proxyAddressEdit->setGeometry(QRect(200, 40, 161, 20));
        proxyAddressEdit->setMaxLength(50);
        proxyPortEdit = new QLineEdit(groupBox_2);
        proxyPortEdit->setObjectName(QString::fromUtf8("proxyPortEdit"));
        proxyPortEdit->setGeometry(QRect(200, 80, 161, 20));
        proxyPortEdit->setMaxLength(5);
        enabledCheckBox = new QCheckBox(groupBox_2);
        enabledCheckBox->setObjectName(QString::fromUtf8("enabledCheckBox"));
        enabledCheckBox->setGeometry(QRect(300, 0, 81, 17));
        enabledCheckBox->setFont(font);
        cancelButton = new QPushButton(Proxy);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(220, 220, 75, 23));
        OkButton = new QPushButton(Proxy);
        OkButton->setObjectName(QString::fromUtf8("OkButton"));
        OkButton->setGeometry(QRect(310, 220, 75, 23));
        groupBox = new QGroupBox(Proxy);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 381, 91));
        username2 = new QLineEdit(groupBox);
        username2->setObjectName(QString::fromUtf8("username2"));
        username2->setGeometry(QRect(10, 40, 158, 20));
        username2->setMaxLength(17);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 20, 124, 16));
        label_11->setFont(font);
        password2 = new QLineEdit(groupBox);
        password2->setObjectName(QString::fromUtf8("password2"));
        password2->setGeometry(QRect(200, 40, 160, 20));
        password2->setMaxLength(17);
        password2->setEchoMode(QLineEdit::Password);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(200, 20, 171, 16));
        label_12->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 70, 371, 21));
        QFont font1;
        font1.setPointSize(8);
        label->setFont(font1);

        retranslateUi(Proxy);

        QMetaObject::connectSlotsByName(Proxy);
    } // setupUi

    void retranslateUi(QWidget *Proxy)
    {
        Proxy->setWindowTitle(QApplication::translate("Proxy", "Form", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("Proxy", "HTTP Proxy settings", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Proxy", "Proxy Login", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Proxy", "Proxy Password", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Proxy", "Proxy Address", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Proxy", "Proxy Port", 0, QApplication::UnicodeUTF8));
        enabledCheckBox->setText(QApplication::translate("Proxy", "Enabled", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("Proxy", "Cancel", 0, QApplication::UnicodeUTF8));
        OkButton->setText(QApplication::translate("Proxy", "Ok", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Proxy", "General", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Proxy", "Username", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("Proxy", "Password", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Proxy", "Only change above settings if you want to use an other WarQuest account!", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Proxy: public Ui_Proxy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROXY_H
