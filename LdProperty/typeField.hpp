#ifndef TYPEFIELD_HPP
#define TYPEFIELD_HPP

#include "LdProperty/comboboxField.hpp"

namespace LdProperty {

class TypeField : public ComboboxField
{
    Q_OBJECT
public:
    TypeField(QQuickItem *parent = nullptr);
    virtual ~TypeField();
    TypeField &operator=(const TypeField &typeField);

    using ComboboxField::operator=;

private:
    void display();

protected:
    QQuickItem *qmlObject_;
};

} // namespace LdProperty

#endif // TYPEFIELD_HPP
