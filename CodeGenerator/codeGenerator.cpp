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
#include <type_traits>

using InputType = std::false_type;
using OutputType = std::true_type;

template <typename T>
OutputType isOutputType;
template <>
InputType isOutputType<Ld::Contact>;
template <>
InputType isOutputType<Ld::Weektimer>;


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
                if(type == Ld::Type::Contact){
                    getAddress(static_cast<Ld::Contact&>(*obj), networkCode);
                }
                else if(type == Ld::Type::Weektimer){
                    getAddress(static_cast<Ld::Weektimer&>(*obj), networkCode);
                    parametersArray_.set(static_cast<Ld::Weektimer&>(*obj));
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                isOutput = true;
                if(type == Ld::Type::Coil){
                    getAddress(static_cast<Ld::Coil&>(*obj), networkCode);
                }
                else if(type == Ld::Type::Timer){
                    getAddress(static_cast<Ld::Timer&>(*obj), networkCode);
                    parametersArray_.set(static_cast<Ld::Timer&>(*obj));
                }
                else if(type == Ld::Type::Counter){
                    getAddress(static_cast<Ld::Counter&>(*obj),networkCode);
                    parametersArray_.set(static_cast<Ld::Counter&>(*obj));
                }
                else if(type == Ld::Type::Text){
                    getAddress(static_cast<Ld::Text&>(*obj), networkCode);
                    parametersArray_.set(static_cast<Ld::Text&>(*obj));
                }
            }
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

template <typename T>
void CodeGenerator::getAddress(T &obj, QString &output)
{
    LdProperty::AddressField & address = obj.getAddress();
    if(address.getTextValue() == "" || !address.textIsValid()){
        throw BadGenerated{"Niepoprawny adress obiektu"};
    }
    QString addressText{};
    if constexpr(!isOutputType<T>){
        if constexpr(std::is_same<T, Ld::Contact>::value){
            addressText = address.getAddressType();
            if(obj.getPropertyType().getValue())
                addressText = addressText.toLower();
            addressText += address.getAddressNr();
        }
        else{
            addressText = address.getFullAddress();
        }
    }
    else{
        if constexpr(std::is_same<T, Ld::Coil>::value){
            switch(obj.getPropertyType().getValue()){
            case 1:
                addressText += 'S';
                break;
            case 2:
                addressText += 'R';
                break;
            default:
                addressText += '=';
                break;
            }
            addressText += address.getFullAddress();;
        }
        else if constexpr(std::is_same<T, Ld::Counter>::value){
            switch(obj.getPropertyType().getValue()){
            case 1:
                addressText += "=D" + address.getAddressNr();
                break;
            case 2:
                addressText += 'R' + address.getFullAddress();
                break;
            default:
                addressText += '=' + address.getFullAddress();
                break;
            }
        }
        else {
            addressText = "=" + address.getFullAddress();
        }
    }

    output += addressText;
}













