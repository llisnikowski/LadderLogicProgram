#ifndef SERIALPORT_HPP
#define SERIALPORT_HPP

#include "logInterface.hpp"
#include <QObject>
#include <QList>
#include <QSerialPortInfo>
#include <QDateTime>
#include <QSerialPort>


class SerialPort : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList foundDevices READ getFoundDevices
                   NOTIFY foundDevicesChanged)
    Q_PROPERTY(int selectDevice READ getSelectDevice WRITE setSelectDevice
                   NOTIFY selectDeviceChanged)
    Q_PROPERTY(bool deviceConnected READ getDeviceConnected
                   WRITE setDeviceConnected NOTIFY deviceConnectedChanged)
public:
    explicit SerialPort(QObject *parent = nullptr);
    ~SerialPort();

public slots:
    void searchDevices();
    void connect();
    void disconnect();

public:
    bool send(const QString &message);
    void read();

    void setLogObject(LogInterface *logObject);

    bool getDeviceConnected() const;
    void setDeviceConnected(bool connected);
    QStringList &getFoundDevices();
    int getSelectDevice() const;
    void setSelectDevice(int device);

signals:
    void deviceConnectedChanged();
    void foundDevicesChanged();
    void selectDeviceChanged();

private:
    QSerialPort serialPort_;
    QStringList foundDevices_;
    LogInterface *logObject_;
    int selectDeviceIndex_;
    bool deviceConnected_;
};

#endif // SERIALPORT_HPP
