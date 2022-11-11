/*!
 * \file componentLd.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>

namespace Ld{

class LdPainter;

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
class ComponentLd : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ComponentLd(QQuickItem *parent = nullptr);

    void setLdPainter(LdPainter *ldPainter);
    LdPainter *getLdPainter();

protected:
    LdPainter *ldPainter_;
};

} // namespace Ld

#endif // COMPONENTLD_HPP
