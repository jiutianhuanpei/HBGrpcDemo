#ifndef SIMPLECLIENT_H
#define SIMPLECLIENT_H

#include "../Common/GrpcHeader.h"
#include "../PBFiles/HBService.grpc.pb.h"

using SHB::HBService;
using SHB::HBRequest;
using SHB::HBResponse;
using grpc::CompletionQueue;

class SimpleClient
{
public:
    SimpleClient(std::string host);


    bool sendMsg(HBRequest request);
    void sendStreamMsg(HBRequest request);


private:
    std::unique_ptr<HBService::Stub> stub_;

    std::unique_ptr< ::grpc::ClientWriter< HBRequest>> m_writer;

    void m_receivedStreamMsgCallback();

private:
    CompletionQueue m_queue;

    std::unique_ptr< ::grpc::ClientReaderWriter<HBRequest, HBResponse> >  m_stream = nullptr;

    ClientContext context;
    bool hadRead = false;
};

#endif // SIMPLECLIENT_H
