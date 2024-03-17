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
        FixedPointArithmetic<T, E> operator+(FixedPointArithmetic<T, E>& fpa){
            FixedPointArithmetic<T, E> fpa_(0, std::max(e_, fpa.e_));
            fpa_.num_ = (num_  << (fpa.e_ - e_)) + fpa.num_;
            return fixp_;
        }
        FixedPointArithmetic<T, E> operator-(FixedPointArithmetic<T, E>& fpa);
        FixedPointArithmetic<T, E> operator*(FixedPointArithmetic<T, E>& fpa);
        FixedPointArithmetic<T, E> operator/(FixedPointArithmetic<T, E>& fpa);
        bool operator<(FixedPointArithmetic<T, E>& fpa);
        bool operator==(FixedPointArithmetic<T, E>& fpa);
        bool operator>(FixedPointArithmetic<T, E>& fpa);
        friend std::ostream& operator<<(std::ostream& os, const FixedPointArithmetic<T, E>& fpa){
            os << "num: " << fpa.num_/pow(2, fpa.e_) << ", e: " << fpa.e_ << '\n';
            return os;
        }
    private:
        E num_;
        E e_;
};

#endif //FIXP_H