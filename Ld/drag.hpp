/*!
 * \file drag.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef DRAG_HPP
#define DRAG_HPP

#include "Ld/base.hpp"
#include "ldFunction.hpp"

class QMimeData;
class QPainter;
class QDrag;

namespace Ld{

class DragData;

/*!
 * \brief Klasa Drag udostępnia interfejs przeciągania dla mechanizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 */
class Drag : public Base
{
    Q_OBJECT
public:
    explicit Drag(QQuickItem *parent = nullptr);
    virtual ~Drag();

    Type getType() const override;
    void setDragData(DragData *data);
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
    virtual void paintDrag(QPainter &painter);

signals:
    void dragged();

private:
    QDrag *createQDrag(QMouseEvent &event);
    QMimeData *createDragData(QMouseEvent &event);
    QPixmap createDragPixmap();

    DragData *dragData_;
};


} // namespace Ld

#endif // DRAG_HPP
