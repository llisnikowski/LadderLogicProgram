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

    Type getType() const override;
    QByteArray getData() const override;

    void setTextValue(QString textValue);
    QString getTextValue();

private:
    bool validText();

signals:
    void textValueChanged();

protected:
    QString textValue_;
};

} // namespace LdProperty

#endif // TEXTFIELD_HPP
