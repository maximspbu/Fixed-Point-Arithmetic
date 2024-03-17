#include "fixp.h"

int main(){
    double n1 = 1.23;
    int e1 = 16;
    double n2 = 2.4722;
    int e2 = 16;
    FixedPointArithmetic<double, int> num1(n1, e1);
    FixedPointArithmetic<double, int> num2(n2, e2);
    std::cout << num1;
    std::cout << num2;
    std::cout << num1 + num2;
    return 0;
}
