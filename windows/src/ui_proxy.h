/********************************************************************************
** Form generated from reading UI file 'proxy.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROXY_H
#define UI_PROXY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

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
            Proxy->setObjectName(QStringLiteral("Proxy"));
        Proxy->resize(400, 249);
        groupBox_2 = new QGroupBox(Proxy);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 110, 381, 101));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(14, 19, 62, 16));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(13, 57, 97, 16));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(200, 20, 124, 16));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(200, 59, 70, 16));
        LoginNameEdit = new QLineEdit(groupBox_2);
        LoginNameEdit->setObjectName(QStringLiteral("LoginNameEdit"));
        LoginNameEdit->setGeometry(QRect(12, 34, 169, 20));
        LoginNameEdit->setMaxLength(20);
        passwordEdit = new QLineEdit(groupBox_2);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setGeometry(QRect(12, 72, 168, 20));
        passwordEdit->setMaxLength(20);
        passwordEdit->setEchoMode(QLineEdit::Password);
        proxyAddressEdit = new QLineEdit(groupBox_2);
        proxyAddressEdit->setObjectName(QStringLiteral("proxyAddressEdit"));
        proxyAddressEdit->setGeometry(QRect(199, 35, 161, 20));
        proxyAddressEdit->setMaxLength(50);
        proxyPortEdit = new QLineEdit(groupBox_2);
        proxyPortEdit->setObjectName(QStringLiteral("proxyPortEdit"));
        proxyPortEdit->setGeometry(QRect(199, 73, 161, 20));
        proxyPortEdit->setMaxLength(5);
        enabledCheckBox = new QCheckBox(groupBox_2);
        enabledCheckBox->setObjectName(QStringLiteral("enabledCheckBox"));
        enabledCheckBox->setGeometry(QRect(115, 13, 70, 17));
        cancelButton = new QPushButton(Proxy);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setGeometry(QRect(220, 220, 75, 23));
        OkButton = new QPushButton(Proxy);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setGeometry(QRect(310, 220, 75, 23));
        groupBox = new QGroupBox(Proxy);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 381, 91));
        username2 = new QLineEdit(groupBox);
        username2->setObjectName(QStringLiteral("username2"));
        username2->setGeometry(QRect(10, 40, 158, 20));
        username2->setMaxLength(17);
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 20, 124, 16));
        password2 = new QLineEdit(groupBox);
        password2->setObjectName(QStringLiteral("password2"));
        password2->setGeometry(QRect(200, 40, 160, 20));
        password2->setMaxLength(17);
        password2->setEchoMode(QLineEdit::Password);
        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(200, 20, 70, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 70, 371, 21));

        retranslateUi(Proxy);

        QMetaObject::connectSlotsByName(Proxy);
    } // setupUi

    void retranslateUi(QWidget *Proxy)
    {
        Proxy->setWindowTitle(QApplication::translate("Proxy", "Form", 0));
        groupBox_2->setTitle(QApplication::translate("Proxy", "HTTP Proxy settings", 0));
        label_3->setText(QApplication::translate("Proxy", "Proxy Login", 0));
        label_4->setText(QApplication::translate("Proxy", "Proxy Password", 0));
        label_5->setText(QApplication::translate("Proxy", "Proxy Address", 0));
        label_6->setText(QApplication::translate("Proxy", "Proxy Port", 0));
        enabledCheckBox->setText(QApplication::translate("Proxy", "Enabled", 0));
        cancelButton->setText(QApplication::translate("Proxy", "Cancel", 0));
        OkButton->setText(QApplication::translate("Proxy", "Ok", 0));
        groupBox->setTitle(QApplication::translate("Proxy", "General", 0));
        label_11->setText(QApplication::translate("Proxy", "Username", 0));
        label_12->setText(QApplication::translate("Proxy", "Password", 0));
        label->setText(QApplication::translate("Proxy", "Only change above settings if you want to use an other WarQuest account!", 0));
    } // retranslateUi

};

namespace Ui {
    class Proxy: public Ui_Proxy {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROXY_H
