#include "fpa.h"

int main(){
    double n1 = 1.23;
    int64_t e1 = 8;
    double n2 = 2.4722;
    int64_t e2 = 16;
    FixedPointArithmetic<double, int64_t, int64_t> num1(n1, e1);
    FixedPointArithmetic<double, int64_t, int64_t> num2(n2, e2);
    std::cout << num1;
    std::cout << num2;
    std::cout << "add:\n";
    std::cout << num1 + num2;
    std::cout << "subtract:\n";
    std::cout << num1 - num2;
    std::cout << "multiply:\n";
    std::cout << num1 * num2;
    std::cout << "divide:\n";
    std::cout << num2 / num1;
    return 0;
}
