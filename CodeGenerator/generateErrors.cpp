#include "generateErrors.hpp"


GenerateErrors::GenerateErrors(QObject *parent)
    :errorMessages_()
{
}

void GenerateErrors::addError(QString message)
{
    errorMessages_.append(message);
}

void GenerateErrors::clearErrors()
{
    errorMessages_.clear();
}

const QStringList &GenerateErrors::getErrorMessages() const
{
    return errorMessages_;
}

bool GenerateErrors::isOk() const
{
    return errorMessages_.isEmpty();
}
