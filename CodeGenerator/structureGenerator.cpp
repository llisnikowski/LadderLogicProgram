#include "structureGenerator.hpp"
#include "network.hpp"
#include "containerLd.hpp"
#include "type.hpp"
#include "contact.hpp"
#include "coil.hpp"
#include "counter.hpp"
#include "generateErrors.hpp"


template<>
QString StructureGenerator::getAddress<Ld::Input>(Ld::Input &obj);
template<>
QString StructureGenerator::getAddress<Ld::Contact>(Ld::Contact &obj);
template<>
QString StructureGenerator::getAddress<Ld::Output>(Ld::Output &obj);
template<>
QString StructureGenerator::getAddress<Ld::Coil>(Ld::Coil &obj);
template<>
QString StructureGenerator::getAddress<Ld::Counter>(Ld::Counter &obj);


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

QString StructureGenerator::getInputSeparator(Position pos)
{
    if(pos.line == 0){
        if(pos.x != 1){
            return "&";
        }
    }
    else{
        return "|";
    }
    return "";
}

void StructureGenerator::checkInputAndOutput(uint8_t inOut)
{
    if(!generateErrors_) return;
    if(inOut == onlyOut){
        generateErrors_->addError("Brak wejścia w networku nr: "
                                  + QString::number(networkNr_));
    }
    else if(inOut == onlyIn){
        generateErrors_->addError("Brak wyjścia w networku nr: "
                                  + QString::number(networkNr_));
    }
}

uint8_t StructureGenerator::inputOrOutput(Ld::Base &obj)
{
    if(obj.getType() >= Ld::Type::Input){
        return onlyIn;
    }
    else if(obj.getType() >= Ld::Type::Output){
        return onlyOut;
    }
    return noInNoOut;
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
    uint8_t inOutState = noInNoOut;
    network.getContainerLd().iteratorXLine(
        {Ld::Type::Address},
        [this, &inOutState, &networkCode](Position pos, Ld::Base* obj){
            inOutState |= inputOrOutput(*obj);
            if(obj->getType() >= Ld::Type::Input){
                networkCode += getInputSeparator(pos);
            }
            networkCode += getAddress(static_cast<Ld::Address&>(*obj));
        });

    checkInputAndOutput(inOutState);

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
    if(obj.getType() >= Ld::Type::Input){
        return getAddress(static_cast<Ld::Input&>(obj));
    }
    else if(obj.getType() >= Ld::Type::Output){
        return getAddress(static_cast<Ld::Output&>(obj));
    }
    return "";
}




template<>
QString StructureGenerator::getAddress<Ld::Input>(Ld::Input &obj)
{
    if(obj.getType() >= Ld::Type::Contact){
        return getAddress(static_cast<Ld::Contact&>(obj));
    }
    LdProperty::AddressField & address = obj.getAddress();
    return address.getFullAddress();
}

template<>
QString StructureGenerator::getAddress<Ld::Contact>(Ld::Contact &obj)
{
    QString addressText{};
    LdProperty::AddressField & address = obj.getAddress();
    addressText = address.getAddressType();
    if(obj.getPropertyType().getValue())
        addressText = addressText.toLower();
    addressText += address.getAddressNr();
    return addressText;
}

template<>
QString StructureGenerator::getAddress<Ld::Output>(Ld::Output &obj)
{
    if (obj.getType() >= Ld::Type::Coil){
        return getAddress(static_cast<Ld::Coil&>(obj));
    }
    else if(obj.getType() >= Ld::Type::Counter){
        return getAddress(static_cast<Ld::Counter&>(obj));
    }
    return "=" + obj.getAddress().getFullAddress();
}

template<>
QString StructureGenerator::getAddress<Ld::Coil>(Ld::Coil &obj)
{
    LdProperty::AddressField & address = obj.getAddress();
    switch(obj.getPropertyType().getValue()){
    case 1:
        return 'S' + address.getFullAddress();
    case 2:
        return 'R' + address.getFullAddress();
    default:
        return '=' + address.getFullAddress();
    }
}

template<>
QString StructureGenerator::getAddress<Ld::Counter>(Ld::Counter &obj)
{
    LdProperty::AddressField & address = obj.getAddress();
    switch(obj.getPropertyType().getValue()){
    case 1:
        return "=D" + address.getAddressNr();
    case 2:
        return 'R' + address.getFullAddress();
    default:
        return '=' + address.getFullAddress();
    }
}













































