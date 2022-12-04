#ifndef LDPROPERTY_FUNCTIONS_HPP
#define LDPROPERTY_FUNCTIONS_HPP

#include <QDataStream>

namespace LdProperty{
class Base;
} // namespace Ld


QDataStream & operator >>(QDataStream & stream, LdProperty::Base **property);

LdProperty::Base *getLdPropertyObject(const QByteArray &dataArray);




#endif // LDPROPERTY_FUNCTIONS_HPP
