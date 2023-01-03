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
    parametersArray_.clear();
    try {
        if(!networkList_) return false;
        code_.clear();
        code_ += ":START\r\n";
        for(uint i = 0; i < networkList_->count(); i++){
            addStructureNetwork(i, networkList_->getNetwork(i));
        }
        parametersArray_.get(code_);
        code_ += ":END";
    }
    catch(const BadGenerated & badGenerated) {
        if(logObject_){
            logObject_->addToLogs(badGenerated.what());
        }
        return false;
    }



    emit codeReady(code_);

#if(DISPLAY_CODE)
    qDebug()<<"---| KOD |---";
    qDebug() << code_;
    qDebug()<<"------";
    qDebug().noquote() << code_;
#endif

    return true;
}

const QString &CodeGenerator::getCode() const
{
    return code_;
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
    lastNetwork_ = network->getNr();
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
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                isOutput = true;
                if(type == Ld::Type::Coil){
                    getAddress(static_cast<Ld::Coil&>(*obj), networkCode);
                }
                else if(type == Ld::Type::Timer){
                    getAddress(static_cast<Ld::Timer&>(*obj), networkCode);
                }
                else if(type == Ld::Type::Counter){
                    getAddress(static_cast<Ld::Counter&>(*obj),networkCode);
                }
                else if(type == Ld::Type::Text){
                    getAddress(static_cast<Ld::Text&>(*obj), networkCode);
                }
            }
    });
    if(!isInput && isOutput){
        throw BadGenerated{"Brak wejścia w networku nr: "
                           + std::to_string(lastNetwork_)};
    }
    else if(!isOutput && isInput){
        throw BadGenerated{"Brak wyjścia w networku nr: "
                           + std::to_string(lastNetwork_)};
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
        throw BadGenerated{"Niepoprawny adress obiektu w networku nr: "
                           + std::to_string(lastNetwork_)};
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
            parametersArray_.set(obj);
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
                parametersArray_.set(obj);
                break;
            }
        }
        else {
            addressText = "=" + address.getFullAddress();
            parametersArray_.set(obj);
        }
    }

    output += addressText;
}













