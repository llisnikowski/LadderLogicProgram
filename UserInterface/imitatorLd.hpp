#ifndef IMITATORLD_HPP
#define IMITATORLD_HPP

#include <drag.hpp>

class ImitatorLd : public Ld::Drag
{
    Q_OBJECT
public:
    ImitatorLd(QQuickItem *parent = nullptr);
    Base *clone(QQuickItem *parent = nullptr) override;

    void paintBase(QPainter *painter) override;

    Ld::Type getType() const override;
    QByteArray getData() const override;
    void setType(Ld::Type type);

private:
    Ld::Type type_;
};

#endif // IMITATORLD_HPP
