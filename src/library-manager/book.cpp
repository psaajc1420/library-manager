#include "library-manager/book.h"

void Book::AddAuthor(std::string first_name, std::string middle_name,
                     std::string last_name) {
  authors_.push_back(Author(first_name, middle_name, last_name));
  std::sort(authors_.begin(), authors_.end());
}

void Book::AddBorrower(std::string first_name, std::string middle_name,
                       std::string last_name) {
  borrower_ = Borrower(first_name, middle_name, last_name);
}

bool Book::operator== (const Book& book) const {
  if (this->GetTitle() == book.GetTitle()) return true;
  return false;
}