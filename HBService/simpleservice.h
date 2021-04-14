#ifndef SIMPLESERVICE_H
#define SIMPLESERVICE_H

//#include <QObject>
#include "../Common/GrpcHeader.h"
#include "../PBFiles/HBService.grpc.pb.h"
#include <QMap>

using HBRequest = SHB::HBRequest;
using HBResponse = SHB::HBResponse;
using Service = SHB::HBService::Service;

typedef ::grpc::ServerReaderWriter<SHB::HBResponse, SHB::HBRequest> HBStream;


class SimpleService final : public Service
{
public:
    SimpleService();

    void RunService(std::string host);

    void pushMsgToClient(std::string phone);
    void pushMsgForGlobal();

private:
    grpc::Status request(grpc::ServerContext *context, const HBRequest *request, HBResponse *response);

    grpc::Status streamRequest(grpc::ServerContext *context, ::grpc::ServerReaderWriter<SHB::HBResponse, SHB::HBRequest> *stream);



private:
    std::unique_ptr<Server> m_server;

    ::grpc::ServerReaderWriter<SHB::HBResponse, SHB::HBRequest> *m_stream;

//    std::map<std::string, HBStream> m_map;
    QMap<std::string, HBStream *> m_map;

};

#endif // SIMPLESERVICE_H
