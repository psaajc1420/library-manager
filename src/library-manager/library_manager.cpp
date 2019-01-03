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
}

void LibraryManager::Open(std::string file_name) {
  infile_.open(file_name);    
  if (!infile_) {
    std::cerr << "Error: file can't be opened as it was not found." << std::endl;
  }
}

void LibraryManager::Read(int num_files, char** files) {
  // Reduce by 1 to not include the executable
  num_files -= 1;
  if(num_files == 0) {
    Open();
  } else if (num_files == 1) {
    Open(files[1]);
    ReadAddedBooks();
  } else if (num_files == 2) {
    Open(files[1]);
    ReadAddedBooks();
    Open(files[2]);
    ReadAuthors();
  } else if (num_files == 3) {
    Open(files[1]);
    ReadAddedBooks();
    Open(files[2]);
    ReadAuthors();
    Open(files[3]);
    ReadLoanedBooks();
  } else {
    std::cerr << "Shouldn't be more than 2 files given as command line arguments";
    std::cout << std::endl;
  }
  book_shelf_.Sort(BookShelfOrder);
  loaned_books_.Sort(LoanedBookOrder);
}

void LibraryManager::ReadAddedBooks() {
  std::string line, type;
  while (std::getline(infile_, line)) {
    line_.str(line);
    AddRecord();
    line_.clear();
  } 
  infile_.close();
}

void LibraryManager::ReadLoanedBooks() {
  std::string line, type;
  while (std::getline(infile_, line)) {
    line_.str(line);
    LoanRecord();
    line_.clear();
  } 
  infile_.close();
}

void LibraryManager::ReadReturnedBooks() {
  std::string line, type;
  while (std::getline(infile_, line)) {
    line_.str(line);
    ReturnRecord();
    line_.clear();
  } 
  infile_.close();
}

void LibraryManager::ReadAuthors() {  
  std::string line;
  std::string author_info[4];
  BookPtrIterator it;
  while (std::getline(infile_, line)) {
    std::size_t found = 0;
    for (int i = 0; found != std::string::npos; i++) {
      found = line.find(',');
      author_info[i] = line.substr(0,found); 
      line = line.substr(found+1);
    }
    it = FindBook(author_info[3]);
    (*it)->AddAuthor(author_info[2], author_info[1], author_info[0]);
  }
  line_.clear();
  infile_.close();
}

LibraryManager::BookPtrIterator LibraryManager::FindBook(std::string title) {
  BookPtrIterator it;
  for (it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    if ((*it)->GetTitle() == title) break;
  } 
  if (it != book_shelf_.End()) return it;
  for (it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    if ((*it)->GetTitle() == title) break;
  } 
  return it;
}

void LibraryManager::AddRecord() {
  int pages, edition;
  float length, width, height;
  std::string title, type;
  line_ >> length >> width >> height >> pages >> edition;
  std::getline(line_, title);
  title = title.substr(1);
  Book* book = new Book(pages, length, width, height, title);
  std::unique_ptr<Book> book_ptr(book);
  book_shelf_.PushBack(std::move(book_ptr));
}

void LibraryManager::LoanRecord() {
  int month, day, year;
  std::string title;
  std::string borrower_last_name, borrower_first_name;            
  line_ >> borrower_last_name >> borrower_first_name;
  line_ >> month >> day >> year;
  std::getline(line_, title);
  title = title.substr(1);
  Date date(day, month, year);
  BookPtrIterator it = FindBook(title);
  (*it)->AddBorrower(borrower_first_name, "", borrower_last_name);
  (*it)->SetDate(date);
  (*it)->SetIsLoaned(true);
  loaned_books_.PushBack(std::move(*it));
  book_shelf_.Erase(it);
}

void LibraryManager::ReturnRecord() {
  std::string title;
  std::getline(line_, title);
  title = title.substr(1);
  BookPtrIterator it = FindBook(title);
  (*it)->SetIsLoaned(false);
  book_shelf_.PushBack(std::move(*it));
  loaned_books_.Erase(it);
}

void LibraryManager::Write() {
  int i = 1;
  int month, day, year;
  outfile_.open("book_shelf.txt");
  outfile_ << book_shelf_.Size() << std::endl;

  for (auto it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    outfile_ << i << ". ";
    outfile_ << (*it)->GetTitle() << " by ";
    const Author first_author = (*it)->GetAuthors().front();
    outfile_ << first_author.GetLastName() << " ";
    outfile_ << "(" << (*it)->GetLength() << "x" << (*it)->GetWidth();
    outfile_ << "x" << (*it)->GetHeight() << " in., ";
    outfile_ << (*it)->GetPages() << " pp.)" << std::endl;
    i++;
  }
  outfile_ << std::endl << std::endl;
  outfile_.close();

  i = 1;
  std::string previous_date = "";
  outfile_.open("books_on_loan.txt");
  outfile_ << loaned_books_.Size() << std::endl;
  for (auto it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    month = (*it)->GetDate().GetMonth();
    day = (*it)->GetDate().GetDay();
    year = (*it)->GetDate().GetYear();
    std::cout << "Date: " << (*it)->GetDate().GetDate();
    std::cout << std::endl;
    if (previous_date != (*it)->GetDate().GetDate()) {
      if (day < 10) {
        outfile_ << month << "/" << 0 << day << "/" << year << std::endl;
      } else {
        outfile_ << month << "/" << day << "/" << year << std::endl;
      }
    }
    outfile_ << i << ". ";
    outfile_ << (*it)->GetTitle() << " by ";
    const Author first_author = (*it)->GetAuthors().front();
    outfile_ << first_author.GetLastName() << " ";
    outfile_ << "borrowed by " << (*it)->GetBorrower().GetName();
    outfile_ << " (" << (*it)->GetLength() << "x" << (*it)->GetWidth();
    outfile_ << "x" << (*it)->GetHeight() << " in., ";
    outfile_ << (*it)->GetPages() << " pp.)" << std::endl;
    previous_date = (*it)->GetDate().GetDate();
    i++;
  }
  outfile_.close();
}

bool LibraryManager::BookShelfOrder(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  const Author author1 = book1->GetAuthors()[0];
  const Author author2 = book2->GetAuthors()[0];
  if (author1 <= author2) return true;
  return false;
}

bool LibraryManager::LoanedBookOrder(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_date = book1->GetDate().GetDate();
  std::string book2_date = book1->GetDate().GetDate();
  if (book1_date <= book2_date) {
    return true;
  }
  return false;
}