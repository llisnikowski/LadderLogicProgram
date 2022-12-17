/*!
 * \file factory.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <QObject>
#include <QQuickItem>
#include <functional>
#include "selectItem.hpp"

namespace Ld {
class Base;
class Line;
class Contact;
class Coil;
} // namespace Ld


/*!
 * \brief Klasą Factory jest odpowiedzialną za tworzenie obiektów symboli Ld
 * i inicjalizacje ich odpowiednimi zmiennymi (np. rozmiar obiektu).
 */
class FactoryLd
{
public:
    FactoryLd() = delete;

    static void setSelectItem(SelectItem *selectItem);
    static SelectItem *getSelectItem();

    template <typename T>
    static T *create(QQuickItem *parent,
                     std::function<void(T *obj)> initFunction = nullptr);

    template <typename T>
    static T *initObject(T * obj, std::function<void(T *obj)> initFunction = nullptr);

private:
    template <typename T>
    static T *basicInit(T * obj);

    static SelectItem *selectItem_;
};



//---------------------------------------


template <typename T>
T *FactoryLd::basicInit(T * obj)
{
    if(selectItem_) selectItem_->addItemToList(obj);
    return obj;
}


template <typename T>
T *FactoryLd::initObject(T * obj, std::function<void(T *obj)> initFunction)
{
    if(!obj) return obj;
    basicInit(obj);
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
T *FactoryLd::create(QQuickItem *parent, std::function<void(T *obj)> initFunction)
{
    T * obj = new T{parent};
    initObject(obj, initFunction);
    return obj;
}
















#endif // LDFACTORY_HPP
