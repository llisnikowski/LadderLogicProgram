#ifndef EMPTYDROP_HPP
#define EMPTYDROP_HPP

#include "drop.hpp"

namespace Ld {

/*!
 * \brief Klasa EmptyDrop udostępniająca pusty obszar przeciągania dla mechnizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 */
class EmptyDrop : public Drop
{
public:
    EmptyDrop(QQuickItem *parent = nullptr);

    Base *clone(QQuickItem *parent = nullptr) override;
    Type getType() const override;
    void paint(QPainter *painter) override;
    QByteArray getData() const override;
};


}; //namespace Ld

#endif // EMPTYDROP_HPP
