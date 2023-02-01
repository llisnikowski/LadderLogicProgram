#ifndef CODEGENERATOR_HPP
#define CODEGENERATOR_HPP

#include <QObject>
#include <QString>
#include "generateErrors.hpp"
#include "logInterface.hpp"
#include "parametersGenetator.hpp"
#include "structureGenerator.hpp"

#define DEBUG_DISPLAY_CODE 1

class NetworkList;
class Network;
class ConsoleLog;
class ParametersGenetator;
class ContainerLd;
namespace Ld {
class Coil;
class Counter;
class Address;
} // namespace Ld



class CodeGenerator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString code READ getCode NOTIFY codeReady)
public:
    explicit CodeGenerator(QObject *parent = nullptr);

    void setNetworkList(NetworkList *networkList);
    void setLogObject(LogInterface *logObject);

    bool startGenerating();
    const QString &getCode() const;

signals:
    void codeReady(const QString &);

private:
    void clear();
    bool generate();
    template <typename T>
    void getAddress(T &obj, QString &output);
    void addObjectsFromContainer(ContainerLd &containerLd);
    void mergeCodes();
    bool checkGenerateErrors();
    void debugDisplayCode();
    QString getHeader();
    QString getFooter();

    NetworkList *networkList_;
    LogInterface *logObject_;
    QString code_;
    GenerateErrors generateErrors_;
    StructureGenerator structureGenerator_;
    ParametersGenetator parametersGenetator_;
};

#endif // CODEGENERATOR_HPP
