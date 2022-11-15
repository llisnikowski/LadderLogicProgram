/*!
 * \file factory.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QObject>
#include <QQuickItem>

namespace Ld {
class Base;
class Line;
class Contact;
class Coil;
class Painter;

/*!
 * \brief Klasą Factory jest odpowiedzialną za tworzenie obiektów symboli Ld
 * i inicjalizacje ich odpowiednimi zmiennymi (np. rozmiar obiektu).
 */
class Factory : public QObject
{
    Q_OBJECT
public:
    explicit Factory(QObject *parent = nullptr);

    void setObjectSize(float objectSize);
    float getObjectSize() const;
    void setPainter(Painter *painter);
    Painter *getPainter();

    Line *createLine(QQuickItem *parent = nullptr) const;
    Contact *createContact(QQuickItem *parent = nullptr) const;
    Coil *createCoil(QQuickItem *parent = nullptr) const;

private:
    template <typename T>
    T *initObject(T * obj) const;

    /*!
     * \brief Rozmiar tworzonych obiektów
     * \see setObjectSize, getObjectSize
     */
    float objectSize_;
    /*!
     * \brief Przypisywana klasa Painter
     * \see setPainter, getPainter
     */
    Painter *painter_;
};

} // namespace Ld

#endif // LDFACTORY_HPP
