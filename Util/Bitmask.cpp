#include "Bitmask.h"

namespace JEngine {

    void Bitmask::set(int index, int value)
    {
        if (value == 0)
            _flags &= !(1 << index);
        else
            _flags |= (1 << index);
    }

    unsigned int Bitmask::get(int index)
    {
        return (_flags >> index) & 1;
    }

    unsigned int Bitmask::operator[](int index)
    {
        return get(index);
    }

    Bitmask& Bitmask::operator<<(int index)
    {
        set(index, 1);
        return *this;
    }

}