/*!
 * \file componentLd.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>
#include "type.hpp"

namespace Ld{

class Painter;

/*!
 * \brief ComponentLd jest klasą bazową dla klas symboli z języka LD takich
 *  jak Coil, Contact, Line, Timer itp..
 *
 *  Dziedzyczy po klacie
 *  <a href="https://doc.qt.io/qt-5/qquickpainteditem.html">QQuickPaintedItem</a>
 *  która udostępnia wirtualną metodę
 *  <a href="https://doc.qt.io/qt-5/qquickpainteditem.html#paint">
 *  paint(QPainter *painter)</a> pozwalającą na wyświetlanie objektu.
 */
class Base : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit Base(QQuickItem *parent = nullptr);

    virtual Type getType() const;

    void setPainter(Painter *ldPainter);
    Painter *getPainter();

    virtual QByteArray getData() const = 0;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void clickEvent(QMouseEvent *event);

    Painter *ldPainter_;
    bool isDrag_;
};


} // namespace Ld

#endif // COMPONENTLD_HPP
