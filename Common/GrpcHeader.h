#ifndef GRPCHEADER_H
#define GRPCHEADER_H

#include <QDebug>
#include <QObject>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include <grpcpp/grpcpp.h>


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ClientReader;
using grpc::ClientWriter;


using grpc::Channel;
using grpc::ClientContext;


const QString hb_hostStr = "10.10.10.111:50052";




#endif // GRPCHEADER_H
