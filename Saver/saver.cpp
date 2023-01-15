#include "saver.hpp"
#include <QFile>

Saver::Saver(QObject *parent)
    : QObject{parent}, fileName_{}, networkList_{}
{
}

bool Saver::save()
{
    if(!networkList_){
        return false;
    }
    if(fileName_.isEmpty()){
        return false;
    }
    QFile file(fileName_);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QDataStream out(&file);
    out << *networkList_;
    file.close();
    return true;
}

bool Saver::load()
{
    if(!networkList_){
        return false;
    }
    if(fileName_.isEmpty()){
        return false;
    }
    QFile file(fileName_);
    if (!file.open(QIODevice::ReadOnly)) {
        return false;
    }
    QDataStream in(&file);
    networkList_->clearList();
    in >> *networkList_;
    file.close();
    return true;
}

void Saver::setFile(QString filename)
{
    fileName_ = filename;
}

void Saver::setNetworkList(NetworkList *networkList)
{
    networkList_ = networkList;
}
