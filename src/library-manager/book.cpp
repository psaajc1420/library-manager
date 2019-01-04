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

std::ostream& operator<< (std::ostream& output, const Book& book) {
  output << "ID: " << book.uid_.id_ << std::endl;
  output << "Title: " << book.title_ << std::endl;
  output << "Authors: " << std::endl;
  const std::vector<Author> authors = book.GetAuthors();
  for (auto it = authors.begin(); it != authors.end(); ++it) {
    output << "   " << *it;
  }
  output << "Borrower Name: " << book.borrower_.GetName() << std::endl;
  output << "Number of pages: " << book.pages_ << std::endl;
  output << "Length: " << book.length_ << std::endl;
  output << "Width: " << book.width_ << std::endl;
  output << "Height: " << book.height_ << std::endl;
  output << "Area: " << book.GetArea() << std::endl;
  output << "Date: " << book.GetDate().GetDate() << std::endl;
  output << std::endl;
  return output;
}

std::ostream& operator<< (std::ostream& output, 
                          const std::unique_ptr<Book>& book_ptr) {
  output << "ID: " << book_ptr->uid_.id_ << std::endl;
  output << "Title: " << book_ptr->title_ << std::endl;
  output << "Authors: " << std::endl;
  const std::vector<Author> authors = book_ptr->GetAuthors();
  for (auto it = authors.begin(); it != authors.end(); ++it) {
    output << "   " << *it << std::endl;
  }
  output << "Borrower Name: " << book_ptr->borrower_.GetName() << std::endl;
  output << "Number of pages: " << book_ptr->pages_ << std::endl;
  output << "Length: " << book_ptr->length_ << std::endl;
  output << "Width: " << book_ptr->width_ << std::endl;
  output << "Height: " << book_ptr->height_ << std::endl;
  output << "Area: " << book_ptr->GetArea() << std::endl;
  output << "Date: " << book_ptr->GetDate().GetDate() << std::endl;
  output << std::endl;
  return output;
}