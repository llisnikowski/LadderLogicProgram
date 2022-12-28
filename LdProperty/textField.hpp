#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include "LdProperty/base.hpp"
#include <functional>
#include <QRegularExpressionValidator>

namespace LdProperty {

class TextField : public Base
{
    Q_OBJECT
    Q_PROPERTY(QString textValue READ getTextValue WRITE setTextValue NOTIFY textValueChanged)
    Q_PROPERTY(bool textIsValid READ textIsValid NOTIFY textValueChanged)
    Q_PROPERTY(QString placeholder READ getPlaceholder WRITE setPlaceholder
                   NOTIFY placeholderChanged)
    Q_PROPERTY(QObject *regExp READ getRegExp NOTIFY regExpChanged)
public:
    TextField(QQuickItem *parent = nullptr);
    TextField &operator=(const TextField &textField);

    void setTextValue(QString textValue);
    QString getTextValue() const;
    void operator=(QString value);
    operator QString();
    void operator=(int value);
    operator int();

    void setPlaceholder(const QString &textValue);
    void setPlaceholder(QString &&textValue);
    QString getPlaceholder() const;

    void setValidator(std::function<bool(QString &text)>);
    bool textIsValid();

    QObject *getRegExp();
    void setRegExp(QString &&getRegExp);

signals:
    void textValueChanged();
    void placeholderChanged();
    void regExpChanged();

protected:
    QString textValue_;
    QString placeholder_;
    std::function<bool(QString &text)> validFunction_;
    bool textIsValid_;
    QRegularExpressionValidator regExpValidator_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::TextField &textField);
QDataStream & operator>>(QDataStream &stream, LdProperty::TextField &textField);


#endif // TEXTFIELD_HPP
