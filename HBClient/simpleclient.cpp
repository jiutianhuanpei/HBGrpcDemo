#include "simpleclient.h"
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include "../Common/MsgCenter.h"

SimpleClient::SimpleClient(std::string host)
{

    std::shared_ptr<Channel> channel = grpc::CreateChannel(host, grpc::InsecureChannelCredentials());
    stub_ = HBService::NewStub(channel);

    m_stream = stub_->streamRequest(&context);

    m_receivedStreamMsgCallback();
}

bool SimpleClient::sendMsg(HBRequest request)
{
    HBResponse response;
    ClientContext context;
    Status status = stub_->request(&context, request, &response);

    if (status.ok()) {
        qDebug() << "发送消息成功: " << QString::fromStdString(response.from()) << QString::fromStdString(response.data());
        emit MsgCenter::shareInstance()->signal_didReceivedMessage(response);
        return true;
    }

    qDebug() << "发送消息失败";
    return false;
}

void SimpleClient::sendStreamMsg(HBRequest request)
{

    qDebug() << "Will send stream msg: " << QString::fromStdString(request.phone()) << QString::fromStdString(request.data());

    qDebug() << "Stream: " << &m_stream;
    m_stream->Write(request);

}

void SimpleClient::m_receivedStreamMsgCallback()
{
    std::thread th([&]{

        qDebug() << "In thread";
        HBResponse response;
        while (m_stream->Read(&response)) {
            emit MsgCenter::shareInstance()->signal_didReceivedMessage(response);

        }
    });
    th.detach();
}






