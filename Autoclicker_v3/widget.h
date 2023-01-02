#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QMenu>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QDebug>
#include <QRegExpValidator>
#include <QSizePolicy>
#include <QObject>
#include <xdo.h>
#include <iostream>
#include <QTextStream>
#include <QShortcut>
#include <QSignalMapper>
#include <xdo.h>
#include <qthread.h>
#include <QFuture>
#include <QThread>
extern "C" {
#include <xdo.h>
}

class QGroupBox;

class WorkerThread : public QThread {
    Q_OBJECT
    void run() {
        while(1) {
              //qInfo() << "test1";
              emit progressChanged("Some info");
        }
    }
    // Define signal:
    signals:
    void progressChanged(QString info);
};

class Window1 : public QWidget
{
    Q_OBJECT
private slots:
    void *debug(){
        interval = 100;
        interval = msecs + secs
                + mins + hours;
        rep_num = repeat.toShort();
        qInfo() << rep_num  << ", " << ct
                << ", " << btn << ", " << interval;
        return 0;
    }
    void *stup(){
        qInfo() << "Stop";
        return 0;
    }
    void *changevalue(QString val){
        Window1::repeat = val;
        Window1::rep_test = val;
        return 0;
    }
    void *changetozero(){
        Window1::repeat = "0";
        return 0;
    }
    void *changetovar(){
        Window1::repeat = rep_test;
        return 0;
    }
    void *changebutton(QString b){
        btn = b;
        return 0;
    }
    void *changeclicktype(QString c){
        ct = c;
        return 0;
    }
    void *set_interval_h(QString val){
        Window1::hours = 0;
        Window1::hours += (val.toShort()*3600000);
        return 0;
    }
    void *set_interval_m(QString val){
        Window1::mins = 0;
        Window1::mins += (val.toShort()*60000);
        return 0;
    }
    void *set_interval_s(QString val){
        Window1::secs = 0;
        Window1::secs += (val.toShort()*1000);
        return 0;
    }
    void *set_interval_mi(QString val){
        Window1::msecs = 0;
        Window1::msecs += val.toShort();
        return 0;
    }
    void play(){
#define CURRENTWINDOW (0)
xdo_t *xdoMain = xdo_new(NULL);
xdoMain = xdo_new(NULL);
for (int i = 1; i <= rep_num or i == 0; i++)
{
    qint8 b = 1;
    //The mouse button. Generally, 1 is left, 2 is middle, 3 is
    //right, 4 is wheel up, 5 is wheel down.
    if(btn == "Left"){
        b = 1;
     }else if(btn == "Right"){
        b = 3;
    }
    if(ct == "Single"){
        qInfo() << "test1";
        xdo_mouse_down(xdoMain,0, b);
        xdo_mouse_up(xdoMain,0, b);
        qInfo() << "test2";
    } else if(ct == "Double"){
        xdo_mouse_down(xdoMain,0, b);
        xdo_mouse_up(xdoMain,0, b);
        xdo_mouse_down(xdoMain,0, b);
        xdo_mouse_up(xdoMain,0, b);
    }
    QThread::msleep(interval);
}
    xdo_free(xdoMain);
    qInfo() << "test3";
}
    void startWorkInAThread() {
        // Create an instance of your woker
        WorkerThread *workerThread = new WorkerThread;
        // Connect our signal and slot
        connect(workerThread, SIGNAL(progressChanged(QString)), SLOT(play()));
        // Setup callback for cleanup when it finishes
        connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
        // Run, Forest, run!
        workerThread->start(); // This invokes WorkerThread::run in a new thread
    }
public:
     Window1(QWidget *parent = nullptr);
public:
     QGroupBox *createClickIntervalGroup();
     QGroupBox *createClickOptionsGroup();
     QGroupBox *createClickRepeat();
     QGroupBox *createBottomButtons();
     QString repeat = "0";

     QString rep_test="0";
     QString r2_v;
     QPushButton *Start = new QPushButton();
     QPushButton *Stop = new QPushButton();
     QPushButton *Debug = new QPushButton();
     QShortcut *shortcut;
     QShortcut *shortcut2;
     QShortcut *shortcut3;

     unsigned int msecs = 100;
     unsigned int secs = 0;
     unsigned int mins = 0;
     unsigned int hours = 0;
     inline static QString ct="Single";
     inline static QString btn = "Left";
     inline static unsigned int interval;
     inline static qint16 rep_num;
};



#endif
