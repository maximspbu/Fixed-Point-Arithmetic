#ifndef FIXP_H
#define FIXP_H


#include <vector>
#include <cstdint>
#include <cmath>
#include <iostream>
#include <algorithm>


template <class T, class E>
class FixedPointArithmetic{
    public:
        FixedPointArithmetic(T num, E e):num_(static_cast<E>(num*pow(2, e))), e_(e){};
        FixedPointArithmetic<T, E> operator+(FixedPointArithmetic<T, E>& fixp){
            FixedPointArithmetic<T, E> fixp_(0, std::max(e_, fixp.e_));
            fixp_.num_ = (num_  << (fixp.e_ - e_)) + fixp.num_;
            return fixp_;
        }
        FixedPointArithmetic<T, E> operator-(FixedPointArithmetic<T, E>& num);
        FixedPointArithmetic<T, E> operator*(FixedPointArithmetic<T, E>& num);
        FixedPointArithmetic<T, E> operator/(FixedPointArithmetic<T, E>& num);
        bool operator<(FixedPointArithmetic<T, E>& num);
        bool operator==(FixedPointArithmetic<T, E>& num);
        bool operator>(FixedPointArithmetic<T, E>& num);
        friend std::ostream& operator<<(std::ostream& os, const FixedPointArithmetic<T, E>& fixp){
            os << "num: " << fixp.num_/pow(2, fixp.e_) << ", e: " << fixp.e_ << '\n';
            return os;
        }
    private:
        E num_;
        E e_;
};

#endif //FIXP_H