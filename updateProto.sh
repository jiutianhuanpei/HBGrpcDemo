#/bin/sh

rm -rf PBFiles/*

/usr/local/bin/protoc -I protos --grpc_out=PBFiles --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin protos/*.proto \

/usr/local/bin/protoc -I protos --cpp_out=PBFiles protos/*.proto

