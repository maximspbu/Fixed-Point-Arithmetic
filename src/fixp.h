#ifndef FIXP_H
#define FIXP_H


#include <vector>
#include <cstddef>


template <class T>
class FIXP{
    public:
        FIXP(T num, uint8_t intPartSize, uint8_t fracPartSize);
        T Transform();
        T operator+(Fixp& num);
        T operator-(Fixp& num);
        T operator*(Fixp& num);
        T operator/(Fixp& num);
        bool operator<(Fixp& num);
        bool operator==(Fixp& num);
        bool operator>(Fixp& num);
    private:
        bool sign_;
        std::vector<bool> intPart_;
        std::vector<bool> fracPart_;
        bool overflow_;
};

#endif //FIXP_H