#ifndef LIBRARY_MANAGER_LIBRARY_MANAGER_H_
#define LIBRARY_MANAGER_LIBRARY_MANAGER_H_

#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "linked-lists/linked_list.h"
#include "library-manager/book.h"
#include "library-manager/date.h"
#include "library-manager/uid.h"

class LibraryManager {
  using BookPtr = std::unique_ptr<Book>;
  using BookList = LinkedList<BookPtr>;
  using BookPtrIterator = BookList::iterator;
  using BookInfoMap = std::unordered_map<int, std::vector<std::string>>;

  // These enums values are used in FindAvailableTypes() to 
  // determine the purpose of the input files given via 
  // command line args. 
  enum class ReadType {
    kAddBook, kAddAuthor, kLoanBook, kReturnBook
  };
 public:
  // Opens a file and allows the user to input the files
  void Open();

  // Opens file by file name
  void Open(std::string);

  // Reads all files given via the command line. If no arguments
  // are given force the client to give the files to read.
  void Read(int, char**);

  // Parses a files that is comma seperated and stores the
  // information into a map of vectors. See below to understand
  // the hash map.
  void ParseFile();

  // Add books to the book shelf
  void AddRecords();

  // Adds authors to the corresponding book title
  void AddAuthor();

  // Loans book from the book shelf
  void LoanRecords();

  // Returns book to the book shelf
  void ReturnRecords();

  // Delegates the type of information given to
  // books depending on the enum passed in.
  void AddBookInfo(ReadType);

  // Populates the member vector read_types_, which stores
  // enums that represent the types of file given. The int
  // given represents the number of files received via command
  // line args allowing the client freedom to pass any number
  // of args. See the the enum class for more details on the
  // values in read_types.
  // 
  // The order of command line args does matter. The preferred
  // order is as follows
  // 
  // ./{}.out book_list.txt author_list.txt loaned_list.txt return_list.txt
  void FindAvailableTypes(int);

  // Prints the books on the bookshelf and loaned out in
  // two seperate files
  void Write();

  static bool CompareByAuthor(const BookPtr&, const BookPtr&);
  static bool CompareByTitle(const BookPtr&, const BookPtr&);
  static bool CompareBySubject(const BookPtr&, const BookPtr&);
  static bool CompareByFiction(const BookPtr&, const BookPtr&);
  static bool CompareByDate(const BookPtr&, const BookPtr&);
  static bool CompareBySubjectAndTitle(const BookPtr&, const BookPtr&);
  static bool CompareBySubjectAndAuthor(const BookPtr&, const BookPtr&);
  static bool CompareByFictionAndTitle(const BookPtr&, const BookPtr&);
 private:
  // File object for reading files
  std::ifstream infile_;

  // File object for writing files
  std::ofstream outfile_;

   // String stream object to parse lines
  std::istringstream line_;

  // Map whose key value pair represents the line read
  // in and a vector of all the information in that
  // line respectively.
  BookInfoMap file_info_;

  // Vector of reading options provided by the client
  std::vector<ReadType> read_types_;

  // List that contains the books on the shelf
  BookList book_shelf_;  

  // List that contains the loaned books                     
  BookList loaned_books_;       

  // Returns an iterator that contains the book smart pointer
  // matching the title passed in. Searches through both the
  // the book_shelf_ and loaned_books_ lists and returns 
  // the end of loaned_books_ if nothing was found.
  BookPtrIterator FindBook(std::string);  
};
#endif // LIBRARY_MANAGER_LIBRARY_MANAGER_H_