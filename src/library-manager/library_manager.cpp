#include "library-manager/library_manager.h"

LibraryManager::LibraryManager(int num_files, char** files) {
  Read(num_files, files);
}

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
    throw std::runtime_error("Error: file can't be opened as it was not found.");
  } 
}

void LibraryManager::Read() {
  int num_files;
  std::cout << "How many files do you want to read? ";
  std::cin >> num_files;
  FindAvailableTypes(num_files);
  for (int i = 0; i < num_files; i++) {
    Open();
    ParseFile();
    AddBookInfo(read_types_[i-1]);
    file_info_.clear();
  }
  book_shelf_.Sort(CompareByFictionAndTitle);
  loaned_books_.Sort(CompareByDate);
}

void LibraryManager::Read(int num_files, char** files) {
  if (num_files > 0) {
    FindAvailableTypes(num_files);
    for (int i = 1; i <= read_types_.size(); i++) {
      try {
        Open(files[i]);
      } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
      }     
      ParseFile();
      AddBookInfo(read_types_[i-1]);
      file_info_.clear();
    }
    book_shelf_.Sort(CompareByFictionAndTitle);
    loaned_books_.Sort(CompareByDate);
  } else {
    throw std::runtime_error(
      "Error: the number files given can't be negative or zero");
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
  for (auto& it_file : file_info_) {
    std::string last_name = it_file.second[0]; 
    std::string middle_name = it_file.second[1]; 
    std::string first_name = it_file.second[2];
    std::string title = it_file.second[3];
    BookPtrIterator it = FindBook(title);
    (*it)->AddAuthor(first_name, middle_name, last_name);
  }
}

void LibraryManager::AddRecords() {
  for (auto& it_file : file_info_) {
    float length = std::stof(it_file.second[0]);
    float width = std::stof(it_file.second[1]);
    float height = std::stof(it_file.second[2]);
    int pages = std::stoi(it_file.second[3]);
    int edition = std::stoi(it_file.second[4]);
    std::string subject = it_file.second[5];
    std::string fiction_str = it_file.second[6];
    bool fiction = false;
    if (fiction_str == "fiction") fiction = true;
    std::string title = it_file.second[7];
    Book* book = new Book(pages, edition, length, width, height, 
                          title, subject, fiction);
    std::unique_ptr<Book> book_ptr(book);
    book_shelf_.PushBack(std::move(book_ptr));
  }
}

void LibraryManager::LoanRecords() {
  for (auto& it_file : file_info_) {
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
  for (auto& it_file : file_info_) {
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

bool LibraryManager::CompareByAuthor(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  const Author author1 = book1->GetAuthors()[0];
  const Author author2 = book2->GetAuthors()[0];
  if (author1 <= author2) return true;
  return false;
}

bool LibraryManager::CompareByDate(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_date = book1->GetDate().GetDate();
  std::string book2_date = book2->GetDate().GetDate();
  if (book1_date <= book2_date) return true;
  return false;
}

bool LibraryManager::CompareByTitle(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_title = book1->GetTitle(); 
  std::string book2_title = book2->GetTitle(); 
  if (book1_title <= book2_title) return true;
  return false;
}

bool LibraryManager::CompareBySubject(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_subject = book1->GetSubject();
  std::string book2_subject = book2->GetSubject();
  if (book1_subject <= book2_subject) return true;
  return false;   
}

bool LibraryManager::CompareBySubjectAndTitle(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_subject = book1->GetSubject();
  std::string book2_subject = book2->GetSubject();
  std::string book1_title = book1->GetTitle(); 
  std::string book2_title = book2->GetTitle(); 
  if (book1_subject == book2_subject) {
    if (book1_title <= book2_title) {
      return true;
    }
  } else if (book1_subject < book2_subject) {
    return true;
  }
  return false;
}

bool LibraryManager::CompareBySubjectAndAuthor(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  std::string book1_subject = book1->GetSubject();
  std::string book2_subject = book2->GetSubject();
  const Author author1 = book1->GetAuthors()[0];
  const Author author2 = book2->GetAuthors()[0];
  if (book1_subject == book2_subject) {
    if (author1 <= author2) {
      return true;
    }
  } else if (book1_subject < book2_subject) {
    return true;
  }
  return false;
}

bool LibraryManager::CompareByFictionAndTitle(
    const LibraryManager::BookPtr& book1,
    const LibraryManager::BookPtr& book2) {
  bool book1_is_fiction = book1->GetIsFiction();
  bool book2_is_fiction = book2->GetIsFiction();
  std::string book1_title = book1->GetTitle(); 
  std::string book2_title = book2->GetTitle(); 
  if ((book1_is_fiction && book2_is_fiction) ||
      (!book1_is_fiction && !book2_is_fiction)) {
    if (book1_title <= book2_title) {
      return true;
    }
  } else if (book1_is_fiction && !book2_is_fiction) {
    return true;
  }
  return false;
}