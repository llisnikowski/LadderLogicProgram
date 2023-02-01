#ifndef TEXT_HPP
#define TEXT_HPP

#include "comboboxField.hpp"
#include "output.hpp"

namespace Ld {

/*!
 * \brief Klasa Text udostępnia symbol tekstu.
 *
 * Przechowuje tekst wyświetlany na wyświetlaczu sterownika.
 */
class Text : public Output
{
    Q_OBJECT
public:
    explicit Text(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paintBase(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);
    LdProperty::ComboboxField &getLine();
    LdProperty::TextField &getText();
    LdProperty::TextField &getDisplayParametr();

protected:
    LdProperty::ComboboxField line_;
    LdProperty::TextField text_;
    LdProperty::TextField displayParametr_;
};

} //namespace Ld

#endif // TEXT_HPP
