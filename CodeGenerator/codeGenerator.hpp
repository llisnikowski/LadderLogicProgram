#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QObject>
#include <QString>
#include <exception>
#include "parametersArray.hpp"
#include "logInterface.hpp"

class NetworkList;
class Network;
class ConsoleLog;
namespace Ld {
class Coil;
class Counter;
class Address;
} // namespace Ld


using BadGenerated = std::logic_error;

class CodeGenerator : public QObject
{
    Q_OBJECT
public:
    explicit CodeGenerator(QObject *parent = nullptr);

    void setNetworkList(NetworkList *networkList);
    void setLogObject(LogInterface *logObject);

public slots:
    bool verify();
    bool startGenerating();

signals:
    void codeReady(const QString &);

private:
    void addHeader(uint i);
    void addEnd();
    void addStructureNetwork(uint i, Network *network);

    template <typename T>
    void getAddress(T &obj, QString &output);

    NetworkList *networkList_;
    LogInterface *logObject_;
    QString code_;
    ParametersArray parametersArray_;
};

#endif // CODEGENERATOR_HPP
