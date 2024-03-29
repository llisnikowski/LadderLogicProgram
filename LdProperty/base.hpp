#ifndef PROPERTYOFLD_HPP
#define PROPERTYOFLD_HPP

#include <QQuickItem>

namespace LdProperty {

class Base : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString propertyName READ getPropertyName WRITE setPropertyName
                   NOTIFY propertyNameChanged)
public:
    explicit Base(QQuickItem *parent = nullptr);
    virtual ~Base() = default;
    Base &operator=(const Base &base);

    void setPropertyName(QString propertyName);
    QString getPropertyName() const {return propertyName_;}

signals:
    void propertyNameChanged();
    void itemFocus(bool);

protected:
    QString propertyName_;
};



} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::Base &base);
QDataStream & operator>>(QDataStream &stream, LdProperty::Base &base);

#endif // PROPERTYOFLD_HPP
