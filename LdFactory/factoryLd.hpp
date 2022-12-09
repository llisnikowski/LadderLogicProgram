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
} // namespace Ld

/*!
 * \brief Klasą Factory jest odpowiedzialną za tworzenie obiektów symboli Ld
 * i inicjalizacje ich odpowiednimi zmiennymi (np. rozmiar obiektu).
 */
class FactoryLd
{
public:
    FactoryLd() = delete;
    static void setPainter(Ld::Painter *painter);
    static Ld::Painter *getPainter();

    template <typename T>
    static T *create(QQuickItem *parent = nullptr, QSizeF size = {0,0},
              std::function<void(T *obj)> initFunction = nullptr);
    template <typename T>
    static T *create(QSizeF size, std::function<void(T *obj)> initFunction= nullptr);

private:
    template <typename T>
    static T *initObject(T * obj, QSizeF size);

    /*!
     * \brief Przypisywana klasa Painter
     * \see setPainter, getPainter
     */
    static Ld::Painter *painter_;
};



//---------------------------------------


/*!
 * \brief Ustawia obiektowi właściwości wspólne dla wszystkich typów.
 * \tparam T: Typ obiektu.
 * \param obj: Obiekt.
 * \return Wskaźnik do wcześniej przekazanego obiektu.
 */
template <typename T>
T *FactoryLd::initObject(T *obj, QSizeF size)
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
T *FactoryLd::create(QQuickItem *parent, QSizeF size,
                       std::function<void(T *obj)> initFunction)
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
T *FactoryLd::create(QSizeF size,std::function<void(T *obj)> initFunction)
{
    T * obj = initObject(new T, size);
    if(initFunction) initFunction(obj);
    return obj;
}
















#endif // LDFACTORY_HPP
