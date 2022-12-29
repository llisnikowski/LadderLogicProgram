#include "codeGenerator.hpp"
#include "networkList.hpp"
#include "network.hpp"
#include "consoleLog.hpp"
#include "type.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "timer.hpp"
#include "counter.hpp"
#include "weektimer.hpp"
#include "text.hpp"


CodeGenerator::CodeGenerator(QObject *parent)
    : QObject{parent}, networkList_{}, logObject_{}, code_{},
    parametersArray_{this}
{
}

void CodeGenerator::setNetworkList(NetworkList *networkList)
{
    networkList_ = networkList;
}

void CodeGenerator::setLogObject(LogInterface *logObject)
{
    logObject_ = logObject;
}

bool CodeGenerator::verify()
{
    return startGenerating();
}

bool CodeGenerator::startGenerating()
{
    qDebug() << "Start generating";
    try {
        if(!networkList_) return false;
        code_.clear();
        code_ += ":START\r\n";
        for(uint i = 0; i < networkList_->count(); i++){
            addStructureNetwork(i, networkList_->getNetwork(i));
        }
        code_ += ":END";
    }
    catch(const BadGenerated & badGenerated) {
        if(logObject_){
            logObject_->addToLogs(badGenerated.what());
        }
        return false;
    }



    emit codeReady(code_);

    qDebug()<<"---| KOD |---";
    qDebug() << code_;
    qDebug()<<"------";
    qDebug().noquote() << code_;

    return true;
}

void CodeGenerator::addHeader(uint i)
{
    if(i >= 100){
        throw BadGenerated{"Przekroczono limit networków (max 100)"};
    }
    code_ += ":N";
    code_ += QString::number((i/10)%10);
    code_ += QString::number(i%10);
    code_ += QString(' ');
}

void CodeGenerator::addEnd()
{
    code_ += "\r\n";
}

void CodeGenerator::addStructureNetwork(uint i, Network *network)
{
    ContainerLd &containerLd = network->getContainerLd();
    bool isInput = false;
    bool isOutput = false;
    QString networkCode{};
    containerLd.iteratorXLine(ContainerLd::ItInOut,
        [this, &isInput, &isOutput, &networkCode](uint line, uint x, Ld::Base* obj){
            Ld::Type type = obj->getType();
            if(type >= Ld::Type::Input){
                if(line == 0){
                    isInput = true;
                    if(x != 1){
                        networkCode += "&";
                    }
                }
                else{
                    networkCode += "|";
                }
                if(type == Ld::Type::Weektimer){
                    parametersArray_.set(static_cast<Ld::Weektimer&>(*obj));
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                isOutput = true;
                if(type == Ld::Type::Timer){
                    parametersArray_.set(static_cast<Ld::Timer&>(*obj));
                }
                else if(type == Ld::Type::Counter){
                    parametersArray_.set(static_cast<Ld::Counter&>(*obj));
                }
                else if(type == Ld::Type::Text){
                    parametersArray_.set(static_cast<Ld::Text&>(*obj));
                }
            }
            getAddress(static_cast<Ld::Address&>(*obj), networkCode);
    });
    if(!isInput && isOutput){
        throw BadGenerated{"Brak wejścia"};
    }
    else if(!isOutput && isInput){
        throw BadGenerated{"Brak wyjścia"};
    }
    else if(isInput && isOutput){
        addHeader(i);
        code_ += networkCode;
        addEnd();
    }
}

void CodeGenerator::getAddress(Ld::Address &obj, QString &output)
{
    LdProperty::AddressField & address = obj.getAddress();
    if(address.getTextValue() == "" || !address.textIsValid()){
        throw BadGenerated{"Niepoprawny adress obiektu"};
    }
    QString addressText = obj.getAddress().getTextValue().toUpper();
    if(obj.getType() >= Ld::Type::Input){
        if(obj.getType() == Ld::Type::Contact
                && static_cast<Ld::Contact&>(obj)
                       .getPropertyType().getValue() == 1){
            addressText = addressText.toLower();
        }
    }
    else if(obj.getType() >= Ld::Type::Output){
        if(obj.getType() == Ld::Type::Coil){
            addressText = getPrefix(static_cast<Ld::Coil&>(obj))
                          + addressText;
        }
        else if(obj.getType() == Ld::Type::Counter){
            addressText = getPrefix(static_cast<Ld::Counter&>(obj))
                          + addressText;
        }
        else {
            addressText = "=" + addressText;
        }
    }
    output += addressText;
}

QChar CodeGenerator::getPrefix(Ld::Coil &obj)
{
    switch(obj.getPropertyType().getValue()){
    case 1:
        return 'S';
    case 2:
        return 'R';
    default:
        return '=';
    }
}

QChar CodeGenerator::getPrefix(Ld::Counter &obj)
{
    switch(obj.getPropertyType().getValue()){
    case 1:
        return 'D';
    case 2:
        return 'R';
    default:
        return '=';
    }
}















