#ifndef MULTITEXTFIELD_HPP
#define MULTITEXTFIELD_HPP

#include "LdProperty/base.hpp"

namespace LdProperty {

class MultitextField : public Base
{
    Q_OBJECT
    Q_PROPERTY(uint numberOfTexts READ getNumberOfTexts WRITE setNumberOfTexts
                   NOTIFY numberChanged)
    Q_PROPERTY(QStringList textsList MEMBER textsList_ NOTIFY textsListChanged)
public:
    MultitextField(uint number, QQuickItem *parent = nullptr);
    MultitextField &operator=(const MultitextField &multitextField);

    uint getNumberOfTexts() const;
    void setNumberOfTexts(uint n);
    const QStringList &getTextsList() const;
    void setTextsList(QStringList textList);

//public slots:
//    void setTextValue(uint number, QString textValue);
//    QString getTextValue(uint number);// const;

signals:
    void numberChanged();
    void textsListChanged();

protected:
    uint numberOfTexts_;
    QStringList textsList_;
};

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::MultitextField &multitextField);
QDataStream & operator>>(QDataStream &stream, LdProperty::MultitextField &multitextField);

#endif // MULTITEXTFIELD_HPP
