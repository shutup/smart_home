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
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QLabel *status_label;
    QLabel *label_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label;
    QLCDNumber *lcdNum_temp;
    QSpinBox *spinBox_temp_min;
    QSpinBox *spinBox_temp_max;
    QPushButton *pushButton_temp_min;
    QPushButton *pushButton_temp_max;
    QLabel *label_2;
    QLCDNumber *lcdNum_humi;
    QSpinBox *spinBox_humi_min;
    QSpinBox *spinBox_humi_max;
    QPushButton *pushButton_humi_min;
    QPushButton *pushButton_humi_max;
    QWidget *tab;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QTextEdit *infoPad;
    QPushButton *pushButton_conn;
    QPushButton *searchButton;
    QPushButton *pushButton_discon;
    QPushButton *pushButton_open_light;
    QPushButton *pushButton;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(505, 436);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 492, 341));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMaximumSize(QSize(492, 341));
        tabWidget->setFocusPolicy(Qt::StrongFocus);
        tabWidget->setAutoFillBackground(false);
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        status_label = new QLabel(tab_3);
        status_label->setObjectName(QString::fromUtf8("status_label"));
        status_label->setGeometry(QRect(430, 280, 36, 14));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(status_label->sizePolicy().hasHeightForWidth());
        status_label->setSizePolicy(sizePolicy1);
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(328, 280, 96, 14));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        layoutWidget = new QWidget(tab_3);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(320, 280, 151, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget1 = new QWidget(tab_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(9, 9, 471, 251));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lcdNum_temp = new QLCDNumber(layoutWidget1);
        lcdNum_temp->setObjectName(QString::fromUtf8("lcdNum_temp"));
        sizePolicy1.setHeightForWidth(lcdNum_temp->sizePolicy().hasHeightForWidth());
        lcdNum_temp->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lcdNum_temp, 1, 0, 1, 1);

        spinBox_temp_min = new QSpinBox(layoutWidget1);
        spinBox_temp_min->setObjectName(QString::fromUtf8("spinBox_temp_min"));
        sizePolicy1.setHeightForWidth(spinBox_temp_min->sizePolicy().hasHeightForWidth());
        spinBox_temp_min->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(spinBox_temp_min, 1, 1, 1, 1);

        spinBox_temp_max = new QSpinBox(layoutWidget1);
        spinBox_temp_max->setObjectName(QString::fromUtf8("spinBox_temp_max"));
        sizePolicy1.setHeightForWidth(spinBox_temp_max->sizePolicy().hasHeightForWidth());
        spinBox_temp_max->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(spinBox_temp_max, 1, 2, 1, 1);

        pushButton_temp_min = new QPushButton(layoutWidget1);
        pushButton_temp_min->setObjectName(QString::fromUtf8("pushButton_temp_min"));
        sizePolicy1.setHeightForWidth(pushButton_temp_min->sizePolicy().hasHeightForWidth());
        pushButton_temp_min->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_temp_min, 2, 1, 1, 1);

        pushButton_temp_max = new QPushButton(layoutWidget1);
        pushButton_temp_max->setObjectName(QString::fromUtf8("pushButton_temp_max"));
        sizePolicy1.setHeightForWidth(pushButton_temp_max->sizePolicy().hasHeightForWidth());
        pushButton_temp_max->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_temp_max, 2, 2, 1, 1);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        lcdNum_humi = new QLCDNumber(layoutWidget1);
        lcdNum_humi->setObjectName(QString::fromUtf8("lcdNum_humi"));
        sizePolicy1.setHeightForWidth(lcdNum_humi->sizePolicy().hasHeightForWidth());
        lcdNum_humi->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lcdNum_humi, 4, 0, 1, 1);

        spinBox_humi_min = new QSpinBox(layoutWidget1);
        spinBox_humi_min->setObjectName(QString::fromUtf8("spinBox_humi_min"));
        sizePolicy1.setHeightForWidth(spinBox_humi_min->sizePolicy().hasHeightForWidth());
        spinBox_humi_min->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(spinBox_humi_min, 4, 1, 1, 1);

        spinBox_humi_max = new QSpinBox(layoutWidget1);
        spinBox_humi_max->setObjectName(QString::fromUtf8("spinBox_humi_max"));
        sizePolicy1.setHeightForWidth(spinBox_humi_max->sizePolicy().hasHeightForWidth());
        spinBox_humi_max->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(spinBox_humi_max, 4, 2, 1, 1);

        pushButton_humi_min = new QPushButton(layoutWidget1);
        pushButton_humi_min->setObjectName(QString::fromUtf8("pushButton_humi_min"));
        sizePolicy1.setHeightForWidth(pushButton_humi_min->sizePolicy().hasHeightForWidth());
        pushButton_humi_min->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_humi_min, 5, 1, 1, 1);

        pushButton_humi_max = new QPushButton(layoutWidget1);
        pushButton_humi_max->setObjectName(QString::fromUtf8("pushButton_humi_max"));
        sizePolicy1.setHeightForWidth(pushButton_humi_max->sizePolicy().hasHeightForWidth());
        pushButton_humi_max->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_humi_max, 5, 2, 1, 1);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        gridLayout_3 = new QGridLayout(tab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 0, 1, 1);

        infoPad = new QTextEdit(tab);
        infoPad->setObjectName(QString::fromUtf8("infoPad"));

        gridLayout_3->addWidget(infoPad, 1, 0, 1, 3);

        pushButton_conn = new QPushButton(tab);
        pushButton_conn->setObjectName(QString::fromUtf8("pushButton_conn"));

        gridLayout_3->addWidget(pushButton_conn, 2, 1, 1, 1);

        searchButton = new QPushButton(tab);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));

        gridLayout_3->addWidget(searchButton, 2, 2, 1, 1);

        pushButton_discon = new QPushButton(tab);
        pushButton_discon->setObjectName(QString::fromUtf8("pushButton_discon"));

        gridLayout_3->addWidget(pushButton_discon, 3, 1, 1, 1);

        pushButton_open_light = new QPushButton(tab);
        pushButton_open_light->setObjectName(QString::fromUtf8("pushButton_open_light"));

        gridLayout_3->addWidget(pushButton_open_light, 2, 0, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout_3->addWidget(pushButton, 3, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(43, 361, 441, 31));
        QFont font;
        font.setPointSize(14);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 505, 25));
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
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "SMART HOME CLIENT", 0, QApplication::UnicodeUTF8));
        status_label->setText(QApplication::translate("MainWindow", "\346\234\252\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\350\277\236\346\216\245\347\212\266\346\200\201\357\274\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246", 0, QApplication::UnicodeUTF8));
        pushButton_temp_min->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\234\200\345\260\217\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton_temp_max->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\234\200\345\244\247\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\346\271\277\345\272\246", 0, QApplication::UnicodeUTF8));
        pushButton_humi_min->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\234\200\345\260\217\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
        pushButton_humi_max->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\346\234\200\345\244\247\351\230\200\345\200\274", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "\347\212\266\346\200\201\346\230\276\347\244\272", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
        pushButton_conn->setText(QApplication::translate("MainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        searchButton->setText(QApplication::translate("MainWindow", "\346\237\245\346\211\276\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        pushButton_discon->setText(QApplication::translate("MainWindow", "\346\226\255\345\274\200\346\234\215\345\212\241\345\231\250", 0, QApplication::UnicodeUTF8));
        pushButton_open_light->setText(QApplication::translate("MainWindow", "\345\274\200\347\201\257", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "\345\205\263\347\201\257", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\345\221\275\344\273\244\346\265\213\350\257\225", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "\346\231\272\350\203\275\345\256\266\345\272\255 PC\347\253\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
