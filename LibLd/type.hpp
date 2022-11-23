#ifndef LD_TYPE_HPP
#define LD_TYPE_HPP
#pragma once

namespace Ld {

enum class Type : int {
    None =      0x0000,
    Base =      0x0001,
    Drop =      0x0002 | Base,
    Drag =      0x0004 | Base,
    Node =      0x0008 | Base,
    Line =      0x0010 | Drop,
    Input =     0x0010 | Drag,
    Output =    0x0020 | Drag,
    Contact =   0x0100 | Input,
    Coil =      0x0100 | Output
};

inline bool operator >=(Type derivative, Type base){
    return !(~static_cast<int>(derivative) & static_cast<int>(base));
}

inline bool operator <(Type derivative, Type base){
    return (~static_cast<int>(derivative) & static_cast<int>(base));
}

bool operator >(Type derivative, Type base) = delete;
bool operator <=(Type derivative, Type base) = delete;


} // namespace Ld



#endif // TYPE_HPP
