#include "text.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"
#include <QRegularExpression>

namespace Ld {

Text::Text(QQuickItem *parent)
    :Output{parent}, line_{this}, text_{this}, displayParametr_{this}
{
    addProperty(&line_);
    line_.setPropertyName("Nr linii");
    line_.setModel({"0", "1", "2", "3", "4" ,"5", "6", "7"});

    addProperty(&text_);
    text_.setPropertyName("Tekst");
    text_.setPlaceholder("Tekst");
    text_.setRegExp("^[\\x20-\\x7E]{0,25}$");

    addProperty(&displayParametr_);
    displayParametr_.setPropertyName("Parametr");
    displayParametr_.setPlaceholder("C/T##");
    displayParametr_.setRegExp("^[CcTt](0?\\d|[1-2]\\d|3[01])$");

    address_.setPlaceholder("X##");
    address_.setRegExp("^[Xx](0?\\d|[1-2]\\d|3[01])$");
}

Base *Text::clone(QQuickItem *parent)
{
    Text *copyObject = new Text{parent};
    copyObject->address_ = this->address_;
    copyObject->line_ = this->line_;
    copyObject->text_ = this->text_;
    copyObject->displayParametr_ = this->displayParametr_;
    return copyObject;
}

/*!
 * \brief Funkcja rysująca obiekt na ekranie
 */
void Text::paintBase(QPainter *painter)
{
    PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    painterLd.drawCoil();
    painterLd.printCenterLetter('X');

    if(selected_){
        painter->setPen(QPen(Qt::black, 2));
        painterLd.drawFrame();
    }
}

Type Text::getType() const
{
    return Type::Text;
}

QByteArray Text::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_
               << line_ << text_ << displayParametr_;
    return itemData;
}

LdProperty::ComboboxField &Text::getLine()
{
    return line_;
}

LdProperty::TextField &Text::getText()
{
    return text_;
}

LdProperty::TextField &Text::getDisplayParametr()
{
    return displayParametr_;
}


} //namespace Ld
