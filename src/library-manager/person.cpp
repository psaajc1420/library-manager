#include "library-manager/person.h"

Person::Person(std::string name) {
  SetName(name);
}

Person::Person(std::string first_name,
               std::string middle_name,
               std::string last_name) {
  SetFirstName(first_name);
  SetMiddleName(middle_name);
  SetLastName(last_name);
}