/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *lblPattern;
    QLabel *lblTo;
    QLineEdit *txtPattern;
    QLineEdit *txtDesiredPattern;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        lblPattern = new QLabel(centralwidget);
        lblPattern->setObjectName(QString::fromUtf8("lblPattern"));
        lblPattern->setGeometry(QRect(30, 100, 84, 23));
        lblTo = new QLabel(centralwidget);
        lblTo->setObjectName(QString::fromUtf8("lblTo"));
        lblTo->setGeometry(QRect(30, 140, 84, 23));
        lblTo->setMidLineWidth(-10);
        lblTo->setTextFormat(Qt::PlainText);
        txtPattern = new QLineEdit(centralwidget);
        txtPattern->setObjectName(QString::fromUtf8("txtPattern"));
        txtPattern->setGeometry(QRect(150, 100, 621, 31));
        txtDesiredPattern = new QLineEdit(centralwidget);
        txtDesiredPattern->setObjectName(QString::fromUtf8("txtDesiredPattern"));
        txtDesiredPattern->setGeometry(QRect(150, 140, 621, 31));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lblPattern->setText(QCoreApplication::translate("MainWindow", "Pattern", nullptr));
        lblTo->setText(QCoreApplication::translate("MainWindow", "To", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
