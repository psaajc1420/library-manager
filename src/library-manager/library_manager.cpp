#include "library-manager/library_manager.h"

void LibraryManager::Open() {
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
  std::string records;
  std::getline(infile_, records);
  records_ = stoi(records);
}

void LibraryManager::Open(std::string file_name) {
  infile_.open(file_name);    
  if (infile_) {
    std::string records;
    std::getline(infile_, records);
    records_ = stoi(records);
  } else {
    std::cerr << "Error: file can't be opened as it was not found." << std::endl;
  }
}

void LibraryManager::Read(int num_files, char** files) {
  // Reduce by 1 to not include the executable
  num_files -= 1;
  if(num_files == 0) {
    Open();
  } else if (num_files == 1) {
    Open(files[0]);
    ReadBooks();
  } else if (num_files == 2) {
    Open(files[1]);
    ReadBooks();
    Open(files[2]);
    ReadAuthors();
  } else {
    std::cerr << "Shouldn't be more than 2 files given as command line arguments";
    std::cout << std::endl;
  }
}

void LibraryManager::ReadBooks() {
  std::string line, type;
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
    // Clear global string stream object for reuse
    line_.clear();
  }
  infile_.close();

  book_shelf_.Sort(BookOrder);
  loaned_books_.Sort();
}

void LibraryManager::ReadAuthors() {
  std::string author_names, title;
  std::string first_name;
  std::string middle_name;
  std::string last_name;
  for (int i = 0; i < records_; i++) {
    std::getline(infile_, title);
    while (std::getline(infile_, author_names, ',')) {
      std::cout << author_names << std::endl;
    }
  }
  // Clear global string stream object for reuse
  line_.clear();
  infile_.close();
}

const Book LibraryManager::FindBook(std::string title) {
  Book current_book;
  LinkedList<Book>::iterator it;
  for (it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    current_book = *it;
    if (current_book.GetTitle() == title) {
      break;
    }
  }
  return current_book;
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
  Book current_book = FindBook(title);
  current_book.SetBorrowerName(borrower_name);
  current_book.SetDate(date);
  current_book.SetIsLoaned(true);
  loaned_books_.PushBack(current_book);
  book_shelf_.Remove(current_book);
}

void LibraryManager::ReturnRecord() {
  std::string title;
  std::getline(line_, title);
  title = title.substr(1);
  Book current_book = FindBook(title);
  current_book.SetIsLoaned(false);
  book_shelf_.PushBack(current_book);
  loaned_books_.Remove(current_book);
}


void LibraryManager::Write() {
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
  outfile_.close();
}

bool LibraryManager::BookOrder(const Book& book1,
                               const Book& book2) {
  if (book1.GetTitle() <= book2.GetTitle()) return true;
  return false;
}