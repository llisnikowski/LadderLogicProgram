#ifndef TEXT_HPP
#define TEXT_HPP

#include "output.hpp"
#include "multitextfield.hpp"

namespace Ld {

class Text : public Output
{
    Q_OBJECT
public:
    explicit Text(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paint(QPainter *painter) override;

    Type getType() const override;
    QByteArray getData() const override;
    friend QDataStream & ::operator >>(QDataStream &, Ld::Base **);

protected:
    LdProperty::MultitextField texts_;
};

} //namespace Ld

#endif // TEXT_HPP