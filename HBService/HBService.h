#ifndef HBSERVICE_H
#define HBSERVICE_H

#include <QWidget>
#include "simpleservice.h"

#include "../PBFiles/HBService.grpc.pb.h"

using SHB::HBRequest;

QT_BEGIN_NAMESPACE
namespace Ui { class HBService; }
QT_END_NAMESPACE

class HBService : public QWidget
{
    Q_OBJECT

public:
    HBService(QWidget *parent = nullptr);
    ~HBService();

private slots:
    void on_pBtnone2one_clicked();

    void on_pBtnStream_clicked();



    void slot_didReceived1v1(HBRequest request);
    void slot_didReceivedStream(HBRequest request);

    void on_pBtnStreamGlobal_clicked();

private:
    Ui::HBService *ui;

    SimpleService *m_simService;

};
#endif // HBSERVICE_H
