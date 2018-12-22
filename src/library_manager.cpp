#include "library_manager.h"

LibraryManager::LibraryManager() {
  
  std::string file_name;
  while(true) {
    std::cout << "Enter file name: ";
    std::cin >> file_name;

    infile_.open(file_name);    

    if(!infile_) {
      std::cerr << "Error: file can't be opened as it was not found." << std::endl;
    } else {
      break;
    }
  }

  std::string record_string;
  std::getline(infile_, record_string);
  records_ = stoi(record_string);
}

LibraryManager::LibraryManager(std::string file_name) {

  infile_.open(file_name);    

  if(!infile_) {
    std::cerr << "Error: file can't be opened as it was not found." << std::endl;
  } else {
    std::string record_string;
    std::getline(infile_, record_string);
    records_ = stoi(record_string);
  }
}

void LibraryManager::ReadFile() {

  int pages, height, width;
  int month, day, year;
  std::string title, type;
  std::string author_last_name, author_first_name;
  std::string borrower_last_name, borrower_first_name;
  std::string author_name, borrower_name;
  std::string line;
  while(std::getline(infile_, line)) {
    std::istringstream iss(line);
    iss >> type;
    if(type == "A"){
      iss >> width >> height >> pages;
      iss >> author_last_name >> author_first_name;
      std::getline(iss, title);
      title = title.substr(1);
      author_name = author_first_name + " " + author_last_name; 
      Book book(pages, height, width, title, author_name);
      AddRecord(book);
    } else if(type == "L") {
      iss >> borrower_last_name >> borrower_first_name;
      iss >> month >> day >> year;
      std::getline(iss, title);
      title = title.substr(1);
      borrower_name = borrower_first_name + " " + borrower_last_name;
      Date date(day, month, year);
      LoanRecord(borrower_name, title, date);
    } else if(type == "R") {
      std::getline(iss, title);
      title = title.substr(1);
      ReturnRecord(title);
    } else {
      std::cout << "Something is wrong" << std::endl;
      std::cout << line << std::endl;
    }
  }

  book_shelf_.Sort();
  loaned_books_.Sort();
}

void LibraryManager::AddRecord(Book& book) {
  book_shelf_.PushBack(book);
}

void LibraryManager::LoanRecord(std::string borrower_name,
                                std::string title, Date& date) {

  Book current_book;
  LinkedList<Book>::iterator it;
  for(it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    current_book = *it;
    if (current_book.GetTitle() == title) {
      break;
    }
  }
  current_book.SetBorrowerName(borrower_name);
  current_book.SetDate(date);
  current_book.SetIsLoaned(true);
  loaned_books_.PushBack(current_book);
  book_shelf_.Remove(current_book);
}

void LibraryManager::ReturnRecord(std::string title) {

  Date date;
  Book current_book;
  LinkedList<Book>::iterator it;
  for(it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    current_book = *it;
    if (current_book.GetTitle() == title) {
      break;
    }
  }
  current_book.SetIsLoaned(false);
  current_book.SetDate(date);
  book_shelf_.PushBack(current_book);
  loaned_books_.Remove(current_book);
}


void LibraryManager::WriteFile() {

  int i = 1;
  int month, day, year;
  std::string previous_date;
  Book book;
  LinkedList<Book>::iterator it;

  outfile_.open("book_shelf.txt");
  outfile_ << book_shelf_.Size() << std::endl;

  for(it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    book = *it;
    outfile_ << i << ". ";
    outfile_ << book.GetTitle() << " by " << book.GetAuthorName();
    outfile_ << " (" << book.GetHeight() << "x" << book.GetWidth() << ", ";
    outfile_ << book.GetPages() << " p)" << std::endl;
    i++;
  }
  outfile_ << std::endl << std::endl;
  outfile_.close();

  i = 1;
  outfile_.open("books_on_loan.txt");
  outfile_ << loaned_books_.Size() << std::endl;
  for(it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    book = *it;
    month = book.GetDate().GetMonth();
    day = book.GetDate().GetDay();
    year = book.GetDate().GetYear();
    if(previous_date != book.GetDate().GetDate()) {
      if(day < 10) {
        outfile_ << month << "/" << 0 << day << "/" << year << std::endl;
      } else {
        outfile_ << month << "/" << day << "/" << year << std::endl;
      }
    }
    outfile_ << i << ". ";
    outfile_ << book.GetTitle() << " by " << book.GetAuthorName();
    outfile_ << " (" << book.GetHeight() << "x" << book.GetWidth() << ", ";
    outfile_ << book.GetPages() << " p)" << std::endl;
    previous_date = book.GetDate().GetDate();
    i++;
  }
}