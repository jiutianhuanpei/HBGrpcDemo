#include "HBService.h"
#include "ui_HBService.h"
#include <QDebug>
#include "../Common/MsgCenter.h"

HBService::HBService(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HBService)
{
    ui->setupUi(this);
}

HBService::~HBService()
{
    delete ui;
}


void HBService::on_pBtnone2one_clicked()
{
    if (m_simService == nullptr) {
        m_simService = new SimpleService();
        connect(MsgCenter::shareInstance(), &MsgCenter::signal_didReceived1v1Msg, this, &HBService::slot_didReceived1v1);
        connect(MsgCenter::shareInstance(), &MsgCenter::signal_didReceivedStreamMsg, this, &HBService::slot_didReceivedStream);
    }

    m_simService->RunService(hb_hostStr.toStdString());
    ui->textBrowser->append("启动服务");
}

void HBService::on_pBtnStream_clicked()
{

    m_simService->pushMsgToClient(ui->lineEdit->text().toStdString());

}

void HBService::on_pBtnStreamGlobal_clicked()
{
    m_simService->pushMsgForGlobal();
}


void HBService::slot_didReceived1v1(HBRequest request)
{
    QString str = QString("收到1v1消息： %1\n").arg(QString::fromStdString(request.data()));
    ui->textBrowser->append(str);
}

void HBService::slot_didReceivedStream(HBRequest request)
{
    QString str = QString("收到流消息： %1\n").arg(QString::fromStdString(request.data()));
    ui->textBrowser->append(str);
}
