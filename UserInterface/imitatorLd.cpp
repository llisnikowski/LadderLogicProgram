#include "imitatorLd.hpp"
#include "coil.hpp"
#include "contact.hpp"
#include "painterLd.hpp"
#include "timer.hpp"
#include "weektimer.hpp"
#include "counter.hpp"
#include "text.hpp"
#include <QPainter>

ImitatorLd::ImitatorLd(QQuickItem *parent)
    :Ld::Drag{parent}, type_{}
{
}

Ld::Base *ImitatorLd::clone(QQuickItem *parent)
{
    ImitatorLd *copyObject = new ImitatorLd{parent};
    return copyObject;
}

void ImitatorLd::paint(QPainter *painter)
{
    Ld::PainterLd painterLd{painter, size()};
    painter->setPen(QPen(Qt::white, 2));
    if(type_ >= Ld::Type::Input){
        painterLd.drawContact();
        if(type_ == Ld::Type::Weektimer){
            painterLd.printCenterLetter('Z');
        }
    }
    else if(type_ >= Ld::Type::Output){
        painterLd.drawCoil();
        if(type_ == Ld::Type::Timer){
            painterLd.printCenterLetter('T');
        }
        else if(type_ == Ld::Type::Counter){
            painterLd.printCenterLetter('C');
        }
        else if(type_ == Ld::Type::Text){
            painterLd.printCenterLetter('X');
        }
    }
}

Ld::Type ImitatorLd::getType() const
{
    return type_;
}

void ImitatorLd::setType(Ld::Type type)
{
    type_ = type;
}

QByteArray ImitatorLd::getData() const
{
    Ld::Base *obj{};
    if(type_ >= Ld::Type::Input){
        if(type_ == Ld::Type::Contact){
            obj = new Ld::Contact;
        }
        if(type_ == Ld::Type::Weektimer){
            obj = new Ld::Weektimer;
        }
    }
    else if(type_ >= Ld::Type::Output){
        if(type_ == Ld::Type::Coil){
            obj = new Ld::Coil;
        }
        else if(type_ == Ld::Type::Timer){
            obj = new Ld::Timer;
        }
        else if(type_ == Ld::Type::Counter){
            obj = new Ld::Counter;
        }
        else if(type_ == Ld::Type::Text){
            obj = new Ld::Text;
        }
    }
    QByteArray data;
    if(obj){
        data = obj->getData();
    }
    if(obj) delete obj;
    return data;
}



