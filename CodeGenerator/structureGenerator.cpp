#include "structureGenerator.hpp"
#include "network.hpp"
#include "containerLd.hpp"
#include "type.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "timer.hpp"
#include "counter.hpp"
#include "weektimer.hpp"
#include "text.hpp"
#include "generateErrors.hpp"

using InputType = std::false_type;
using OutputType = std::true_type;

template <typename T>
OutputType isOutputType;
template <>
InputType isOutputType<Ld::Contact>;
template <>
InputType isOutputType<Ld::Weektimer>;

StructureGenerator::StructureGenerator(QObject *parent)
    : QObject{parent}, networkNr_{}, code_{}, generateErrors_{}
{

}

void StructureGenerator::setGenerateErrors(GenerateErrors *generateErrors)
{
    generateErrors_ = generateErrors;
}

void StructureGenerator::clear()
{
    code_.clear();
    networkNr_ = 0;
}

void StructureGenerator::addNetwork(Network &network)
{
    QString networkCode = getStructure(network);
    if(networkCode.isEmpty()) return;
    code_ += getPrefix() + networkCode + getPostfix();
    networkNr_++;
}

const QString &StructureGenerator::getCode() const
{
    return code_;
}

QString StructureGenerator::getPrefix()
{
    if(networkNr_ >= 100){
        if(generateErrors_){
            generateErrors_->addError("Przekroczono limit networków (max 100)");
        }
        return "";
    }
    return QString(":N%1 ").arg(networkNr_, 2, 10, QChar('0'));
}

QString StructureGenerator::getPostfix()
{
    return "\r\n";
}

QString StructureGenerator::getStructure(Network &network)
{
    QString networkCode{};
    ContainerLd &containerLd = network.getContainerLd();
    bool isInput = false;
    bool isOutput = false;
    containerLd.iteratorXLine(
        {Ld::Type::Address},
        [this, &isInput, &isOutput, &networkCode](Position pos, Ld::Base* obj){
            Ld::Type type = obj->getType();
            if(type >= Ld::Type::Input){
                if(pos.line == 0){
                    isInput = true;
                    if(pos.x != 1){
                        networkCode += "&";
                    }
                }
                else{
                    networkCode += "|";
                }
                if(type == Ld::Type::Contact){
                    networkCode += getAddress(static_cast<Ld::Contact&>(*obj));
                }
                else if(type == Ld::Type::Weektimer){
                    networkCode += getAddress(static_cast<Ld::Weektimer&>(*obj));
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                isOutput = true;
                if(type == Ld::Type::Coil){
                    networkCode += getAddress(static_cast<Ld::Coil&>(*obj));
                }
                else if(type == Ld::Type::Timer){
                    networkCode += getAddress(static_cast<Ld::Timer&>(*obj));
                }
                else if(type == Ld::Type::Counter){
                    networkCode += getAddress(static_cast<Ld::Counter&>(*obj));
                }
                else if(type == Ld::Type::Text){
                    networkCode += getAddress(static_cast<Ld::Text&>(*obj));
                }
            }
        });

    if(!isInput && isOutput){
        if(generateErrors_){
            generateErrors_->addError("Brak wejścia w networku nr: "
                                       + QString::number(networkNr_));
        }
    }
    else if(!isOutput && isInput){
        if(generateErrors_){
            generateErrors_->addError("Brak wyjścia w networku nr: "
                                       + QString::number(networkNr_));
        }
    }

    return networkCode;
}

template<typename T>
QString StructureGenerator::getAddress(T &obj)
{
    LdProperty::AddressField & address = obj.getAddress();
    if(address.getTextValue() == "" || !address.textIsValid()){
        if(generateErrors_){
            generateErrors_->addError("Niepoprawny adress obiektu w networku nr: "
                                       + QString::number(networkNr_));
        }
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

    return addressText;
}
