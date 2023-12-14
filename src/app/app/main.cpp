#include <libfuncs/funcs.hpp>

#include <fstream>
#include <iostream>
#include <string>

int main(void) {
  // altsu::printFile("./data.txt");
  // Salary salary;
  // altsu::parseFile("./data.txt", salary);
  // altsu::newFile(salary);
  // altsu::printFile("./datadir/newfile.txt");
  // altsu::addLinesInFile("./data.txt");
  //   altsu::getEmpoyeeByMonth(4);
  //   altsu::calculateOverAllAndAverageSalary(4, salary);

  // altsu::deleteLines("./data.txt", salary);
  // altsu::changeLines("./data.txt");
  while (true) {
    std::cout << "Enter filename: ";
    std::string filename;
    std::getline(std::cin, filename);
    std::ifstream file(filename);

    if (!file.is_open()) {
      std::cout << "File not found." << '\n';
    } else {
      Salary salary;
      altsu::parseFile(filename, salary);
      std::string option;
      std::cout << "Choose option:" << '\n'
                << "1. Print file." << '\n'
                << "2. Calculate salary." << '\n'
                << "3. Create new salary file." << '\n'
                << "4. Add line in file." << '\n'
                << "5. Delete line in file." << '\n'
                << "6. Change office." << '\n';

      std::getline(std::cin, option);
      size_t choose = std::stoi(option);

      switch (choose) {
        case 1:
          altsu::printFile(filename);
          break;
        case 2:
          std::cout << "Enter month: ";
          size_t month;
          std::cin >> month;
          altsu::calculateOverAllAndAverageSalary(month, salary);
          break;
        case 3:
          altsu::newFile(salary);
          break;
        case 4:
          altsu::addLinesInFile(filename);
          break;
        case 5:
          altsu::deleteLines(filename, salary);
          break;
        case 6:
          altsu::changeLines(filename);
          break;
        default:
          std::cout << "No such option.";
          break;
      }
    }
    std::cout << "Do You want to continue? (1/0): ";
    std::string option;
    std::getline(std::cin, option);
    size_t choose = std::stoi(option);
    if (choose == 0) {
      break;
    }
  }
}