#include "LdProperty/base.hpp"


namespace LdProperty{

Base::Base(QQuickItem *parent)
    : QQuickItem{parent}
{

}

Type Base::getType() const
{
    return Type::Base;
}

} // namespace LdProperty


