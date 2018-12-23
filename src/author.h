#ifndef LIBRARY_MANAGER_AUTHOR_H
#define LIBRARY_MANAGER_AUTHOR_H

#include <string>
#include <vector>

class Author {

 public:
  explicit Author(std::string name="");
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
#endif // LIBRARY_MANAGER_AUTHOR_H