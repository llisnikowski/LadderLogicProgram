#ifndef ADDRESSFIELD_HPP
#define ADDRESSFIELD_HPP

#include "LdProperty/textField.hpp"

namespace LdProperty {

class AddressField : public TextField
{
    Q_OBJECT
public:
    AddressField(QQuickItem *parent = nullptr);
    virtual ~AddressField();
    AddressField &operator=(const AddressField &addressField);

private:
    void display();

protected:
    QQuickItem *qmlObject_;
};

} // namespace LdProperty


#endif // ADDRESSFIELD_HPP
