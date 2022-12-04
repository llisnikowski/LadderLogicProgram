#ifndef TYPE_HPP
#define TYPE_HPP

namespace LdProperty {

enum class Type : int {
    None =          0x0000,
    Base =          0x0001,
    TextField =     0x0002 | Base,
    Address =       0x0004 | TextField
};

inline bool operator >=(Type derivative, Type base){
    return !(~static_cast<int>(derivative) & static_cast<int>(base));
}

inline bool operator <(Type derivative, Type base){
    return (~static_cast<int>(derivative) & static_cast<int>(base));
}

bool operator >(Type derivative, Type base) = delete;
bool operator <=(Type derivative, Type base) = delete;


} // namespace LdProperty


#endif // TYPE_HPP
