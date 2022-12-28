#include "text.hpp"
#include <QPainter>
#include "painterLd.hpp"
#include "type.hpp"
#include <QRegularExpression>

namespace Ld {

Text::Text(QQuickItem *parent)
    :Output{parent}, texts_{4, this}
{
    addProperty(&texts_);
    texts_.setPropertyName("Text");

    address_.setPlaceholder("X[00-15]");
    address_.setRegExp("^[Xx]((0?\\d)|(1[0-5]))$");
}

Base *Text::clone(QQuickItem *parent)
{
    Text *copyObject = new Text{parent};
    copyObject->address_ = this->address_;
    copyObject->texts_ = this->texts_;
    return copyObject;
}

void Text::paint(QPainter *painter)
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
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_ << texts_;
    return itemData;
}


} //namespace Ld
