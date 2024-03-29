#ifndef COMPONENTLD_HPP
#define COMPONENTLD_HPP

#include <QQuickPaintedItem>
#include "LdProperty/base.hpp"
#include "type.hpp"

namespace Ld{

/*!
 * \brief Base jest klasą bazową dla klas symboli z języka LD takich
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

    /*!
     * \brief Funkcja wirtualna zwracająca kopie obiektu.
     * \param parent: rodzic dla nowopowstałego obiektu
     */
    virtual Base *clone(QQuickItem *parent = nullptr) = 0;

    virtual Type getType() const;

    /*!
     * \brief Zwraca dane obieku w postaci tablicy bajtów
     * <a href="https://doc.qt.io/qt-6/qbytearray.html">QByteArray</a>.
     */
    virtual QByteArray getData() const = 0;

    void paint(QPainter *painter) override = 0;

    void addProperty(LdProperty::Base* property);
    QVector<LdProperty::Base*> &getPropertiesList();

    void setSelect(bool sel);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    virtual void clickEvent(QMouseEvent *event);

    bool isDrag_;
    QVector<LdProperty::Base*> properties_;
    bool selected_;

signals:
    void clicked();
    void itemFocus();
};


} // namespace Ld

#endif // COMPONENTLD_HPP
