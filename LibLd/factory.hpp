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

    void setObjectSize(float objectSize);
    float getObjectSize() const;
    void setPainter(Painter *painter);
    Painter *getPainter();

//    Line *createLine(QQuickItem *parent = nullptr) const;
//    Contact *createContact(QQuickItem *parent = nullptr) const;
//    Coil *createCoil(QQuickItem *parent = nullptr) const;

    template <typename T>
    T *create(QQuickItem *parent = nullptr,
              std::function<void(T *obj)> initFunction = nullptr) const;
    template <typename T>
    T *create(std::function<void(T *obj)> initFunction) const;

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



//---------------------------------------


/*!
 * \brief Ustawia obiektowi właściwości wspólne dla wszystkich typów.
 * \tparam T: Typ obiektu.
 * \param obj: Obiekt.
 * \return Wskaźnik do wcześniej przekazanego obiektu.
 */
template <typename T>
T *Ld::Factory::initObject(T *obj) const
{
    obj->setSize({objectSize_, objectSize_});
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
T *Ld::Factory::create(QQuickItem *parent,
                       std::function<void(T *obj)> initFunction) const
{
    T * obj = initObject(new T{parent});
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
T *Ld::Factory::create(std::function<void(T *obj)> initFunction) const
{
    T * obj = new T;
    if(initFunction) initFunction(obj);
    return obj;
}














} // namespace Ld

#endif // LDFACTORY_HPP
