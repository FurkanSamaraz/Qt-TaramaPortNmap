#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QtConcurrent>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QSortFilterProxyModel>
#include <QSerialPortInfo>
#include <QDirModel>
#include <QScrollBar>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->results->setMaximumWidth(maximumHeight());

    QPalette p = palette();
    p.setColor(QPalette::Base, Qt::black);
    p.setColor(QPalette::Text, Qt::green);
    setPalette(p);



    QSerialPort   *serial = new QSerialPort(this);

           qDebug()<<    serial->open(QIODevice::ReadOnly);
           serial->setBaudRate(QSerialPort::Baud9600, QSerialPort::AllDirections);
           serial->setDataBits(QSerialPort::Data8);
           serial->setParity(QSerialPort::NoParity);
           serial->setStopBits(QSerialPort::OneStop);
           serial->setFlowControl(QSerialPort::NoFlowControl);

           connect(serial,SIGNAL(readyRead()),this,SLOT(serialReceived()));
           if (serial->isOpen()) {
               qDebug() << "Serial port is open...";
               QByteArray datas = serial->readLine();
               if (datas.size() == 0) {
                   qDebug() << "Arrived data: 0";
               } else {
                   for (int i = 0; i < datas.size(); i++){
                       if (datas.at(i)) {
                           qDebug() << datas[i];
                       }
                   }
               }

           } else {
               qDebug() << "HATA: " << serial->errorString();
           }

           serial->close();
           qDebug() << "...serial port kapandı!";

           //seri bağlantı sayısı
           qDebug() << "Seri bağlantı port sayısı:" << QSerialPortInfo::availablePorts().count();
        ui->lcdNumber->display( QSerialPortInfo::availablePorts().count());





}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_on_actionclear_triggered_triggered()
{
    ui->results->clear();
    QMessageBox::information(this,"...","Silinme Başarılı");
}

void MainWindow::on_on_actionA_k_triggered_triggered()
{

    ui->results->setText("");
    QString host = ui ->lineEditHost->text();
    QString startPort = ui ->lineEditStartPort->text();
    quint16 startPortInt = startPort.toUShort();
    QString endPort = ui ->lineEditEndPort->text();
    quint16 endPortInt = endPort.toUShort();
    QString timeout = ui ->lineEditTimeout->text();
    quint16 timeoutInt = timeout.toUShort();
    qInfo() << host;
    QTcpSocket socket;
    qInfo() <<startPort ;


    QElapsedTimer timer;
       timer.start();
QFuture<void> future = QtConcurrent::run([=]() {
      QTcpSocket socket;
    for(quint16 i = startPortInt; i < endPortInt; i++){

            socket.connectToHost(host, i);
            if(socket.waitForConnected(timeoutInt)){
                qInfo() << "Acik Port: " << i;


                QString openPort = QString::number(i);
                ui->results->append("Açık Port: " + openPort);
                socket.disconnectFromHost();
                 QApplication::processEvents();
            }

    }

    ui->results->append("Tarama Tamamlandı.");
   qInfo() << "Tarama Tamamlandı.";
   timer.clockType();
   int a = timer.elapsed();
   QString b = QString::number(a);
   ui->results->append("Tarama Süresi: " +b +" ms");
   qInfo() <<"Tarama Süresi"<<a << "ms";


});

QSerialPort   *serial = new QSerialPort(this);
    serial->setPortName(host);


}

void MainWindow::on_on_actionKapat_triggered_triggered()
{

    QApplication::quit();
}

void MainWindow::on_on_actionAyarlar_triggered_triggered()
{

}

void MainWindow::serialReceived()
{

    QByteArray data;
     data=serial->readAll();
 ui->label->setText(data);

}

