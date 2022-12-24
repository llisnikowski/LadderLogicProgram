#include "codeGenerator.hpp"
#include "networkList.hpp"

CodeGenerator::CodeGenerator(QObject *parent)
    : QObject{parent}, networkList_{}
{
}

void CodeGenerator::setNetworkList(NetworkList *networkList)
{
    networkList_ = networkList;
}
