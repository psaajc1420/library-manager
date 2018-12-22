#include "book.h"

Book::Book(int pages, int height, int width, 
           std::string title, std::string author_name, 
           std::string borrower_name, bool is_loaned) {
  SetPages(pages);
  SetHeight(height);
  SetWidth(width);
  SetTitle(title);
  SetAuthorName(author_name);
  SetBorrowerName(borrower_name);
  SetIsLoaned(is_loaned);
}

void Book::Print() {
  std::cout << *this;
}

bool Book::operator<= (const Book& book) const {

  if(is_loaned_) {
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
  if(this->GetTitle() == book.GetTitle()) return true;
  return false;
}


std::ostream& operator<< (std::ostream& output, const Book& book) {
  output << "Title: " << book.title_ << std::endl;
  output << "Author Name: " << book.author_name_ << std::endl;
  output << "Borrower Name: " << book.borrower_name_ << std::endl;
  output << "Number of pages: " << book.pages_ << std::endl;
  output << "Height: " << book.height_ << std::endl;
  output << "Width: " << book.width_ << std::endl;
  output << "Area: " << book.GetArea() << std::endl;
  output << "Date: " << book.GetDate().GetDate() << std::endl;
  output << std::endl;
  return output;
}

