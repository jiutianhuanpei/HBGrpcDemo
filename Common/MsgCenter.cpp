#include "MsgCenter.h"
#include <QMutex>


MsgCenter *MsgCenter::m_center = NULL;
static QMutex k_HB_msg_Mutex;

MsgCenter *MsgCenter::shareInstance()
{
    if (m_center == NULL) {
        QMutexLocker locker(&k_HB_msg_Mutex);
        if (m_center == NULL) {
            m_center = new MsgCenter;
        }
    }
    return m_center;
}

MsgCenter::MsgCenter(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<HBRequest>("HBRequest");
    qRegisterMetaType<HBResponse>("HBResponse");
}
