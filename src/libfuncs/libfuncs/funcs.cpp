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

void getEmpoyeeByMonth(const size_t month, const Salary& salary) {
  // Salary salary;
  // parseFile("./data.txt", salary);

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
  std::ofstream file("./newfile.txt", std::ios::app);

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

void addLinesInFile(const std::string& filename) {
  std::ofstream file(filename, std::ios::app);
  std::string line;

  std::cout << "Enter line: ";
  std::getline(std::cin, line);
  file << line << '\n';
}

void deleteLines(const std::string& filename, Salary& salary) {
  std::string deleteLine;

  std::cout << "Enter employee to delete: ";
  std::getline(std::cin, deleteLine);

  for (auto it = salary.begin(); it != salary.end();) {
    if (it->first.first == deleteLine) {
      it = salary.erase(it);
    } else {
      ++it;
    }
  }

  std::ofstream temp("temp.txt");
  for (const auto& entry : salary) {
    const auto& key = entry.first;
    const auto& salaries = entry.second;

    temp << key.first << " " << key.second << " ";
    for (const auto& i : salaries) {
      temp << i << " ";
    }
    temp << '\n';
  }

  remove(filename.c_str());
  rename("temp.txt", filename.c_str());
}

void changeLines(const std::string& filename) {
  std::string changeLine, newOffice;

  std::cout << "Enter employee to change: ";
  std::getline(std::cin, changeLine);

  std::cout << "Enter new office: ";
  std::getline(std::cin, newOffice);

  std::string tempLine;
  std::ifstream file(filename);
  std::ofstream temp("temp.txt");
  while (std::getline(file, tempLine)) {
    std::vector<std::string> tempVec;
    splitByWords(tempLine, tempVec);
    std::string str = tempVec[0] + " " + tempVec[1];
    if (str == changeLine) {
      tempVec[2] = newOffice;
      for (const auto& i : tempVec) {
        temp << i << " ";
      }
      temp << '\n';
    } else {
      temp << tempLine << '\n';
    }
  }

  remove(filename.c_str());
  rename("temp.txt", filename.c_str());
}
}  // namespace altsu