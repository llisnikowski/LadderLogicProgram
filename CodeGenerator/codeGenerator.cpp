#include "codeGenerator.hpp"
#include "networkList.hpp"
#include "network.hpp"
#include <type_traits>
#include "type.hpp"
#include "counter.hpp"
#include "text.hpp"
#include "timer.hpp"
#include "weektimer.hpp"

CodeGenerator::CodeGenerator(QObject *parent)
    : QObject{parent}, networkList_{}, logObject_{}, code_{},
    generateErrors_{this}, structureGenerator_{this}, parametersArray_{this}
{
    structureGenerator_.setGenerateErrors(&generateErrors_);
    parametersArray_.setGenerateErrors(&generateErrors_);
}

void CodeGenerator::setNetworkList(NetworkList *networkList)
{
    networkList_ = networkList;
}

void CodeGenerator::setLogObject(LogInterface *logObject)
{
    logObject_ = logObject;
}

bool CodeGenerator::startGenerating()
{
    clear();
    if(!networkList_) return false;
    generate();
    if(!checkGeneration()) return false;
    mergeCodes();

#if(DISPLAY_CODE)
    debugDisplayCode();
#endif

    emit codeReady(code_);
    return true;
}

const QString &CodeGenerator::getCode() const
{
    return code_;
}

void CodeGenerator::clear()
{
    generateErrors_.clearErrors();
    structureGenerator_.clear();
    parametersArray_.clear();
    code_.clear();
}

void CodeGenerator::generate()
{
    for(uint i = 0; i < networkList_->count(); i++){
        auto network = networkList_->getNetwork(i);
        if(!network) continue;
        structureGenerator_.addNetwork(*network);
        addObjectsFromContainer(network->getContainerLd());
    }
}

void CodeGenerator::addObjectsFromContainer(ContainerLd &containerLd)
{
    containerLd.iteratorLineX(
        {Ld::Type::Address},
        [this](Position poz, Ld::Base* obj){
            Ld::Type type = obj->getType();
            if(type >= Ld::Type::Input){
                if(type == Ld::Type::Weektimer){
                    parametersArray_.checkAndSet(static_cast<Ld::Weektimer&>(*obj));
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                if(type == Ld::Type::Timer){
                    parametersArray_.checkAndSet(static_cast<Ld::Timer&>(*obj));
                }
                else if(type == Ld::Type::Counter){
                    parametersArray_.checkAndSet(static_cast<Ld::Counter&>(*obj));
                }
                else if(type == Ld::Type::Text){
                    parametersArray_.checkAndSet(static_cast<Ld::Text&>(*obj));
                }
            }
        });
}

void CodeGenerator::mergeCodes()
{
    code_ += getHeader();
    code_ += structureGenerator_.getCode();
    code_ += parametersArray_.getCode();
    code_ += getFooter();
}

bool CodeGenerator::checkGeneration()
{
    if(!generateErrors_.isOk()){
        for(auto errorMessage : generateErrors_.getErrorMessages()){
            logObject_->addToLogs(errorMessage);
        }
        return false;
    }
    return true;
}


void CodeGenerator::debugDisplayCode()
{
    qDebug()<<"---| KOD |---";
    qDebug() << code_;
    qDebug()<<"------";
    qDebug().noquote() << code_;
}

QString CodeGenerator::getHeader()
{
    return ":START\r\n";
}

QString CodeGenerator::getFooter()
{
    return ":END";
}










