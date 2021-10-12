#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
void serialReceived();
private slots:
//    void on_pushButton_clicked();

    void on_on_actionclear_triggered_triggered();

    void on_on_actionA_k_triggered_triggered();

    void on_on_actionKapat_triggered_triggered();

    void on_on_actionAyarlar_triggered_triggered();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
    QSerialPort *loadcellPort;
};
#endif // MAINWINDOW_H
