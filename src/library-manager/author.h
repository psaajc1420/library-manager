#ifndef LIBRARY_MANAGER_AUTHOR_H
#define LIBRARY_MANAGER_AUTHOR_H

#include <iostream>
#include <string>
#include <vector>

#include "library-manager/person.h"
#include "library-manager/uid.h"

class Author : public Person {
  public:
    Author(UID);
    Author(std::string first_name, std::string middle_name,
           std::string last_name) 
        : Person(first_name, middle_name, last_name) {}
    UID GetBookUid() const;
    void SetBookUid(UID);
  private:
    UID book_id_;
  
};
inline UID Author::GetBookUid() const { return book_id_ ; }
inline void Author::SetBookUid(UID book_id) { book_id_ = book_id; }
#endif // LIBRARY_MANAGER_AUTHOR_H