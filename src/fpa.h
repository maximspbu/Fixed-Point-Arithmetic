#ifndef FIXP_H
#define FIXP_H


#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>


template <class T, class D, class E>
class FixedPointArithmetic{
    public:
        FixedPointArithmetic(T num, E e): delta_(static_cast<D>(num * (1 << e))), e_(e), num_(num){};
        constexpr FixedPointArithmetic<T, D, E> operator+(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (delta_  << (fpa.e_ - e_)) + fpa.delta_: fpa_.delta_ = delta_ + (fpa.delta_ << (e_ - fpa.e_));
            std::cout << fpa.delta_ / static_cast<T>(1L << fpa.e_) << '\n';
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator-(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (delta_  << (fpa.e_ - e_)) - fpa.delta_: fpa_.delta_ = delta_ - (fpa.delta_ << (e_ - fpa.e_));
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator*(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, 2*std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (delta_  << (fpa.e_ - e_)) * fpa.delta_: fpa_.delta_ = delta_ * (fpa.delta_ << (e_ - fpa.e_));
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator/(FixedPointArithmetic<T, D, E>& fpa){
            if (fpa.delta_ == 0){
                throw "Division by zero!";
            }
            FixedPointArithmetic<T, D, E> fpa_(0, 0);
            (e_ < fpa.e_)? fpa_.delta_ = ((delta_  << (fpa.e_-e_) << e_) / fpa.delta_) : fpa_.delta_ = ((delta_ <<fpa.e_) / (fpa.delta_  << (e_-fpa.e_)));
            fpa_.e_ = std::min(e_, fpa.e_);
            return fpa_;
        }
        constexpr void SetNum(){
            num_ = delta_ / static_cast<T>(1 << e_);
        }
        constexpr bool operator<(FixedPointArithmetic<T, D, E>& fpa){
            return delta_ < fpa.delta_;
        }
        constexpr bool operator<=(FixedPointArithmetic<T, D, E>& fpa){
            return delta_ <= fpa.delta_;
        }
        constexpr bool operator==(FixedPointArithmetic<T, D, E>& fpa){
            return delta_ == fpa.delta_;
        }
        constexpr bool operator>(FixedPointArithmetic<T, D, E>& fpa){
            return delta_ > fpa.delta_;
        }
        constexpr bool operator>=(FixedPointArithmetic<T, D, E>& fpa){
            return delta_ >= fpa.delta_;
        }
        friend std::ostream& operator<<(std::ostream& os, const FixedPointArithmetic<T, D, E>& fpa){
            os << "num: " << fpa.delta_ / static_cast<T>(1L << fpa.e_) << ", e: " << fpa.e_ << ", delta: " << fpa.delta_ << '\n';
            return os;
        }
    private:
        T num_;
        D delta_;
        E e_;
};

#endif //FIXP_H