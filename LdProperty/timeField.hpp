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
    Q_PROPERTY(bool textIsValid READ textIsValid NOTIFY textValueChanged)
    Q_PROPERTY(QString placeholder READ getPlaceholder WRITE setPlaceholder
                   NOTIFY placeholderChanged)
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

    void setPlaceholder(const QString &textValue);
    void setPlaceholder(QString &&textValue);
    QString getPlaceholder() const;

    void setValidator(std::function<bool(QString &text)>);
    bool textIsValid();

signals:
    void textValueChanged();
    void unitsChanged();
    void modelChanged();
    void placeholderChanged();

protected:
    QString textValue_;
    int units_;
    QStringList model_;
    QString placeholder_;
    std::function<bool(QString &text)> validFunction_;
    bool textIsValid_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::TimeField &timeField);
QDataStream & operator>>(QDataStream &stream, LdProperty::TimeField &timeField);

#endif // TIMERFIELD_HPP
