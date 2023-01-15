#include "serialPort.hpp"

SerialPort::SerialPort(QObject *parent)
    : QObject{parent}, serialPort_{this}, foundDevices_{}, logObject_{},
    selectDeviceIndex_{}, deviceConnected_{}
{
    QObject::connect(&serialPort_, &QSerialPort::readyRead,
                     this, &SerialPort::read);
}

SerialPort::~SerialPort()
{
    logObject_ = nullptr;
    disconnect();
}

void SerialPort::searchDevices()
{
    if(logObject_)
        logObject_->addToLogs("Szukam urządzeń...");
    QList<QSerialPortInfo> devices = QSerialPortInfo::availablePorts();
    foundDevices_.clear();
    for(int i = 0; i < devices.count(); i++) {
        if(logObject_){
            logObject_->addToLogs("Znalaziono urządzenie: " +
                devices.at(i).portName() + " " + devices.at(i).description());
        }
        foundDevices_.append(devices.at(i).portName() + "\t"
                             + devices.at(i).description());
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
    if(selectDeviceIndex_ >= foundDevices_.count()) {
        if(logObject_)
            logObject_->addToLogs("Nie wybrano urządzenia!");
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
        if(logObject_)
            logObject_->addToLogs("Otwarto port szeregowy.");
        emit deviceConnectedChanged();
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
        emit deviceConnectedChanged();
    } else {
        if(logObject_)
            logObject_->addToLogs("Port nie jest otwarty!");
    }
}

bool SerialPort::send(const QString &message)
{
    if(serialPort_.isOpen() && serialPort_.isWritable()) {
        serialPort_.write(message.toLocal8Bit());
        return true;
    }
    if(logObject_)
        logObject_->addToLogs("Brak połączenia ze sterownikiem");
    return false;
}

void SerialPort::read()
{
    while(serialPort_.canReadLine()) {
        QString line = serialPort_.readLine();
        int pos = line.lastIndexOf("\n");
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
    return serialPort_.isOpen();
}

const QStringList &SerialPort::getFoundDevices() const
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








