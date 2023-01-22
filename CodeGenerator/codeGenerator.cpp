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
    generateErrors_{this}, structureGenerator_{this}, parametersGenetator_{this}
{
    structureGenerator_.setGenerateErrors(&generateErrors_);
    parametersGenetator_.setGenerateErrors(&generateErrors_);
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
    if(!generate()) return false;
    if(checkGenerateErrors()) return false;
    mergeCodes();

#if(DEBUG_DISPLAY_CODE)
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
    parametersGenetator_.clear();
    code_.clear();
}

bool CodeGenerator::generate()
{
    if(!networkList_) return false;
    for(uint i = 0; i < networkList_->count(); i++){
        auto network = networkList_->getNetwork(i);
        if(!network) continue;
        structureGenerator_.addNetwork(*network);
        addObjectsFromContainer(network->getContainerLd());
    }
    return true;
}

void CodeGenerator::addObjectsFromContainer(ContainerLd &containerLd)
{
    containerLd.iteratorLineX(
        {Ld::Type::Address},
        [this](Position poz, Ld::Base* obj){
            Ld::Type type = obj->getType();
            if(type >= Ld::Type::Input){
                if(type == Ld::Type::Weektimer){
                    parametersGenetator_.checkAndSet(static_cast<Ld::Weektimer&>(*obj));
                }
            }
            else if(obj->getType() >= Ld::Type::Output){
                if(type == Ld::Type::Timer){
                    parametersGenetator_.checkAndSet(static_cast<Ld::Timer&>(*obj));
                }
                else if(type == Ld::Type::Counter){
                    parametersGenetator_.checkAndSet(static_cast<Ld::Counter&>(*obj));
                }
                else if(type == Ld::Type::Text){
                    parametersGenetator_.checkAndSet(static_cast<Ld::Text&>(*obj));
                }
            }
        });
}

void CodeGenerator::mergeCodes()
{
    code_ += getHeader();
    code_ += structureGenerator_.getCode();
    code_ += parametersGenetator_.getCode();
    code_ += getFooter();
}

bool CodeGenerator::checkGenerateErrors()
{
    if(!generateErrors_.isOk()){
        if(!logObject_) return true;
        for(auto errorMessage : generateErrors_.getErrorMessages()){
            logObject_->addToLogs(errorMessage);
        }
        return true;
    }
    return false;
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










