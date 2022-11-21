#include <iostream>
#include "libs/sqlite/sqlite3.h"
#include "src/headers/models.h"
#include "src/headers/applications.h"

int main(int argc, char argv[]){
  // VerbBlock block = { "hablar", "talk", "hablo", "present", false, false };
  // std::cout << block << std::endl;

  ConsoleApplication app;

  int exit = app.Run();

  return exit;
}

/*
  LEARNINGS:

  & operator - reference operator, can be read as address of variable
  std::string.compare() - returns 0 if equal

*/
