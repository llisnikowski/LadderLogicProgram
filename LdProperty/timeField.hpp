#ifndef TIMERFIELD_HPP
#define TIMERFIELD_HPP

#include "LdProperty/base.hpp"

namespace LdProperty {

class TimeField : public Base
{
    Q_OBJECT
    Q_PROPERTY(QString textValue READ getTextValue WRITE setTextValue NOTIFY textValueChanged)
    Q_PROPERTY(int units READ getUnits WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(QStringList model READ getModel NOTIFY modelChanged)
public:
    TimeField(QQuickItem *parent = nullptr);
    TimeField &operator=(const TimeField &timeField);

    void setTextValue(QString textValue);
    QString getTextValue() const;
    void setUnits(int units);
    int getUnits() const;
    const QStringList &getModel() const;
    void setModel(const QStringList &model);
    void setModel(const QStringList &&model);

signals:
    void textValueChanged();
    void unitsChanged();
    void modelChanged();

protected:
    QString textValue_;
    int units_;
    QStringList model_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::TimeField &timeField);
QDataStream & operator>>(QDataStream &stream, LdProperty::TimeField &timeField);

#endif // TIMERFIELD_HPP
