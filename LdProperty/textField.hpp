#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "LdProperty/base.hpp"
#include <functional>

namespace LdProperty {

class TextField : public Base
{
    Q_OBJECT
    Q_PROPERTY(QString textValue READ getTextValue WRITE setTextValue NOTIFY textValueChanged)
public:
    TextField(QQuickItem *parent = nullptr);
    TextField &operator=(const TextField &textField);

    Type getType() const override;
    QByteArray getData() const override;

    void setTextValue(QString textValue);
    QString getTextValue() const;

private:
    bool validText();

signals:
    void textValueChanged();

protected:
    QString textValue_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::TextField &textField);
QDataStream & operator>>(QDataStream &stream, LdProperty::TextField &textField);


#endif // TEXTFIELD_HPP
