#ifndef DROPDELETER_HPP
#define DROPDELETER_HPP

#include "dropValidator.hpp"

class DropDeleter : public Ld::DropValidator
{
public:
    explicit DropDeleter(QObject *parent = nullptr);

    Qt::DropAction valid(const QByteArray &dragArrayData) override;
    void doAction(const QByteArray &dragArrayData) override;
};

#endif // DROPDELETER_HPP
