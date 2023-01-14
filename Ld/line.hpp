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
    enum DisplayType{
        normal,
        invisible,
        fromLeft,
        toRight,
        fromLeftToRigth
    };
    explicit Line(QQuickItem *parent = nullptr);

    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;
    void setDisplayType(DisplayType displayType);

    Type getType() const override;
    QByteArray getData() const override;

private:
    DisplayType displayType_;
};


} //namespace Ld

#endif // LINE_HPP
