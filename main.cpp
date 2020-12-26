#include <QApplication>
#include <QDebug>
#include <QThread>
#include "customwidget.h"

////// sub-class QThread
//class WorkerThread : public QThread {
//    Q_OBJECT
//public:
//    void run() {
//        qDebug() << currentThreadId();
//        emit resultReady();
//    }

//signals:
//    void resultReady();
//};

int main( int argc, char **argv ) {
    QApplication app( argc, argv );
    CustomWidget worker;
    worker.show();
    //worker.wait();
    return app.exec();
}

#include "main.moc"
