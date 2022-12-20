#ifndef COMBOBOXFIELD_HPP
#define COMBOBOXFIELD_HPP

#include "LdProperty/base.hpp"

namespace LdProperty {

class ComboboxField : public Base
{
    Q_OBJECT
    Q_PROPERTY(int value READ getValue WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QStringList model READ getModel NOTIFY modelChanged)
public:
    ComboboxField(QQuickItem *parent = nullptr);
    ComboboxField &operator=(const ComboboxField &comboboxField);

    void setValue(int value);
    int getValue() const;
    const QStringList &getModel() const;
    void setModel(const QStringList &model);
    void setModel(const QStringList &&model);

signals:
    void valueChanged();
    void modelChanged();

protected:
    int value_;
    QStringList model_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::ComboboxField &comboboxField);
QDataStream & operator>>(QDataStream &stream, LdProperty::ComboboxField &comboboxField);


#endif // COMBOBOXFIELD_HPP
