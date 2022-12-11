#include "ldFunction.hpp"
#include <QString>
#include "line.hpp"
#include "coil.hpp"
#include "contact.hpp"
#include "node.hpp"
#include "type.hpp"
#include "drag.hpp"

QDataStream & operator >>(QDataStream & stream, Ld::Base **ld)
{
    QString title;
    int type;
    stream >> title >> type;
    if(title != "Ld"){
        stream.setStatus(QDataStream::ReadCorruptData);
        return stream;
    }
    switch(type)
    {
    case static_cast<int>(Ld::Type::Contact):
    {
        auto contact = new Ld::Contact;
        stream >> contact->address_ >> contact->type_;
        *ld = contact;
        break;
    }
    case static_cast<int>(Ld::Type::Coil):
    {
        auto coil = new Ld::Coil;
        stream >> coil->address_ >> coil->type_;
        *ld = coil;
        break;
    }
    case static_cast<int>(Ld::Type::Line):
        *ld = new Ld::Line;
        break;
    case static_cast<int>(Ld::Type::Node):
        *ld = new Ld::Node;
        break;
    }

    return stream;
}

Ld::Base * getLdObject(const QByteArray &dataArray)
{
    Ld::Base * ldObj{};
    QDataStream dataStream(dataArray);
    dataStream >> &ldObj;
    return ldObj;
}

