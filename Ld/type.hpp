#ifndef LD_TYPE_HPP
#define LD_TYPE_HPP
#pragma once

namespace Ld {

/*!
 * \brief Enum przechowujący typy obiektów Ld
 */
enum class Type : int {
    None =      0x0000,
    Base =      0x0001,
    Drop =      0x0002 | Base,
    Drag =      0x0004 | Base,
    Node =      0x0008 | Base,
    Line =      0x0010 | Drop,
    Address =   0x0010 | Drag,
    EmptyDrop = 0x0020 | Drop,
    Input =     0x0020 | Address,
    Output =    0x0040 | Address,
    Contact =   0x0100 | Input,
    Weektimer = 0x0200 | Input,
    Coil =      0x0100 | Output,
    Timer =     0x0200 | Output,
    Counter =   0x0400 | Output,
    Text =      0x0800 | Output
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
