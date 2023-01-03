#include "serialPort.hpp"

SerialPort::SerialPort(QObject *parent)
    : QObject{parent}, serialPort_{this}, foundDevices_{}, logObject_{},
    selectDeviceIndex_{}, deviceConnected_{}
{
}

SerialPort::~SerialPort()
{
    disconnect();
}

void SerialPort::searchDevices()
{
    if(logObject_)
        logObject_->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();
    foundDevices_.clear();
    for(int i = 0; i < devices.count(); i++) {
        if(logObject_){
            logObject_->addToLogs("Znalaziono urządzenie: " + devices.at(i).portName() + " " + devices.at(i).description());
        }
            foundDevices_.append(devices.at(i).portName() + "\t" + devices.at(i).description());
    }
    emit foundDevicesChanged();
}

void SerialPort::connect()
{
    if(foundDevices_.count() == 0) {
        if(logObject_)
            logObject_->addToLogs("Nie wykryto żadnych urządzeń!");
        return;
    }

    QString portName = foundDevices_.at(selectDeviceIndex_).split("\t").first();
    serialPort_.setPortName(portName);

    if(serialPort_.open(QSerialPort::ReadWrite)) {
        serialPort_.setBaudRate(QSerialPort::Baud115200);
        serialPort_.setDataBits(QSerialPort::Data8);
        serialPort_.setParity(QSerialPort::NoParity);
        serialPort_.setStopBits(QSerialPort::OneStop);
        serialPort_.setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(&serialPort_, &QSerialPort::readyRead,
                         this, &SerialPort::read);
        if(logObject_)
            logObject_->addToLogs("Otwarto port szeregowy.");
        setDeviceConnected(true);
    } else {
        if(logObject_)
            logObject_->addToLogs("Otwarcie porty szeregowego się nie powiodło!");
    }
}

void SerialPort::disconnect()
{
    if(serialPort_.isOpen()) {
        serialPort_.close();
        if(logObject_)
            logObject_->addToLogs("Zamknięto połączenie.");
        setDeviceConnected(false);
    } else {
        if(logObject_)
            logObject_->addToLogs("Port nie jest otwarty!");
    }
}

bool SerialPort::send(QString message)
{
    if(serialPort_.isOpen() && serialPort_.isWritable()) {
        serialPort_.write(message.toStdString().c_str());
        return true;
    }
    return false;
}

void SerialPort::read()
{
    while(serialPort_.canReadLine()) {
        QString line = serialPort_.readLine();
        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        if(logObject_)
            logObject_->addToLogs(line.left(pos));
    }
}

void SerialPort::setLogObject(LogInterface *logObject)
{
    logObject_ = logObject;
}





bool SerialPort::getDeviceConnected() const
{
    return deviceConnected_;
}

void SerialPort::setDeviceConnected(bool connected)
{
    deviceConnected_ = connected;
    emit deviceConnectedChanged();
}

QStringList &SerialPort::getFoundDevices()
{
    return foundDevices_;
}

int SerialPort::getSelectDevice() const
{
    return selectDeviceIndex_;
}

void SerialPort::setSelectDevice(int device)
{
    selectDeviceIndex_ = device;
    emit selectDeviceChanged();
}








