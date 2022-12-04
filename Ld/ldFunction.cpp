#include "ldFunction.hpp"
#include <QString>
#include "line.hpp"
#include "coil.hpp"
#include "contact.hpp"
#include "node.hpp"
#include "type.hpp"

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
        *ld = new Ld::Contact;
        break;
    case static_cast<int>(Ld::Type::Coil):
        *ld = new Ld::Coil;
        break;
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

