#include "port.h"
#include "ui_port.h"

port::port(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::port)
{
    ui->setupUi(this);
}

port::~port()
{
    delete ui;
}
