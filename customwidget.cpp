#include "customwidget.h"
#include "ui_customwidget.h"


CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent), m_ui( new Ui::CustomWidget ) {
    m_ui->setupUi( this );
    this->setAttribute( Qt::WA_QuitOnClose );

    connect( m_ui->m_startBtn, SIGNAL(clicked()), this, SLOT(startThread()) );
    connect( m_ui->m_pauseBtn, SIGNAL(clicked()), this, SLOT(onPause()) );
    connect( m_ui->m_stopBtn, SIGNAL(clicked()), this, SLOT(onStop()) );

    // Qt::DirectConnect
    // The slot is invoked immediately when the signal is emitted.
    // The slot is executed in the signalling thread
    // connect( worker, SIGNAL(resultReady(int)), this, SLOT(handleResult(int)), Qt::DirectConnection );
    connect( &m_workerThread, SIGNAL(resultReady(int)), this, SLOT(handleResult(int)) );
    connect( &m_workerThread, SIGNAL(finished()), this, SLOT(onFinish()) );

    //m_ui->m_processBar->setValue(0);
}

CustomWidget::~CustomWidget() {
    delete m_ui;
}

void CustomWidget::startThread() {
    if ( !m_workerThread.isRunning() ) {
        m_workerThread.start();
        m_ui->m_startBtn->setEnabled( false );
        m_ui->m_pauseBtn->setEnabled( true );
        m_ui->m_stopBtn->setEnabled( true );
    }
}

void CustomWidget::handleResult( int value ) {
    m_ui->m_processBar->setValue( value );
}

void CustomWidget::onStop() {
    if ( m_workerThread.isRunning() ) {
        m_ui->m_startBtn->setEnabled( true );
        m_ui->m_pauseBtn->setEnabled( false );
        m_ui->m_stopBtn->setEnabled( false );
        m_workerThread.stop();
    }
}

void CustomWidget::onPause() {
    if ( m_workerThread.isRunning() ) {
        m_workerThread.pause();
    }
}

void CustomWidget::onFinish() {
    m_ui->m_startBtn->setEnabled( true );
    m_ui->m_pauseBtn->setEnabled( false );
    m_ui->m_stopBtn->setEnabled( false );
}

