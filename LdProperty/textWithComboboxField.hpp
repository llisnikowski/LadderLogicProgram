#ifndef TIMERFIELD_HPP
#define TIMERFIELD_HPP

#include "LdProperty/textField.hpp"

namespace LdProperty {

class TextWithComboboxField : public TextField
{
    Q_OBJECT
    Q_PROPERTY(int units READ getUnits WRITE setUnits NOTIFY unitsChanged)
    Q_PROPERTY(QStringList model READ getModel NOTIFY modelChanged)
    Q_PROPERTY(bool textIsValid READ textIsValid NOTIFY textValueChanged)
public:
    TextWithComboboxField(QQuickItem *parent = nullptr);
    TextWithComboboxField &operator=(const TextWithComboboxField &obj);

    void setUnits(int units);
    int getUnits() const;
    const QStringList &getModel() const;
    void setModel(const QStringList &model);
    void setModel(const QStringList &&model);

signals:
    void unitsChanged();
    void modelChanged();

protected:
    int units_;
    QStringList model_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::TextWithComboboxField &obj);
QDataStream & operator>>(QDataStream &stream, LdProperty::TextWithComboboxField &obj);

#endif // TIMERFIELD_HPP
