#ifndef LIBRARY_MANAGER_BORROWER_H
#define LIBRARY_MANAGER_BORROWER_H

#include <string>

#include "library-manager/person.h"

class Borrower: public Person {
 public:
  Borrower() : Person("","","") {}
  explicit Borrower(std::string first_name, std::string middle_name,
                    std::string last_name) 
      : Person(first_name, middle_name, last_name) {}
};
#endif // LIBRARY_MANAGER_BORROWER_H