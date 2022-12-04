/*!
 * \file factory.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QObject>
#include <QQuickItem>
#include <functional>

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

    void setPainter(Painter *painter);
    Painter *getPainter();

//    Line *createLine(QQuickItem *parent = nullptr) const;
//    Contact *createContact(QQuickItem *parent = nullptr) const;
//    Coil *createCoil(QQuickItem *parent = nullptr) const;

    template <typename T>
    T *create(QQuickItem *parent = nullptr, QSizeF size = {0,0},
              std::function<void(T *obj)> initFunction = nullptr) const;
    template <typename T>
    T *create(QSizeF size, std::function<void(T *obj)> initFunction= nullptr) const;

private:
    template <typename T>
    T *initObject(T * obj, QSizeF size) const;

    /*!
     * \brief Przypisywana klasa Painter
     * \see setPainter, getPainter
     */
    Painter *painter_;
};



//---------------------------------------


/*!
 * \brief Ustawia obiektowi właściwości wspólne dla wszystkich typów.
 * \tparam T: Typ obiektu.
 * \param obj: Obiekt.
 * \return Wskaźnik do wcześniej przekazanego obiektu.
 */
template <typename T>
T *Ld::Factory::initObject(T *obj, QSizeF size) const
{
    obj->setSize({size.width(), size.height()});
    obj->setPainter(painter_);
    return obj;
}


/*!
 * \brief Alokuje i inicjalizuje obiekt wybranej klasy i zwraca wskaźnik
 *  na niego.
 *
 *  Pozwala wysłać zbiór dodatkowych instrukcji inicjalizujących za pomocą
 *  funkcji, obiektu funkcyjnego lub wyrażenia lambda.
 * \tparam T: Typ tworzonego obiektu
 * \param parent: Rodzic/Element nadrzędny dla tworzonego obiektu.
 * \param initFunction: Dodatkowy instrukcje inicjalizujące.
 * \return Wskaźnik do utworzonego obiektu.
 * \warning Jeśli nie podaliśmy rodzica jako agument funkcji
 * i nie ustawiliśmy mu go, po zakończeniu pracy z obiektem należy go usunąć.
 */
template <typename T>
T *Ld::Factory::create(QQuickItem *parent, QSizeF size,
                       std::function<void(T *obj)> initFunction) const
{
    T * obj = initObject(new T{parent}, size);
    if(initFunction) initFunction(obj);
    return obj;
}


/*!
 * \brief Alokuje i inicjalizuje obiekt wybranej klasy i zwraca wskaźnik
 *  na niego.
 *
 *  Pozwala wysłać zbiór dodatkowych instrukcji inicjalizujących za pomocą
 *  funkcji, obiektu funkcyjnego lub wyrażenia lambda.
 * \tparam T: Typ tworzonego obiektu
 * \param initFunction: Dodatkowe instrukcje inicjalizujące.
 * \return Wskaźnik do utworzonego obiektu.
 * \warning Jeśli nie podaliśmy rodzica jako agument funkcji
 * i nie ustawiliśmy mu go, po zakończeniu pracy z obiektem należy go usunąć.
 */
template <typename T>
T *Ld::Factory::create(QSizeF size,std::function<void(T *obj)> initFunction) const
{
    T * obj = initObject(new T, size);
    if(initFunction) initFunction(obj);
    return obj;
}














} // namespace Ld

#endif // LDFACTORY_HPP
