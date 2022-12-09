/*!
 * \file factoryContainer.cpp
 * \brief
 * \author Łukasz Liśnikowski
*/

#include "factoryContainer.hpp"


namespace Ld{

/*!
 * \brief Konstructor klasy FactoryContainer.
 */
FactoryContainer::FactoryContainer()
    :factory_{}
{
}

/*!
 * \brief Ustawia wewnętrzny wskaźnik na podany obiekt.
 *
 * Wywołuje również wirtualną metodę changedFactory().
 * \param factory: wskaźnik do obiektu Factory.
 */
void FactoryContainer::setFactory(Factory *factory)
{
    factory_ = factory;
    changedFactory();
}

/*!
 * \brief Zwraca przechowywany obiekt Factory.
 * \return Wskaźnik na obiekt Factory.
 */
Factory *FactoryContainer::getFactory()
{
    return factory_;
}

/*!
 * \brief Wirtualna metoda wywoływana w momencie zmiany obiektu metodą
 * setFactory().
 */
void FactoryContainer::changedFactory()
{
}


} // namespace Ld
