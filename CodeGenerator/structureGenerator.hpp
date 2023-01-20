#ifndef STRUCTUREGENERATOR_HPP
#define STRUCTUREGENERATOR_HPP

#include <QObject>


class Network;
class GenerateErrors;

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
