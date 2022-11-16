/*!
 * \file symbolsBar.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef SYMBOLSBAR_H
#define SYMBOLSBAR_H


#include <QQuickItem>

namespace Ld {
class Painter;
class Factory;

/*!
 * \brief SymbolsBar jest klasą odpowiedzialną za utworzenie paska z symbolami Ld.
 */
class SymbolsBar : public QQuickItem
{
    Q_OBJECT
public:
    SymbolsBar();
    void setFactory(Factory *factory);
    Factory *getFactory();

public slots:
    void setNewParentItem(QQuickItem *parentItem);

private:
    Factory *factory_;
};


} // namespace Ld

#endif // SYMBOLSBAR_H
