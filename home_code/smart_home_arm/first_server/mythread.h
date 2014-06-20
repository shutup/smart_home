#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QString>
#include "utils.h"
#include <QDebug>
class MyThread : public QThread
{
    Q_OBJECT
//public:
//    explicit MyThread(QObject *parent = 0);
public:
    MyThread();

protected:
    void run();
private:
    QString msg;
signals:

    void engineForward();
    void engineBackward();
    void engineStop();
    void openBuzzer();
    void closeBuzzer();
    void valueOfTemp(char);
    void valueOfHum(char);

public slots:
    void setData(QString msg);
};

#endif // MYTHREAD_H
