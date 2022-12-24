#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QObject>

class NetworkList;

class CodeGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CodeGenerator(QObject *parent = nullptr);

    void setNetworkList(NetworkList *networkList);

signals:

private:
    NetworkList *networkList_;

};

#endif // CODEGENERATOR_HPP
