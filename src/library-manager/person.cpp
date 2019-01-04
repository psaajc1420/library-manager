#include "library-manager/person.h"

std::string Person::GetName() const {
  std::string name = last_name_;
  if (first_name_ != "") {
    name = first_name_ + " " + last_name_; 
  }
  if (middle_name_ != "") {
    name = first_name_ + " " + middle_name_;
    name += ". " + last_name_; 
  }
  return name;
}

bool Person::operator<= (const Person& author) const {
  if (this->last_name_ <= author.last_name_) return true;
  return false;
}

bool Person::operator< (const Person& author) const {
  if (this->last_name_ < author.last_name_) return true;
  return false;
}

std::ostream& operator<< (std::ostream& output, const Person& person) {
  output << person.first_name_ << " ";
  output << person.middle_name_ << " ";
  output << person.last_name_;
  return output;
}