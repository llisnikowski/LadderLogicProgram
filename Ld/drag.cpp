/*!
 * \file drag.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "drag.hpp"
#include "dragData.hpp"
#include "qpixmap.h"
#include <QMimeData>
#include <QPainter>
#include <QDrag>
#include <functional>

namespace Ld{


Drag::Drag(QQuickItem *parent)
    :Base{parent}, dragData_{}
{
}

Drag::~Drag()
{
    if(dragData_) delete dragData_;
}

Type Drag::getType() const
{
    return Type::Drag;
}

/*!
 * \brief Ustawia obiekt przechowujący dane dla mechanizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 */
void Drag::setDragData(DragData *data)
{
    if(dragData_) delete dragData_;
    dragData_ = data;
}


/*!
 * \brief Funkcja obsługująca wydarzenie MouseMove po zaakceptowaniu
 * wydarzenia MouseButtonPress
 *
 * Inicjalizuje przeciąganie obiektu dla mechanizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html"> Drag and Drop</a>.
 * \param event: Wskaźnik do obiektu
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 */
void Drag::mouseMoveEvent(QMouseEvent *event)
{
    event->accept();
    if(!isDrag_){
        isDrag_ = true;
        QDrag *drag = createQDrag(*event);
        Qt::DropAction dragAction =
            drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::IgnoreAction);
        if(dragData_) dragData_->doAction(dragAction);
        if(dragAction != Qt::IgnoreAction){
            emit dragged();
            forceActiveFocus();
        }
    }
}



/*!
 * \brief Wirtualna metoda rysująca ikonę przeciągania.
 *
 * Nie przesłonięta uruchamia domyślną metode rysującą obiekt (paint()).
 * \param painter: Referencja do klasy rysującej
 * <a href="https://doc.qt.io/qt-6/qpainter.html">QPainter</a>.
 */
void Drag::paintDrag(QPainter &painter)
{
    paint(&painter);
}

/*!
 * \brief Tworzy klasę
 * <a href="https://doc.qt.io/qt-6/qdrag.html">QDrag</a>
 * zapewniającą obsługę dla metody przeciągnij i upuść.
 * \param event: Wydarzenie
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 * \return Wskaźnik do utworzonego obiektu
 * <a href="https://doc.qt.io/qt-6/qdrag.html">QDrag</a>.
 */
QDrag *Drag::createQDrag(QMouseEvent &event)
{
    QDrag *drag = new QDrag(this);
    drag->setMimeData(createDragData(event));
    drag->setPixmap(createDragPixmap());
    drag->setHotSpot(QPoint(drag->pixmap().width()/2,
                            drag->pixmap().height()/2));
    return drag;
}


/*!
 * \brief Tworzy kontener danych dla wydarzenia przeciągania.
 * \param event: Wydarzenie
 * <a href="https://doc.qt.io/qt-6/qmouseevent.html">QMouseEvent</a>.
 * \return Wskaźnik do utworzonego obiektu
 * <a href="https://doc.qt.io/qt-6/qmimedata.html">QMimeData</a>.
 */
QMimeData *Drag::createDragData(QMouseEvent &)
{
    QMimeData *mimeData = new QMimeData;
    if(dragData_){
        dragData_->setLd(*this);
        mimeData->setData("application/x-dnditemdata", dragData_->getData());
    }

    return mimeData;
}

/*!
 * \brief Tworzy ikonę przeciągania.
 * \return Utworzona ikona
 * <a href="https://doc.qt.io/qt-6/qpixmap.html">QPixmap</a>.
 */
QPixmap Drag::createDragPixmap()
{
    QPixmap pixmap(width(), height());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing, true);
    paintDrag(painter);
    return pixmap;
}




} // namespace Ld
