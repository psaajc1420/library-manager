#ifndef LIBRARY_MANAGER_PERSON_H
#define LIBRARY_MANAGER_PERSON_H

#include <string>

class Person {
 public:
  explicit Person(std::string name="");
  explicit Person(std::string, std::string,
                  std::string);
  std::string GetName() const;
  void SetName(std::string);
  std::string GetFirstName() const;
  void SetFirstName(std::string);
  std::string GetMiddleName() const;
  void SetMiddleName(std::string);
  std::string GetLastName() const;
  void SetLastName(std::string);
  static std::vector<std::string> ParseName();
  static std::string GetInitial(std::string);

 private:
  std::string name_;
  std::string first_name_;
  std::string middle_name;
  std::string last_name_;
};
#endif // LIBRARY_MANAGER_PERSON_H 