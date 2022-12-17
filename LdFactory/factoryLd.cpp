/*!
 * \file factory.cpp
 * \author Łukasz Liśnikowski
*/
#include "factoryLd.hpp"


SelectItem *FactoryLd::selectItem_ = nullptr;

/*!
 * \brief Ustawia klase Painter która będzie przypisana do nowo tworzonych obiektów.
 *
 * Ustwawie również zmienną objectSize_ na podstawie klasy Painter.
 * \param painter: Wskaźnik do klasy Painter.
 */

void FactoryLd::setSelectItem(SelectItem *selectItem)
{
    selectItem_ = selectItem;
}

SelectItem *FactoryLd::getSelectItem()
{
    return selectItem_;
}



















