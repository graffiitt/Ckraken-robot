#ifndef MD_CLIENT_H
#define MD_CLIENT_H

#include <QObject>
#include <QModbusTcpClient>
#include <QModbusDataUnit>
#include <QUrl>

class MD_CLient : public QObject
{
    Q_OBJECT
public:
    MD_CLient(QObject *parent = nullptr) : QObject(parent)
    {
        modbusDevice = new QModbusTcpClient(this);
    };
    ~MD_CLient()
    {
        if (modbusDevice)
        {
            modbusDevice->disconnectDevice();
            delete modbusDevice;
        }
    };

    void connection(QString host)
    {
        const QUrl url = QUrl::fromUserInput(host);
        // modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, url.port());
        // modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, url.host());
    };

private:
    QModbusReply *lastRequest;
    QModbusClient *modbusDevice;
};

#endif