#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include "workerthread.h"

namespace Ui {
class CustomWidget;
}

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);
    ~CustomWidget();

private slots:
    void startThread();
    void handleResult( int value );
    void onStop();
    void onPause();
    void onFinish();

private:
    Ui::CustomWidget *m_ui;
    WorkerThread m_workerThread;
};

#endif // CUSTOMWIDGET_H
