#ifndef FIXP_H
#define FIXP_H


#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>


template <class T, class E>
class FixedPointArithmetic{
    public:
        FixedPointArithmetic(T num, E e): delta_(num * (1 << e)), e_(e), num_(num){};
        constexpr FixedPointArithmetic<T, E> operator+(FixedPointArithmetic<T, E>& fpa){
            FixedPointArithmetic<T, E> fpa_(0, std::max(e_, fpa.e_));
            fpa_.delta_ = (delta_  << (fpa.e_ - e_)) + fpa.delta_;
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, E> operator-(FixedPointArithmetic<T, E>& fpa){
            FixedPointArithmetic<T, E> fpa_(0, std::max(e_, fpa.e_));
            fpa_.delta_ = (delta_  << (fpa.e_ - e_)) - fpa.delta_;
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, E> operator*(FixedPointArithmetic<T, E>& fpa){
            FixedPointArithmetic<T, E> fpa_(0, std::max(e_, fpa.e_));
            fpa_.delta_ = (delta_ * fpa.delta_);
            fpa_.e_ = std::max(e_, fpa.e_) + std::min(e_, fpa.e_);
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, E> operator/(FixedPointArithmetic<T, E>& fpa){
            if (fpa.delta_ == 0){
                throw "Division by zero!";
            }
            FixedPointArithmetic<T, E> fpa_(0, std::max(e_, fpa.e_));
            fpa_.delta_ = (delta_ / fpa.delta_);
            fpa_.e_ = std::max(e_, fpa.e_) - std::min(e_, fpa.e_);
            return fpa_;
        }
        constexpr void SetNum(){
            num_ = delta_ / static_cast<double>(1 << e_);
        }
        constexpr bool operator<(FixedPointArithmetic<T, E>& fpa){
            return delta_ < fpa.delta_;
        }
        constexpr bool operator<=(FixedPointArithmetic<T, E>& fpa){
            return delta_ <= fpa.delta_;
        }
        constexpr bool operator==(FixedPointArithmetic<T, E>& fpa){
            return delta_ == fpa.delta_;
        }
        constexpr bool operator>(FixedPointArithmetic<T, E>& fpa){
            return delta_ > fpa.delta_;
        }
        constexpr bool operator>=(FixedPointArithmetic<T, E>& fpa){
            return delta_ >= fpa.delta_;
        }
        friend std::ostream& operator<<(std::ostream& os, const FixedPointArithmetic<T, E>& fpa){
            os << "num: " << fpa.delta_ / static_cast<double>(1 << fpa.e_) << ", e: " << fpa.e_ << ", delta: " << fpa.delta_ << '\n';
            return os;
        }
    private:
        T num_;
        int64_t delta_;
        E e_;
};

#endif //FIXP_H