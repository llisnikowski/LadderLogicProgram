#ifndef GENERATEERRORS_HPP
#define GENERATEERRORS_HPP

#include <QObject>
#include <QStringList>

class GenerateErrors : public QObject
{
public:
    explicit GenerateErrors(QObject *parent = nullptr);

    void addError(QString message);
    void clearErrors();
    const QStringList &getErrorMessages() const;
    bool isOk() const;

private:
    QStringList errorMessages_;
};

#endif // CODEGENERATIONEXCEPTION_HPP
