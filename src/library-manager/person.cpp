#include "library-manager/person.h"

Person::Person(std::string name) {
  SetName(name);
}

Person::Person(std::string first_name, std::string middle_name,
               std::string last_name) {
  SetFirstName(first_name);
  SetMiddleName(middle_name);
  SetLastName(last_name);
}

bool Person::operator<= (const Person& author) const {
  if(this->last_name_ <= author.last_name_ ) return true;
  return false;
}

bool Person::operator< (const Person& author) const {
  if(this->last_name_ < author.last_name_ ) return true;
  return false;
}

std::ostream& operator<< (std::ostream& output, const Person& person) {
  output << person.first_name_ << " ";
  output << person.middle_name_ << " ";
  output << person.last_name_;
  return output;
}