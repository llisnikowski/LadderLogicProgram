/*!
 * \file symbolsBar.hpp
 * \author Łukasz Liśnikowski
*/
#ifndef SYMBOLSBAR_H
#define SYMBOLSBAR_H

#include <QQuickItem>

namespace Ld {
class Painter;

/*!
 * \brief SymbolsBar jest klasą odpowiedzialną za utworzenie paska z symbolami Ld.
 */
class SymbolsBar : public QQuickItem
{
    Q_OBJECT
public:
    SymbolsBar();
    void setLdPainter(Painter *ldPainter);
    Painter *getLdPainter();

public slots:
    void setNewParentItem(QQuickItem *parentItem);

private:
    Painter *ldPainter_;
};


} // namespace Ld

#endif // SYMBOLSBAR_H
