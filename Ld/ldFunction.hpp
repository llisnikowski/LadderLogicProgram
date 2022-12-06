#ifndef LDFUNCTION_HPP
#define LDFUNCTION_HPP

#include <QDataStream>

namespace Ld{
class Base;
} // namespace Ld


QDataStream & operator >>(QDataStream & stream, Ld::Base ** ld);

Ld::Base * getLdObject(const QByteArray &dataArray);

#endif // LDFUNCTION_HPP
