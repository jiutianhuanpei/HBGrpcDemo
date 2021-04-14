#include "HBClient.h"
#include "ui_HBClient.h"
#include <QRegExpValidator>
#include "../Common/MsgCenter.h"

using SHB::MessageType;

HBClient::HBClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HBClient)
{
    ui->setupUi(this);

    QRegExp exp("[0-9]*");
    QRegExpValidator *reg = new QRegExpValidator(exp, this);
    ui->lineEdit->setValidator(reg);

    if (m_simClient == nullptr) {
        m_simClient = new SimpleClient(hb_hostStr.toStdString());

    }

    connect(MsgCenter::shareInstance(), &MsgCenter::signal_didReceivedMessage, [&](HBResponse response) {

       QString msg;
       if (response.type() == MessageType::Chat_Msg) {
           msg = "对单消息：" + QString::fromStdString(response.data());
       } else if (response.type() == MessageType::Group_Msg) {
           msg = "流消息：" + QString::fromStdString(response.data());
       } else if (response.type() == MessageType::Push_Msg) {
           msg = "信令消息：" + QString::fromStdString(response.data());
       }


       ui->textBrowser->append("收到" + msg);
    });
}

HBClient::~HBClient()
{
    delete ui;
}


void HBClient::on_pBtn1V1_clicked()
{

    HBRequest request;
    request.set_phone(ui->phone_lineEdit->text().toStdString());
    request.set_data(ui->lineEdit->text().toStdString());

    bool ret = m_simClient->sendMsg(request);
    if (ret)
        ui->textBrowser->insertPlainText("\n发送成功");
    else
        ui->textBrowser->insertPlainText("\n发送失败");
}

void HBClient::on_pBtnStream_clicked()
{
    HBRequest request;
    request.set_phone(ui->phone_lineEdit->text().toStdString());
    request.set_data(ui->lineEdit_2->text().toStdString());


     m_simClient->sendStreamMsg(request);

     ui->textBrowser->insertPlainText("\n发送成功");
}

void HBClient::on_pBtnPush_clicked()
{

}
