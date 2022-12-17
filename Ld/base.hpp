/*!
 * \file componentLd.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>
#include "LdProperty/base.hpp"
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

    virtual Base *clone(QQuickItem *parent = nullptr) = 0;

    virtual Type getType() const;

    void setPainter(Painter *ldPainter);
    Painter *getPainter();

    virtual QByteArray getData() const = 0;
    void setVisibleProperties(bool visible);
    void addProperty(LdProperty::Base* property);
    QVector<LdProperty::Base*> &getPropertiesList();

    void setSelect(bool sel);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void clickEvent(QMouseEvent *event);
    int getSelectedFlag();

    Painter *ldPainter_;
    bool isDrag_;
    QVector<LdProperty::Base*> properties_;
    bool showProperties_;
    bool selected_;

signals:
    void clicked();
    void itemFocus();
};


} // namespace Ld

#endif // COMPONENTLD_HPP
