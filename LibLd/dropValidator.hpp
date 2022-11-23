#ifndef DROPVALIDATOR_HPP
#define DROPVALIDATOR_HPP

#include <QObject>

namespace Ld {

class DropValidator : public QObject
{
public:
    explicit DropValidator(QObject *parent = nullptr);

    virtual Qt::DropAction valid(const QByteArray & dragArrayData) = 0;
};


} // namespace Ld

#endif // DROPVALIDATOR_HPP
