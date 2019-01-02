#include "library-manager/book.h"

Book::Book(int pages, float length, float width, float height,
           std::string title, std::string author_name,
           std::string borrower_name, bool is_loaned) {
  SetPages(pages);
  SetLength(length);
  SetWidth(width);
  SetHeight(height);
  SetTitle(title);
  SetAuthorName(author_name);
  SetBorrowerName(borrower_name);
  SetIsLoaned(is_loaned);
}

void Book::AddAuthor(const std::vector<Author>& authors) {
  for (int i = 0; i < authors.size(); i++) {
    authors_.push_back(authors[i]);
  }
  std::sort(authors_.begin(), authors_.end());
}

void Book::AddAuthor(const Author& author) {
  authors_.push_back(author);
  std::sort(authors_.begin(), authors_.end());
}

void Book::AddAuthor(std::string first_name, std::string middle_name,
                     std::string last_name) {
  authors_.push_back(Author(first_name, middle_name, last_name));
  std::sort(authors_.begin(), authors_.end());
}

bool Book::operator<= (const Book& book) const {
  if (is_loaned_) {
    std::string curr_date = book.GetDate().GetDate();
    std::string this_date = this->GetDate().GetDate();
    if(this_date.compare(curr_date) < 0) {
      return true;
    }
  } else {
    if (book.GetArea() <= this->GetArea()) {
      return true;
    } else if (book.GetArea() == this->GetArea()) {
      if (book.GetPages() <= this->GetPages()) {
        return true;
      }
    }
  }

  return false; 
}

bool Book::operator== (const Book& book) const {
  if (this->GetTitle() == book.GetTitle()) return true;
  return false;
}


std::ostream& operator<< (std::ostream& output, const Book& book) {
  output << "ID: " << book.uid_.id_ << std::endl;
  output << "Title: " << book.title_ << std::endl;
  output << "Authors: " << book.author_name_ << std::endl;
  const std::vector<Author> authors = book.GetAuthors();
  for (auto it = authors.begin(); it != authors.end(); ++it) {
    output << "   " << *it;
  }
  output << "Borrower Name: " << book.borrower_name_ << std::endl;
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
  output << "Authors: " << book_ptr->author_name_ << std::endl;
  const std::vector<Author> authors = book_ptr->GetAuthors();
  for (auto it = authors.begin(); it != authors.end(); ++it) {
    output << "   ";
    output << *it;
    output << std::endl;
  }
  output << "Borrower Name: " << book_ptr->borrower_name_ << std::endl;
  output << "Number of pages: " << book_ptr->pages_ << std::endl;
  output << "Length: " << book_ptr->length_ << std::endl;
  output << "Width: " << book_ptr->width_ << std::endl;
  output << "Height: " << book_ptr->height_ << std::endl;
  output << "Area: " << book_ptr->GetArea() << std::endl;
  output << "Date: " << book_ptr->GetDate().GetDate() << std::endl;
  output << std::endl;
  return output;
}
