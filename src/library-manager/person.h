#ifndef LIBRARY_MANAGER_PERSON_H
#define LIBRARY_MANAGER_PERSON_H

#include <iostream>
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

  bool operator< (const Person&) const;
  bool operator<= (const Person&) const;
  friend std::ostream& operator<< (std::ostream&, const Person&);
 protected:
  std::string name_;
  std::string first_name_;
  std::string middle_name_;
  std::string last_name_;
};

inline std::string Person::GetName() const { return name_; }
inline void Person::SetName(std::string name) { name_ = name; }
inline std::string Person::GetFirstName() const { return first_name_; }
inline void Person::SetFirstName(std::string first_name) { 
  first_name_ = first_name; 
}
inline std::string Person::GetMiddleName() const { return middle_name_; }
inline void Person::SetMiddleName(std::string middle_name) { 
  middle_name_ = middle_name; 
}
inline std::string Person::GetLastName() const { return last_name_; }
inline void Person::SetLastName(std::string last_name) { 
  last_name_ = last_name; 
}

#endif // LIBRARY_MANAGER_PERSON_H 