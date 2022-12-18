#include "multitextfield.hpp"

namespace LdProperty {

MultitextField::MultitextField(uint number, QQuickItem *parent)
    :Base{parent}, numberOfTexts_{number}, textsList_{number}
{
}

MultitextField &MultitextField::operator=(const MultitextField &multitextField)
{
    if(this != &multitextField){
        Base::operator=(multitextField);
        this->numberOfTexts_ = multitextField.numberOfTexts_;
        this->textsList_ = multitextField.textsList_;
        emit numberChanged();
        emit textsListChanged();
    }
    return *this;
}

uint MultitextField::getNumberOfTexts() const
{
    return numberOfTexts_;
}

void MultitextField::setNumberOfTexts(uint n)
{
    numberOfTexts_ = n;
    emit numberChanged();
}

const QStringList &MultitextField::getTextsList() const
{
    return textsList_;
}

void MultitextField::setTextsList(QStringList textList)
{
    textsList_ = textList;
    emit textsListChanged();
}

} // namespace LdProperty


QDataStream & operator<<(QDataStream &stream, const LdProperty::MultitextField &multitextField)
{
    stream << static_cast<const LdProperty::Base&>(multitextField) <<
        multitextField.getNumberOfTexts() << multitextField.getTextsList();
    return stream;
}

QDataStream & operator>>(QDataStream &stream, LdProperty::MultitextField &multitextField)
{
    uint numberOfTexts;
    QStringList textList;
    stream >> static_cast<LdProperty::Base&>(multitextField) >> numberOfTexts >> textList;
    multitextField.setNumberOfTexts(numberOfTexts);
    multitextField.setTextsList(textList);
    return stream;
}


