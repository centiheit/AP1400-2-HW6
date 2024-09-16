#ifndef Q4_H
#define Q4_H

namespace q4 {
    struct Vector2D {
        double x{};
        double y{}; 
    };

    struct Sensor {
    	Vector2D pos;
    	double accuracy;    
    };

    Vector2D kalman_filter(std::vector<Sensor> sensors) {
        // 计算测量精度的和
        // 这里 -> 操作符用于指定返回类型
        double sum = 0;
        auto accumulater = [&sum](const Sensor& s) -> void {sum += s.accuracy;};
        for_each(sensors.begin(), sensors.end(), accumulater);

        // 统计每个传感器的权重
        std::vector<double> weight;
        auto weight_builder = [&weight, sum](const Sensor& s) -> void {weight.push_back(s.accuracy / sum);};
        for_each(sensors.begin(), sensors.end(), weight_builder);

        double X = 0;
        size_t i = 0;
        auto w_x = [weight, sensors, &X, &i](const Sensor& s) -> void { X += weight[i] * sensors[i].pos.x; ++i;};
        for_each(sensors.begin(), sensors.end(), w_x);

        double Y = 0;
        i = 0;
        auto w_y = [weight, sensors, &Y, &i](const Sensor& s) -> void { Y += weight[i] * sensors[i].pos.y; ++i;};
        for_each(sensors.begin(), sensors.end(), w_y);

        return Vector2D{X, Y};
    }
}

#endif //Q4_H