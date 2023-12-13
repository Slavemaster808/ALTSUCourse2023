#include <libfuncs/funcs.hpp>

int main(void) {
  //   altsu::printFile("./data.txt");
  Salary salary;
  altsu::parseFile("./datadir/data.txt", salary);
  altsu::newFile(salary);
  altsu::printFile("./datadir/newfile.txt");
  //   altsu::getEmpoyeeByMonth(4);
  //   altsu::calculateOverAllAndAverageSalary(4, salary);
}