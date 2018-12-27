#include "library-manager/library_manager.h"

LibraryManager::LibraryManager() {
  std::string file_name;
  while (true) {
    std::cout << "Enter file name: ";
    std::cin >> file_name;
    infile_.open(file_name);    
    if (!infile_) {
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
  if (infile_) {
    std::string record_string;
    std::getline(infile_, record_string);
    records_ = stoi(record_string);
  }
  std::cerr << "Error: file can't be opened as it was not found." << std::endl;
}

LibraryManager::LibraryManager(std::string file_name) {
  infile_.open(file_name);    
  if (!infile_) {
    std::cerr << "Error: file can't be opened as it was not found." << std::endl;
  } else {
    std::string record_string;
    std::getline(infile_, record_string);
    records_ = stoi(record_string);
  }
}

void LibraryManager::ReadFile() {
  int pages, edition;
  float length, width, height;
  int month, day, year;
  std::string title, type;
  std::string author_last_name, author_first_name;
  std::string borrower_last_name, borrower_first_name;
  std::string author_name, borrower_name;
  std::string line;
  while (std::getline(infile_, line)) {
    line_.str(line);
    line_ >> type;
    if (type == "A") {
      AddRecord();
    } else if (type == "L") {
      LoanRecord();
    } else if (type == "R") {
      ReturnRecord();
    } else {
      std::cout << "Something is wrong" << std::endl;
      std::cout << line << std::endl;
    }
  }

  book_shelf_.Sort(BookOrder);
  loaned_books_.Sort();
}

Book* LibraryManager::FindBook(std::string title) {
  Book current_book;
  LinkedList<Book>::iterator it;
  for (it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    current_book = *it;
    if (current_book.GetTitle() == title) {
      return &current_book;
    }
  }
  return nullptr;
}

void LibraryManager::AddRecord() {
  int pages, edition;
  float length, width, height;
  std::string title, type;
  std::string author_last_name, author_first_name;
  std::string author_name;
  line_ >> length >> width >> height >> pages >> edition;
  line_ >> author_last_name >> author_first_name;
  std::getline(line_, title);
  title = title.substr(1);
  author_name = author_first_name + " " + author_last_name; 
  Book book(pages, length, width, height, title, author_name);
  book_shelf_.PushBack(book);
}

void LibraryManager::LoanRecord() {
  int month, day, year;
  std::string title, borrower_name;
  std::string borrower_last_name, borrower_first_name;            
  line_ >> borrower_last_name >> borrower_first_name;
  line_ >> month >> day >> year;
  std::getline(line_, title);
  title = title.substr(1);
  borrower_name = borrower_first_name + " " + borrower_last_name;
  Date date(day, month, year);
  Book* current_book = FindBook(title);
  current_book->SetBorrowerName(borrower_name);
  current_book->SetDate(date);
  current_book->SetIsLoaned(true);
  loaned_books_.PushBack(*current_book);
  book_shelf_.Remove(*current_book);
}

void LibraryManager::ReturnRecord() {
  std::string title;
  std::getline(line_, title);
  title = title.substr(1);
  Book* current_book = FindBook(title);
  current_book->SetIsLoaned(false);
  book_shelf_.PushBack(*current_book);
  loaned_books_.Remove(*current_book);
}


void LibraryManager::WriteFile() {
  int i = 1;
  int month, day, year;
  std::string previous_date;
  Book book;
  LinkedList<Book>::iterator it;

  outfile_.open("book_shelf.txt");
  outfile_ << book_shelf_.Size() << std::endl;

  for (it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    book = *it;
    outfile_ << i << ". ";
    outfile_ << book.GetTitle() << " by " << book.GetAuthorName();
    outfile_ << "(" << book.GetLength() << "x" << book.GetWidth();
    outfile_ << "x" << book.GetHeight() << " in., ";
    outfile_ << book.GetPages() << " pp.)" << std::endl;
    i++;
  }
  outfile_ << std::endl << std::endl;
  outfile_.close();

  i = 1;
  outfile_.open("books_on_loan.txt");
  outfile_ << loaned_books_.Size() << std::endl;
  for (it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    book = *it;
    month = book.GetDate().GetMonth();
    day = book.GetDate().GetDay();
    year = book.GetDate().GetYear();
    if (previous_date != book.GetDate().GetDate()) {
      if (day < 10) {
        outfile_ << month << "/" << 0 << day << "/" << year << std::endl;
      } else {
        outfile_ << month << "/" << day << "/" << year << std::endl;
      }
    }
    outfile_ << i << ". ";
    outfile_ << book.GetTitle() << " by " << book.GetAuthorName();
    outfile_ << "(" << book.GetLength() << "x" << book.GetWidth();
    outfile_ << "x" << book.GetHeight() << " in., ";
    outfile_ << book.GetPages() << " pp.)" << std::endl;
    previous_date = book.GetDate().GetDate();
    i++;
  }
}

bool LibraryManager::BookOrder(const Book& book1,
                               const Book& book2) {
  if (book1.GetTitle() <= book2.GetTitle()) return true;
  return false;
}