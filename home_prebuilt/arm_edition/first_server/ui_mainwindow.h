/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *status;
    QVBoxLayout *verticalLayout_2;
    QTableView *data_table;
    QHBoxLayout *horizontalLayout;
    QPushButton *freshButton;
    QPushButton *testButton;
    QWidget *control;
    QVBoxLayout *verticalLayout;
    QTextEdit *infoPad;
    QPushButton *startBtn;
    QPushButton *stopBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(686, 397);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 625, 61));
        QFont font1;
        font1.setPointSize(16);
        label->setFont(font1);
        label->setAlignment(Qt::AlignCenter);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 80, 671, 271));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        status = new QWidget();
        status->setObjectName(QString::fromUtf8("status"));
        verticalLayout_2 = new QVBoxLayout(status);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        data_table = new QTableView(status);
        data_table->setObjectName(QString::fromUtf8("data_table"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(data_table->sizePolicy().hasHeightForWidth());
        data_table->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(data_table);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        freshButton = new QPushButton(status);
        freshButton->setObjectName(QString::fromUtf8("freshButton"));
        sizePolicy2.setHeightForWidth(freshButton->sizePolicy().hasHeightForWidth());
        freshButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(freshButton);

        testButton = new QPushButton(status);
        testButton->setObjectName(QString::fromUtf8("testButton"));
        sizePolicy2.setHeightForWidth(testButton->sizePolicy().hasHeightForWidth());
        testButton->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(testButton);


        verticalLayout_2->addLayout(horizontalLayout);

        tabWidget->addTab(status, QString());
        control = new QWidget();
        control->setObjectName(QString::fromUtf8("control"));
        verticalLayout = new QVBoxLayout(control);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        infoPad = new QTextEdit(control);
        infoPad->setObjectName(QString::fromUtf8("infoPad"));

        verticalLayout->addWidget(infoPad);

        startBtn = new QPushButton(control);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));

        verticalLayout->addWidget(startBtn);

        stopBtn = new QPushButton(control);
        stopBtn->setObjectName(QString::fromUtf8("stopBtn"));

        verticalLayout->addWidget(stopBtn);

        tabWidget->addTab(control, QString());
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 686, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SMART HOME SERVER", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\346\231\272\350\203\275\345\256\266\345\272\255\347\273\210\347\253\257", 0, QApplication::UnicodeUTF8));
        freshButton->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", 0, QApplication::UnicodeUTF8));
        testButton->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(status), QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        startBtn->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\347\233\221\345\220\254", 0, QApplication::UnicodeUTF8));
        stopBtn->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\347\233\221\345\220\254", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(control), QApplication::translate("MainWindow", "Control", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
