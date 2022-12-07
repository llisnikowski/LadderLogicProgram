#ifndef PROPERTYOFLD_HPP
#define PROPERTYOFLD_HPP

#include <QQuickItem>
#include "LdProperty/type.hpp"

namespace LdProperty {

class Base : public QQuickItem
{
    Q_OBJECT
public:
    explicit Base(QQuickItem *parent = nullptr);
    virtual ~Base();
    Base &operator=(const Base &base);

    virtual Type getType() const;
    virtual QByteArray getData() const;
    virtual void setVisible(bool visible){};

    void setPropertyName(QString propertyName){propertyName_ = propertyName;}
    QString getPropertyName() const {return propertyName_;}

protected:
    QString propertyName_;
    QQuickItem *qmlObject_;

};



} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::Base &base);
QDataStream & operator>>(QDataStream &stream, LdProperty::Base &base);

#endif // PROPERTYOFLD_HPP
