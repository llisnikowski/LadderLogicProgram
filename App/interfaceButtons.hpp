#ifndef INTERFACEBUTTONS_HPP
#define INTERFACEBUTTONS_HPP

#include "codeGenerator.hpp"
#include "saver.hpp"
#include "serialPort.hpp"
#include <QObject>

class InterfaceButtons : public QObject
{
    Q_OBJECT
public:
    explicit InterfaceButtons(QObject *parent = nullptr);

    void setLogObject(LogInterface *logObject){logObject_ = logObject;}
    void setSerialPort(SerialPort *serialPort){serialPort_ = serialPort;}
    void setSaver(Saver *saver){saver_ = saver;}
    void setCodeGenerator(CodeGenerator *codeGenerator){
        codeGenerator_ = codeGenerator;
    }
    void setNetworkList(NetworkList *networkList){networkList_ = networkList;}

public slots:
    void newProject();
    void open(QString filename);
    void save(QString filename);

    void connectWindow();
    void verify();
    void upload();
    void plcMode();
    void setCurrentTime();

signals:

private:
    LogInterface *logObject_;
    SerialPort *serialPort_;
    CodeGenerator *codeGenerator_;
    NetworkList *networkList_;
    Saver *saver_;
};

#endif // INTERFACEBUTTONS_HPP
