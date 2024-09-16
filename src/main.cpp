#include <iostream>
#include <gtest/gtest.h>

// 这里把几个头文件的include都注释，是因为unit_test.cpp中已经包含了这些头文件
// 而本题要求在头文件中定义函数，如果重复include，会导致函数重复定义
// 其实最合理的方式应该是将这些函数定义在cpp文件中，然后在头文件中声明
// #include "q1.h"
// #include "q2.h"
// #include "q3.h"
// #include "q4.h"

int main(int argc, char **argv)
{
    if (false) // make false to run unit-tests
    {
        // debug section
        // std::string pattern = "\\d- flight_number:(.+) - duration:(.+) - connections:(\\d+) - connection_times:(.+) - price:(\\d+)";
        // std::regex r(pattern);
        // std::smatch results;
        // std::string line;
        // std::vector<q3::Flight> flights;
// 
        // // 模拟输入数据
        // std::vector<std::string> input_data = {
        //     "1- flight_number:QR492 - duration:11h30m - connections:3 - connection_times:2h,1h30m,4h15m - price:250",
        //     "2- flight_number:QR720 - duration:12h45m - connections:1 - connection_times:1h - price:200",
        //     "3- flight_number:9724 - duration:13h - connections:2 - connection_times:5h15m,2h45m - price:175",
        //     "4- flight_number:9725 - duration:9h - connections:1 - connection_times:1h - price:150",
        //     "5- flight_number:MA127 - duration:13h30m - connections:1 - connection_times:3h - price:150",
        //     "6- flight_number:GH758 - duration:24h10m - connections:2 - connection_times:3h,1h15m - price:550"
        // };
// 
        // for (const auto& line : input_data) {
        //     std::cout << line << std::endl;
        //     if (std::regex_match(line, results, r)) {
        //         q3::Flight flight;
        //         flight.flight_number = results.str(1);
        //         flight.duration = q3::convert_time(results.str(2));
        //         flight.connections = std::stoi(results.str(3));
        //         flight.connection_times = q3::concat_times(results.str(4));
        //         flight.price = std::stoi(results.str(5));
        //         flights.push_back(flight);
        //     } else {
        //         throw std::runtime_error("Flight format error!");
        //     }
        // }
        // for (const auto& flight : flights) {
        //     std::cout << flight.flight_number << " " << flight.duration << " " << flight.connections << " " << flight.connection_times << " " << flight.price << std::endl;
        // }
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}