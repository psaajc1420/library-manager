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
  if (num_files > 0) {
    FindAvailableTypes(num_files);
    for (int i = 1; i <= read_types_.size(); i++) {
      Open(files[i]);
      ParseFile();
      AddBookInfo(read_types_[i-1]);
      file_info_.clear();
    }
    book_shelf_.Sort(BookShelfOrder);
    loaned_books_.Sort(LoanedBookOrder);
  } else if (num_files == 0) {
    Open();
  } else {
    std::cerr << "Shouldn't be more than 2 files given as command line arguments";
    std::cout << std::endl;
  }
}

void LibraryManager::FindAvailableTypes(int num_files) {
  if (num_files >= 1) {
    read_types_.push_back(ReadType::kAddBook);
  }
  if (num_files >= 2) {
    read_types_.push_back(ReadType::kAddAuthor);
  }
  if (num_files >= 3) {
    read_types_.push_back(ReadType::kLoanBook);
  }
  if (num_files >= 4) {
    read_types_.push_back(ReadType::kReturnBook);
  }
}

void LibraryManager::ParseFile() {
  std::string line;
  int key = 0;
  while (std::getline(infile_, line)) {
    line_.str(line);
    std::size_t found = 0;
    for (int i = 0; found != std::string::npos; i++) {
      found = line.find(',');
      file_info_[key].push_back(line.substr(0,found));
      line = line.substr(found+1);
    }
    key++;
    line_.clear();
  } 
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

void LibraryManager::AddBookInfo(ReadType type) {
  if (type == ReadType::kAddBook) {
    AddRecords();
  } else if (type == ReadType::kLoanBook) { 
    LoanRecords();
  } else if (type == ReadType::kReturnBook) {
    ReturnRecords();
  } else if (type == ReadType::kAddAuthor) {
    AddAuthor();
  } else {
    std::cout << "Something is wrong" << std::endl;
  }
}

void LibraryManager::AddAuthor() {
  for (auto& it_file: file_info_) {
    std::string last_name = it_file.second[0]; 
    std::string middle_name = it_file.second[1]; 
    std::string first_name = it_file.second[2];
    std::string title = it_file.second[3];
    BookPtrIterator it = FindBook(title);
    (*it)->AddAuthor(first_name, middle_name, last_name);
  }
}

void LibraryManager::AddRecords() {
  for (auto& it_file: file_info_) {
    float length = std::stof(it_file.second[0]);
    float width = std::stof(it_file.second[1]);
    float height = std::stof(it_file.second[2]);
    int pages = std::stoi(it_file.second[3]);
    int edition = std::stoi(it_file.second[4]);
    std::string title = it_file.second[5];
    Book* book = new Book(pages, length, width, height, title);
    std::unique_ptr<Book> book_ptr(book);
    book_shelf_.PushBack(std::move(book_ptr));
  }
}

void LibraryManager::LoanRecords() {
  for (auto& it_file: file_info_) {
    std::string last_name = it_file.second[0]; 
    std::string middle_name = it_file.second[1]; 
    std::string first_name = it_file.second[2];
    int month = std::stoi(it_file.second[3]);
    int day = std::stoi(it_file.second[4]);
    int year = std::stoi(it_file.second[5]);
    std::string title = it_file.second[6];
    Date date(day, month, year);
    BookPtrIterator it = FindBook(title);
    (*it)->AddBorrower(first_name, "", last_name);
    (*it)->SetDate(date);
    (*it)->SetIsLoaned(true);
    loaned_books_.PushBack(std::move(*it));
    book_shelf_.Erase(it);
  }
}

void LibraryManager::ReturnRecords() {
  for (auto& it_file: file_info_) {
    std::string title = it_file.second[0];
    BookPtrIterator it = FindBook(title);
    (*it)->SetIsLoaned(false);
    book_shelf_.PushBack(std::move(*it));
    loaned_books_.Erase(it);
  }
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
  std::string book2_date = book2->GetDate().GetDate();
  if (book1_date <= book2_date) return true;
  return false;
}