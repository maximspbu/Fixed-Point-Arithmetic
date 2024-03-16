#include "fixp.h"

template<class T>

FIXP<T>::FIXP(T num, uint8_t intPartSize, uint8_t fracPartSize){
    overflow_ = 0;
    intPart_.resize(intPartSize);
    fracPart_.resize(fracPartSize);
    num >= 0? sign_ = 0: sign_ = 1;
    TransformToBinary<T>(num);
}
