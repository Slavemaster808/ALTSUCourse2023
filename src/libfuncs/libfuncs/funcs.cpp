#include <libfuncs/funcs.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

namespace altsu {
void printFile(const std::string& filename) {
  std::string line;
  std::ifstream file(filename);

  while (std::getline(file, line)) {
    std::cout << line << '\n';
  }
}

void splitByWords(const std::string& line, std::vector<std::string>& words) {
  size_t initPosition = line.find_first_not_of(' ', 0);
  size_t position = line.find(' ', initPosition);

  while (position != std::string::npos) {
    words.push_back(line.substr(initPosition, position - initPosition));
    initPosition = line.find_first_not_of(' ', position);
    position = line.find(' ', initPosition);
  }
  if (initPosition != std::string::npos) {
    words.push_back(line.substr(initPosition, line.size()));
  }
}

void parseFile(const std::string& filename, Salary& salary) {
  std::string line;
  std::ifstream file(filename);

  while (std::getline(file, line)) {
    std::vector<std::string> words;
    splitByWords(line, words);

    std::vector<size_t> numbers;
    for (size_t i = 3; i < words.size(); i++) {
      numbers.push_back(std::stoi(words[i]));
    }

    std::pair<std::string, std::string> key =
        std::make_pair(words[0] + " " + words[1], words[2]);
    salary.insert(std::make_pair(key, numbers));
  }

  //   for (const auto& entry : salary) {
  //     const auto& key = entry.first;
  //     const auto& salaries = entry.second;

  //     std::cout << "Name: " << key.first << " " << key.second << std::endl;
  //     std::cout << "Salaries: ";
  //     for (const auto& salary : salaries) {
  //       std::cout << salary << " ";
  //     }
  //     std::cout << std::endl;
  //   }
}

void getEmpoyeeByMonth(const size_t month) {
  Salary salary;
  parseFile("./data.txt", salary);

  for (const auto& entry : salary) {
    const auto& key = entry.first;
    const auto& salaries = entry.second;

    std::cout << key.first << " " << key.second << " " << salaries[month - 1]
              << std::endl;
  }
}

void calculateOverAllAndAverageSalary(
    const size_t month,
    const Salary& salary) {
  std::unordered_map<std::string, double> mapForSalaries;

  for (const auto& entry : salary) {
    const auto& key = entry.first;
    const auto& salaries = entry.second;

    mapForSalaries[key.second] += static_cast<double>(salaries[month - 1]);
  }

  std::cout << "Overall salary:\n";
  for (const auto& i : mapForSalaries) {
    std::cout << i.first << ": " << i.second << '\n';
  }

  std::cout << "Average salary:\n";
  for (const auto& i : mapForSalaries) {
    std::cout << i.first << ": " << i.second / mapForSalaries.size() << '\n';
  }
}

void newFile(const Salary& salary) {
  std::ofstream file("./datadir/newfile.txt", std::ios::app);

  for (const auto& entry : salary) {
    const auto& key = entry.first;
    const auto& salaries = entry.second;
    size_t salaryPerYear = 0;

    for (const auto& i : salaries) {
      salaryPerYear += i;
    }

    file << key.first << " " << key.second << " " << salaryPerYear << '\n';
  }
}
}  // namespace altsu