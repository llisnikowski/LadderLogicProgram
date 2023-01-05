#include "interfaceButtons.hpp"

InterfaceButtons::InterfaceButtons(QObject *parent)
    : QObject{parent}, logObject_{}, serialPort_{}, saver_{}
{
}

void InterfaceButtons::newProject()
{
    if(!networkList_) return;
    networkList_->clearList();
    networkList_->addNewNetwork();
}

void InterfaceButtons::open(QString filename)
{
    if(!saver_) return;
    saver_->setFile(filename);
    saver_->load();
}

void InterfaceButtons::save(QString filename)
{
    if(!saver_) return;
    saver_->setFile(filename);
    saver_->save();
}

void InterfaceButtons::connectWindow()
{

}

void InterfaceButtons::verify()
{
    if(!codeGenerator_) return;
    if(logObject_) logObject_->addToLogs("Sprawdzanie programu...");
    if(codeGenerator_->verify()){
        if(logObject_) logObject_->addToLogs("Program poprawny");
    }
    else{
        if(logObject_) logObject_->addToLogs("Program niepoprawny");
    }
}

void InterfaceButtons::upload()
{
    if(!codeGenerator_) return;
    if(!serialPort_) return;
    if(codeGenerator_->verify()){
        if(logObject_){
            logObject_->addToLogs("Wysyłanie programu...");
        }
        serialPort_->send(codeGenerator_->getCode());
    }
    else{
        if(logObject_) logObject_->addToLogs("Program niepoprawny");
    }
}

void InterfaceButtons::plcMode()
{

}

void InterfaceButtons::setCurrentTime()
{

}
