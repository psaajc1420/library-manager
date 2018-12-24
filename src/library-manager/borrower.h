#ifndef LIBRARY_MANAGER_BORROWER_H
#define LIBRARY_MANAGER_BORROWER_H

#include <string>
#include <vector>

#include "library-manager/person.h"
#include "library-manager/book.h"

class Borrower: public Person {
 public:
  const std::vector<Book>& GetBooks() const;
  void SetBooks(const std::vector<Book>&);
  
 private:
  std::vector<Book> books_;
};
#endif // LIBRARY_MANAGER_BORROWER_H