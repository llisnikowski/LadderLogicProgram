/*!
 * \file line.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/


#ifndef LINE_HPP
#define LINE_HPP

#include "drop.hpp"

namespace Ld {

/*!
 * \brief Klasa Coil udostępnia symbol linii z języka LD.
 */
class Line : public Drop
{
    Q_OBJECT
public:
    explicit Line(QQuickItem *parent = nullptr);

    Type getType() const override;

    void paint(QPainter *painter) override;
    QByteArray getData() const override;
};


} //namespace Ld

#endif // LINE_HPP
