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

    virtual QByteArray getData() const = 0;
    virtual Type getType() const;

    void setPropertyName(QString propertyName){propertyName_ = propertyName;}
    QString getPropertyName(){return propertyName_;}

protected:
    QString propertyName_;

};

} // namespace LdProperty

#endif // PROPERTYOFLD_HPP
