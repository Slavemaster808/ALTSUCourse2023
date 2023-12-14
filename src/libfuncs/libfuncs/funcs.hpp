#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct PairHash {
  template <typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2>& p) const {
    std::size_t seed = 0;
    seed ^= std::hash<T1>{}(p.first) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= std::hash<T2>{}(p.second) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

using Salary = std::unordered_map<
    std::pair<std::string, std::string>,
    std::vector<size_t>,
    PairHash>;

namespace altsu {
void printFile(const std::string& filename);

void splitByWords(const std::string& line, std::vector<std::string>& words);

void parseFile(const std::string& filename, Salary& salary);

void getEmpoyeeByMonth(const size_t month, const Salary& salary);

void calculateOverAllAndAverageSalary(const size_t month, const Salary& salary);

void newFile(const Salary& salary);

void addLinesInFile(const std::string& filename);

void deleteLines(const std::string& filename, Salary& salary);

void changeLines(const std::string& filename);
}  // namespace altsu