#include "ldPropertyFunctions.hpp"
#include <QString>



QDataStream & operator >>(QDataStream & stream, LdProperty::Base **property)
{
    QString title;
    int type;
    stream >> title >> type;
    if(title != "LdProperty"){
        stream.setStatus(QDataStream::ReadCorruptData);
        return stream;
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
