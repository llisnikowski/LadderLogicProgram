#include "interfaceButtons.hpp"
#include "serialPort.hpp"
#include <QDateTime>
#include <QTimer>
#include <functional>


InterfaceButtons::InterfaceButtons(QObject *parent)
    : QObject{parent}, logObject_{}, serialPort_{}, saver_{}, lastSavePath_{}
{
}

const QString &InterfaceButtons::getSavePath() const
{
    return lastSavePath_;
}

void InterfaceButtons::setSavePath(const QString path)
{
    lastSavePath_ = path;
    emit savePathChanged();
}

void InterfaceButtons::newProject()
{
    if(!networkList_) return;
    networkList_->clearList();
    networkList_->addNewNetwork();
    lastSavePath_ = "";
}

void InterfaceButtons::open()
{
    if(!saver_) return;
    if(lastSavePath_ == "") return;
    saver_->setFile(lastSavePath_);
    saver_->load();
}

void InterfaceButtons::save()
{
    if(!saver_) return;
    if(lastSavePath_ == "") return;
    saver_->setFile(lastSavePath_);
    saver_->save();
}

void InterfaceButtons::connectWindow()
{

}

void InterfaceButtons::verify()
{
    if(!codeGenerator_) return;
    if(logObject_) logObject_->addToLogs("Sprawdzanie programu...");
    if(codeGenerator_->startGenerating()){
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
    if(codeGenerator_->startGenerating()){
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
    if(!serialPort_) return;
    QString currentTimeStr = QTime::currentTime().toString(":Thhmm\r\n");
    auto currentDate = QDate::currentDate();
    QString currentDateStr = currentDate.toString(":DyyMMdd")
                             + QString::number(currentDate.dayOfWeek())
                             + "\r\n";
    serialPort_->send(currentTimeStr);
    QTimer::singleShot(700, [this,currentDateStr](){
        serialPort_->send(currentDateStr);
    });

}















