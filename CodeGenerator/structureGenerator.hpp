#ifndef STRUCTUREGENERATOR_HPP
#define STRUCTUREGENERATOR_HPP

#include <QObject>
#include "position.hpp"


class Network;
class GenerateErrors;
namespace Ld{
class Base;
}



class StructureGenerator : public QObject
{
    Q_OBJECT
public:
    explicit StructureGenerator(QObject *parent = nullptr);

    void setGenerateErrors(GenerateErrors *generateErrors);

    void clear();
    void addNetwork(Network &network);

    const QString &getCode() const;

private:
    enum{
        noInNoOut = 0,
        onlyIn =    1,
        onlyOut =   2,
        inAndOut =  4
    };

    QString getInputSeparator(Position pos);
    void checkInputAndOutput(uint8_t inOut);
    uint8_t inputOrOutput(Ld::Base &obj);

    QString getPrefix();
    QString getPostfix();
    QString getStructure(Network &network);

    template <typename T>
    QString getAddress(T &obj);

    uint networkNr_;
    QString code_;

    GenerateErrors *generateErrors_;
};



#endif // STRUCTUREGENERATOR_HPP
