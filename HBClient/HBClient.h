#ifndef HBCLIENT_H
#define HBCLIENT_H

#include <QWidget>

#include "simpleclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class HBClient; }
QT_END_NAMESPACE

class HBClient : public QWidget
{
    Q_OBJECT

public:
    HBClient(QWidget *parent = nullptr);
    ~HBClient();

private slots:
    void on_pBtn1V1_clicked();

    void on_pBtnStream_clicked();

    void on_pBtnPush_clicked();

private:
    Ui::HBClient *ui;

    SimpleClient *m_simClient;

};
#endif // HBCLIENT_H
