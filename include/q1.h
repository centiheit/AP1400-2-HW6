#ifndef Q1_H
#define Q1_H

#include <functional>

namespace q1 {
    // delta: 用于中心差分法求梯度的步长
    const double delta = 1e-3;
    // epsilon: 用于判断梯度是否为0
    const double epsilon = 1e-10;

    // 中心差分法求梯度
    double central_difference(double x, const std::function<double(double)>& func) {
        return (func(x + delta) - func(x - delta)) / (2 * delta);
    }
    
    // std::function<double(double)> 的意思是函数func接收一个double参数，返回一个double参数
    double gradient_descent(double init, double step, std::function<double(double)> func) {
        double x = init;
        double grad = central_difference(x, func);
        // 当梯度不为0时，继续迭代
        while(grad > epsilon || grad < -epsilon) {
            x -= step * grad;
            grad = central_difference(x, func);
        }
        return x;
    }

    // 构建模板gradient_descent函数
    template <typename T, typename F>
    T gradient_descent(T init, T step) {
        return gradient_descent(init, step, F{});
    }
}

#endif //Q1_H