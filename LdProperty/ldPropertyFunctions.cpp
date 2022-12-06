#include "ldPropertyFunctions.hpp"
#include <QString>
#include "LdProperty/base.hpp"
#include "address.hpp"
#include "textField.hpp"
#include "type.hpp"


QDataStream & operator >>(QDataStream & stream, LdProperty::Base **property)
{
    QString title;
    int type;
    stream >> title >> type;
    if(title != "LdProperty"){
        stream.setStatus(QDataStream::ReadCorruptData);
        return stream;
    }

    switch(type)
    {
    case static_cast<int>(LdProperty::Type::TextField):
        *property = new LdProperty::TextField;
        break;
    case static_cast<int>(LdProperty::Type::Address):
        *property = new LdProperty::Address;
        break;
    }

    return stream;
}



LdProperty::Base *getLdPropertyObject(const QByteArray &dataArray)
{
    LdProperty::Base *property{};
    QDataStream dataStream(dataArray);
    dataStream >> &property;
    return property;
}
