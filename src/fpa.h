#ifndef FIXP_H
#define FIXP_H


#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>


template <class T, class D, class E>
class FixedPointArithmetic{
    public:
        FixedPointArithmetic(T num, E e): delta_(static_cast<D>(num * (1 << e))), e_(e){};
        constexpr T GetNum(){
            return delta_ / static_cast<T>(1L << e_);
        }
        constexpr FixedPointArithmetic<T, D, E> operator+(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (delta_  << (fpa.e_ - e_)) + fpa.delta_: fpa_.delta_ = delta_ + (fpa.delta_ << (e_ - fpa.e_));
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator-(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (delta_  << (fpa.e_ - e_)) - fpa.delta_: fpa_.delta_ = delta_ - (fpa.delta_ << (e_ - fpa.e_));
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator*(FixedPointArithmetic<T, D, E>& fpa){
            FixedPointArithmetic<T, D, E> fpa_(0, std::max(e_, fpa.e_));
            (e_ < fpa.e_)? fpa_.delta_ = (((delta_  << (fpa.e_ - e_)) * fpa.delta_) >> fpa.e_): fpa_.delta_ = ((delta_ * (fpa.delta_ << (e_ - fpa.e_))) >> e_);
            return fpa_;
        }
        constexpr FixedPointArithmetic<T, D, E> operator/(FixedPointArithmetic<T, D, E>& fpa){
            if (fpa.delta_ == 0){
                throw std::runtime_error("Division by zero!");
            }
            FixedPointArithmetic<T, D, E> fpa_(0, 0);
            (e_ < fpa.e_)? fpa_.delta_ = ((delta_  << (fpa.e_ - e_) << e_) / fpa.delta_) : fpa_.delta_ = ((delta_ << fpa.e_) / (fpa.delta_  << (e_-fpa.e_)));
            fpa_.e_ = std::min(e_, fpa.e_);
            return fpa_;
        }
        constexpr void operator+=(FixedPointArithmetic<T, D, E>& fpa){
            (e_ < fpa.e_)? delta_ = (delta_  << (fpa.e_ - e_)) + fpa.delta_: delta_ = delta_ + (fpa.delta_ << (e_ - fpa.e_));
            e_ = std::max(e_, fpa.e_);
        }
        constexpr void operator-=(FixedPointArithmetic<T, D, E>& fpa){
            (e_ < fpa.e_)? delta_ = (delta_  << (fpa.e_ - e_)) - fpa.delta_: delta_ = delta_ - (fpa.delta_ << (e_ - fpa.e_));
            e_ =  std::max(e_, fpa.e_);
        }
        constexpr void operator*=(FixedPointArithmetic<T, D, E>& fpa){
            (e_ < fpa.e_)? delta_ = (((delta_  << (fpa.e_ - e_)) * fpa.delta_) >> fpa.e_): delta_ = ((delta_ * (fpa.delta_ << (e_ - fpa.e_))) >> e_);
            e_ = std::max(e_, fpa.e_);
        }
        constexpr void operator/=(FixedPointArithmetic<T, D, E>& fpa){
            if (fpa.delta_ == 0){
                throw std::runtime_error("Division by zero!");
            }
            (e_ < fpa.e_)? delta_ = ((delta_  << (fpa.e_ - e_) << e_) / fpa.delta_) : delta_ = ((delta_ << fpa.e_) / (fpa.delta_  << (e_ - fpa.e_)));
            e_ = std::min(e_, fpa.e_);
        }
        constexpr T log2(){
            T log = 0;
            if (delta_ <= 0){
                throw std::runtime_error("Log is not defined!");
            } else if (delta_ == (1 << e_)){
                return log;
            }
            FixedPointArithmetic<T, D, E> fpa(0, e_);
            fpa.delta_ = delta_;
            while (fpa.delta_ > (1 << (e_ + 1))){
                fpa.delta_ /= 2;
                ++log;
            }
            size_t iter = 0;
            for (int m = 1; m < e_; ++m){
                while (fpa.delta_ < (1 << (fpa.e_ + 1))){
                    fpa *= fpa;
                    ++iter;
                    if (iter > 64){
                        return log;
                    }
                }
                if (fpa.delta_ == (1 << (fpa.e_ + 1))){
                    return log;
                }
                log += static_cast<T>(1)/(1 << iter);
                fpa.delta_ /= 2;
            }
            return log;
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
        D delta_;
        E e_;
};

#endif //FIXP_H