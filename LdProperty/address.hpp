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

    Type getType() const override;

    void display();
private:
    QQuickItem *qmlObject;
};


} // namespace LdProperty

#endif // ADDRESS_HPP
