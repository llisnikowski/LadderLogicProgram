/*!
 * \file coil.cpp
 * \author Łukasz Liśnikowski
*/

#include "coil.hpp"
#include "painter.hpp"
#include "type.hpp"
#include <QDebug>
#include <QPainter>
#include <QRectF>


namespace Ld {

/*!
 * \brief Konstructor klasy Coil
 * \param parent: rodzic/element nadrzędny
 */
Coil::Coil(QQuickItem *parent)
    :Output(parent), type_{this}
{
    addProperty(&type_);
    type_.setModel({"Normal", "Set", "Reset"});
    QObject::connect(&type_, &LdProperty::ComboboxField::valueChanged,
                     this, &QQuickItem::update);
    QObject::connect(&type_, &LdProperty::ComboboxField::itemFocus,
                     this, [this](bool focus){if(focus) emit clicked();});
}

Base *Coil::clone(QQuickItem *parent)
{
    Coil *copyObject = new Coil{parent};
    copyObject->address_ = this->address_;
    copyObject->type_ = this->type_;
    return copyObject;
}

Type Coil::getType() const
{
    return Type::Coil;
}


void Coil::paint(QPainter *painter)
{
    if(ldPainter_)
        ldPainter_->drawCoil(painter, size(), getSelectedFlag());

    painter->setPen(QPen(Qt::white, 2));
    if(type_.getValue()){
        QFont font = painter->font();
        font.setPixelSize(16*height()/64);
        font.setBold(true);
        painter->setFont(font);
        QRectF rectFont = boundingRect();
        rectFont.setHeight(rectFont.height()*0.95);
        if(type_.getValue() == 1){
            painter->drawText(rectFont, Qt::AlignCenter, tr("S"));
        }
        else if(type_.getValue() == 2){
            painter->drawText(rectFont, Qt::AlignCenter, tr("R"));
        }
    }
}

QByteArray Coil::getData() const
{
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << QString("Ld") << static_cast<int>(getType()) << address_ << type_;
    return itemData;
}


} //namespace Ld
