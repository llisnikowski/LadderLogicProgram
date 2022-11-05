/*!
 * \file componentLd.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>

namespace Ld{

/*!
 * \brief ComponentLd jest klasą bazową dla klas takich jak Coil, Contact,
 * Timer itp..
 *
 *  Dziedzyczy po klacie
 *  <a href="https://doc.qt.io/qt-5/qquickpainteditem.html">QQuickPaintedItem</a>
 *  która udostępnia wirtualną metodę
 *  <a href="https://doc.qt.io/qt-5/qquickpainteditem.html#paint">
 *  paint(QPainter *painter)</a> pozwalającą na wyświetlanie objektu
 */
class ComponentLd : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit ComponentLd(QQuickItem *parent = nullptr);

private:

};

} // namespace Ld

#endif // COMPONENTLD_HPP
