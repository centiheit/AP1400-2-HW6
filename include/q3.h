#ifndef Q3_H
#define Q3_H

#include <iostream>
#include <fstream>
#include <queue>
#include <regex> // 使用正则表达式
#include <string>
#include <sstream>

namespace q3 {
	struct Flight {
		std::string flight_number;
		size_t duration;
		size_t connections;
		size_t connection_times;
		size_t price;
	};

	// 将时间转换为分钟
	size_t convert_time(const std::string& time) {
		// * 表示可能匹配零次或多次
		std::string pattern = "(\\d+)h(\\d*)m*";
		std::regex r(pattern);
		std::smatch results;
		size_t converted_time = 0;
		if (std::regex_match(time, results, r)) {
			converted_time += std::stoi(results[1]) * 60;
			if (results[2] != "") {
				converted_time += std::stoi(results[2]);
			}
		}
		return converted_time;
	}

	// connection_times 可能有多个时间段，将其分割并转换为分钟
	size_t concat_times(const std::string& times) {
		std::stringstream ss(times);
		std::string token;
		size_t time = 0;
		while(std::getline(ss, token, ',')) {
			time += convert_time(token);
		}
		// 最后一组时间段没有逗号
		std::getline(ss, token);
		time += convert_time(token);
		return time;
	}

	bool operator<(const Flight& f1, const Flight& f2) {
		size_t priority_f1 = f1.duration + f1.connection_times + 3 * f1.price;
		size_t priority_f2 = f2.duration + f2.connection_times + 3 * f2.price;
		return priority_f1 > priority_f2;
	}

	// std::priority_queue 基于堆实现，默认是最大堆，即每次取出的元素都是队列中的最大值。
	std::priority_queue<Flight> gather_flights(const std::string& file_name) {
		std::ifstream ifs(file_name);
		std::priority_queue<Flight> flights;
		// 正则表达式匹配模式
	    // \\w+ 匹配任意字母数字下划线（多次），\\d+ 匹配任意数字（多次）
	    // std::string pattern = "(\\w+)-(\\w+)-(\\d+\\.\\d+)";
		// 只有用括号括起来的部分才会被存储到results中
		std::string pattern = "\\d- flight_number:(.+) - duration:(.+) - connections:(\\d+) - connection_times:(.+) - price:(\\d+)";
		// 创建正则表达式对象
		std::regex r(pattern);
		// 存储匹配结果
		std::smatch results;
		std::string line;
		while(std::getline(ifs, line)) {
			// 如果匹配成功
			// 这里用search而不用match，是因为match要求整个字符串都匹配，而search只要求部分匹配
			// 我怀疑是因为前面几行的最后一个字符是换行符，导致整个字符串都不匹配
			if (std::regex_search(line, results, r)) {
				Flight flight;
				flight.flight_number = results.str(1);
				flight.duration = convert_time(results.str(2));
				flight.connections = std::stoi(results.str(3));
				flight.connection_times = concat_times(results.str(4));
				flight.price = std::stoi(results.str(5));
				flights.push(flight);
			}
			else {
				throw std::runtime_error("Flight format error!");
			}
		}
		return flights;
	}
}

#endif //Q3_H