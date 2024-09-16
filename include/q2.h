#ifndef Q2_H
#define Q2_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip> // std::setw, std::left

namespace q2 {
	struct Patient {
		std::string name;
		size_t age;
		size_t smokes;
		size_t area_q;
		size_t alkhol;
		size_t risk;
	};

	// 移除名字中的空格
	std::string& remove_space(std::string& name) {
    	// 使用 std::remove 将所有空格字符移到字符串的末尾，并返回新范围的末尾迭代器
    	auto new_end = std::remove(name.begin(), name.end(), ' ');
    	// 使用 std::string::erase 删除从 new_end 到 name.end() 之间的所有字符
    	name.erase(new_end, name.end());
    	// 返回修改后的字符串
    	return name;
	}

	std::vector<Patient> read_file(std::string file_name) {
		std::vector<Patient> patients;
		std::ifstream ifs(file_name);
		std::string line;
		// 如果文件打开失败，输出File not found!
		if (!ifs.is_open()) {
			std::cout << "File not found!" << std::endl;
			return patients;
		}
		// 读取前两行，分别是文件名和列名
		std::getline(ifs, line);
		std::getline(ifs, line);
		// 读取文件中的每一行
		while (std::getline(ifs, line, ',')) {
			// 按行解析文件
			Patient patient;
			patient.name = remove_space(line);
			std::getline(ifs, line, ',');
			patient.name += ' ' + remove_space(line);
			std::getline(ifs, line, ',');
			patient.age = std::stoul(line);
			std::getline(ifs, line, ',');
			patient.smokes = std::stoul(line);
			std::getline(ifs, line, ',');
			patient.area_q = std::stoul(line);
			std::getline(ifs, line);
			patient.alkhol = std::stoul(line);
			// 计算患癌风险
			patient.risk = 3 * patient.age + 5 * patient.smokes + 2 * patient.area_q + 4 * patient.alkhol;
			// 将解析的数据存入patients
			patients.push_back(patient);
		}
		ifs.close();
		return patients;
	}

	// 重载<运算符，当比较两个Patient对象时，比较其风险值
	// 这里由于需要将风险值越高的患者排在前面，故返回值为p1.risk > p2.risk
	bool operator<(const Patient& p1, const Patient& p2) {
		return p1.risk > p2.risk;
	}

	void sort(std::vector<Patient>& patients) {
		// 使用std::sort对patients进行排序
		// 这里sort默认使用<运算符进行排序
		// 故需要重载<运算符
		std::sort(patients.begin(), patients.end());
	}

	void show_patient(std::vector<Patient>& patients) {
		for (auto& patient : patients) {
			std::cout << std::left << std::setw(20) << patient.name << '\t' << patient.age << '\t' 	\
			<< patient.smokes << '\t' << patient.area_q << '\t' 		\
			<< patient.alkhol << '\t' << patient.risk << std::endl;
		}
	}
}

#endif //Q2_H