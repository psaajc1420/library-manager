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
  book_shelf_.Sort(BookOrder);
  loaned_books_.Sort();
}

void LibraryManager::ReadBooks() {
  std::string line, type;
  std::string records;
  std::getline(infile_, records);
  records_ = stoi(records);
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
  // Clear global string stream object for reuse
  line_.clear();
  infile_.close();
}

LibraryManager::BookPtrIterator LibraryManager::FindBook(std::string title) {
  BookPtrIterator it;
  for (it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
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
  Book* book= new Book(pages, length, width, height, title);
  std::unique_ptr<Book> book_ptr(book);
  book_shelf_.PushBack(std::move(book_ptr));
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
  BookPtrIterator it = FindBook(title);
  (*it)->SetBorrowerName(borrower_name);
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
  std::string previous_date;
  BookPtr book_ptr;

  outfile_.open("book_shelf.txt");
  outfile_ << book_shelf_.Size() << std::endl;

  for (auto it = book_shelf_.Begin(); it != book_shelf_.End(); ++it) {
    book_ptr = std::move(*it);
    outfile_ << i << ". ";
    outfile_ << book_ptr->GetTitle() << " by ";
    const Author first_author = book_ptr->GetAuthors().front();
    outfile_ << first_author;
    outfile_ << "(" << book_ptr->GetLength() << "x" << book_ptr->GetWidth();
    outfile_ << "x" << book_ptr->GetHeight() << " in., ";
    outfile_ << book_ptr->GetPages() << " pp.)" << std::endl;
    i++;
  }
  outfile_ << std::endl << std::endl;
  outfile_.close();

  i = 1;
  outfile_.open("books_on_loan.txt");
  outfile_ << loaned_books_.Size() << std::endl;
  for (auto it = loaned_books_.Begin(); it != loaned_books_.End(); ++it) {
    book_ptr = std::move(*it);
    month = book_ptr->GetDate().GetMonth();
    day = book_ptr->GetDate().GetDay();
    year = book_ptr->GetDate().GetYear();
    if (previous_date != book_ptr->GetDate().GetDate()) {
      if (day < 10) {
        outfile_ << month << "/" << 0 << day << "/" << year << std::endl;
      } else {
        outfile_ << month << "/" << day << "/" << year << std::endl;
      }
    }
    outfile_ << i << ". ";
    outfile_ << book_ptr->GetTitle() << " by " << book_ptr->GetAuthorName();
    outfile_ << "(" << book_ptr->GetLength() << "x" << book_ptr->GetWidth();
    outfile_ << "x" << book_ptr->GetHeight() << " in., ";
    outfile_ << book_ptr->GetPages() << " pp.)" << std::endl;
    previous_date = book_ptr->GetDate().GetDate();
    i++;
  }
  outfile_.close();
}

bool LibraryManager::BookOrder(const LibraryManager::BookPtr& book1,
                               const LibraryManager::BookPtr& book2) {
  const Author author1 = book1->GetAuthors()[0];
  const Author author2 = book2->GetAuthors()[0];
  if (author1 <= author2) return true;
  return false;
}