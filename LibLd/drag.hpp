/*!
 * \file drag.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#ifndef DRAG_HPP
#define DRAG_HPP

#include "base.hpp"

class QMimeData;
class QPainter;
class QDrag;

namespace Ld{

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

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void paintDrag(QPainter &painter);

private:
    QDrag *createQDrag(QMouseEvent &event);
    QMimeData *createDragData(QMouseEvent &event);
    QPixmap createDragPixmap();
};


} // namespace Ld

#endif // DRAG_HPP
