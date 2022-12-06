#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include "textField.hpp"

class QQuickItem;

namespace LdProperty {


class Address : public TextField
{
    Q_OBJECT
public:
    Address(QQuickItem *parent = nullptr);
    ~Address();
    Address &operator=(const Address &address); 

    Type getType() const override;

    void display();
private:
    QQuickItem *qmlObject;
};


} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::Address &address);
QDataStream & operator>>(QDataStream &stream, LdProperty::Address &address);



#endif // ADDRESS_HPP
