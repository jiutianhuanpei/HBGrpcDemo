#include "simpleservice.h"
#include <QDebug>
#include "../Common/MsgCenter.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>

using std::chrono::system_clock;
using SHB::MessageType;

SimpleService::SimpleService()
{

}


grpc::Status SimpleService::request(grpc::ServerContext *context, const HBRequest *request, HBResponse *response)
{

    Q_UNUSED(context);
//    emit signal_didReceivedMsg(88);
    qDebug() << "DidReceiveHBService: " << QString::fromStdString(request->phone()) << QString::fromStdString(request->data());

    MsgCenter::shareInstance()->signal_didReceived1v1Msg(*request);

    response->set_from(request->phone());
    response->set_data(request->data() + "  From server!");
    response->set_type(MessageType::Chat_Msg);


    return Status::OK;
}




grpc::Status SimpleService::streamRequest(grpc::ServerContext *context, ::grpc::ServerReaderWriter<SHB::HBResponse, SHB::HBRequest> *stream)
{
    Q_UNUSED(context);

    qDebug() << "Stream request did received";


    HBRequest request;
    while (stream->Read(&request)) {

        if (m_map.contains(request.phone())) {
            m_map.remove(request.phone());
        }
        m_map.insert(request.phone(), stream);


        emit MsgCenter::shareInstance()->signal_didReceivedStreamMsg(request);

        qDebug() << "Did Received stream: " << QString::fromStdString(request.data()) << QString::fromStdString(request.phone());

        HBResponse response;
        response.set_type(MessageType::Group_Msg);
        response.set_from(request.phone());
        response.set_data(request.data());

        stream->Write(response);

    }

    qDebug() << "DidReceived finished";


    return Status::OK;
}


void SimpleService::RunService(std::string host)
{
    std::thread th([&, host]{


                       grpc::EnableDefaultHealthCheckService(true);
                       grpc::reflection::InitProtoReflectionServerBuilderPlugin();

                       ServerBuilder builder;
                       builder.AddListeningPort(host, grpc::InsecureServerCredentials());
                       builder.RegisterService(this);

//                       std::unique_ptr<Server> server(builder.BuildAndStart());
                       m_server = builder.BuildAndStart();

                       qDebug() << "Server listening on: " << QString::fromStdString(host);
                       m_server->Wait();

                   });
    th.detach();

}



void SimpleService::pushMsgToClient(std::string phone)
{

    if (m_map.find(phone) == m_map.end()) {
        qDebug() << "没有对应流";
        return;
    }

    HBStream * stream = m_map[phone];
    qDebug() << "Server send: " << stream;

    HBResponse res;
    res.set_type(MessageType::Push_Msg);
    res.set_from(phone);
    res.set_data("Push msg to:" + phone);

    stream->Write(res);

}

void SimpleService::pushMsgForGlobal()
{
    auto keys = m_map.keys();

    for (int i = 0; i < keys.count(); i++) {
        std::string k = keys[i];
        auto stream = m_map[k];

        HBResponse res;
        res.set_type(MessageType::Push_Msg);
        res.set_from(k);
        res.set_data("Push msg to:" + k);

        stream->Write(res);
    }



//    stream->Write(res);
}












