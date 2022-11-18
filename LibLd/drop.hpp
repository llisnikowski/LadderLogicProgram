/*!
 * \file drop.hpp
 * \brief
 * \author Łukasz Liśnikowski
*/
#ifndef DROP_HPP
#define DROP_HPP

#include "base.hpp"

namespace Ld {


/*!
 * \brief Klasa Drop udostępnia interfejs upuszczania dla mechanizmu
 * <a href="https://doc.qt.io/qt-6/dnd.html">
 *  Drag and Drop</a>.
 */
class Drop : public Base
{
    Q_OBJECT
public:
    explicit Drop(QQuickItem *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

} // namespace Ld

#endif // DROP_HPP
