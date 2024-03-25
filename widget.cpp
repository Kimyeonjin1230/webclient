#include "widget.h"
#include "ui_widget.h"
#include "qabstractsocket.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    socket_.readyRead();
    QObject::connect(&socket_, &QAbstractSocket::connected,this,&Widget::doConnected);
    QObject::connect(&socket_, &QAbstractSocket::disconnected,this,&Widget::disConnected);
    QObject::connect(&socket_, &QAbstractSocket::readyRead,this,&Widget::doReadyRead);

}

Widget::~Widget()
{
    delete ui;
}
void Widget::doConnected(){
    QString msg = "Connected to" + socket_.peerAddress().toString() + "\r\n";
    ui->pteMessage->insertPlainText(msg);
}
void Widget::disConnected(){
    QString msg = "Disconnected to " + socket_.peerAddress().toString() + "\r\n";
    ui->pteMessage->insertPlainText(msg);
}

void Widget::doReadyRead(){
    QByteArray ba = socket_.readAll();
    ui->pteMessage->insertPlainText(ba);
}
void Widget::on_pbConnect_clicked(){
    //ssl
    //socket_.connectToHost(ui->leHost->text(), ui->lePort->text().toUShort());
    socket_.connectToHostEncrypted(ui->leHost->text(), ui->lePort->text().toUShort());


}


void Widget::on_pbDisconnect_clicked()
{
    socket_.close();
}


void Widget::on_pbSend_clicked()
{
    socket_.write(ui->pteSend->toPlainText().toUtf8());
    //Utff8 :  return bytearray
}

void Widget::on_pbClear_clicked()
{
    ui -> pteMessage -> clear();
}
