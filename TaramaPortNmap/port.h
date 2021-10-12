#ifndef PORT_H
#define PORT_H

#include <QWidget>

namespace Ui {
class port;
}

class port : public QWidget
{
    Q_OBJECT

public:
    explicit port(QWidget *parent = nullptr);
    ~port();

private slots:

     // void serialReceived();
private:
    Ui::port *ui;
};

#endif // PORT_H
