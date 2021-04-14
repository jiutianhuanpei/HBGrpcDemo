#ifndef MSGCENTER_H
#define MSGCENTER_H

#include <QObject>
#include "../PBFiles/HBService.grpc.pb.h"

using SHB::HBRequest;
using SHB::HBResponse;

class MsgCenter : public QObject
{
    Q_OBJECT
public:
    static MsgCenter *shareInstance();

signals:

    void signal_didReceived1v1Msg(HBRequest request);
    void signal_didReceivedStreamMsg(HBRequest request);

    void signal_didReceivedMessage(HBResponse response);

private:
    explicit MsgCenter(QObject *parent = nullptr);
    static MsgCenter *m_center;
    Q_DISABLE_COPY(MsgCenter)

};




#endif // MSGCENTER_H
