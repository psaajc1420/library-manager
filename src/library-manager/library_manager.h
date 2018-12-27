#ifndef LIBRARY_MANAGER_LIBRARY_MANAGER_H_
#define LIBRARY_MANAGER_LIBRARY_MANAGER_H_

#include <fstream>
#include <string>
#include <sstream>

#include "linked-lists/linked_list.h"
#include "library-manager/book.h"
#include "library-manager/date.h"

class LibraryManager {
 public:
  LibraryManager();                       
  explicit LibraryManager(std::string);    
  void ReadFile();                        // read contents of the file to call the 
                                          // apppropiate methods
  void AddRecord(Book&);                  // add book to the bookshelf
  void LoanRecord(std::string,
                  std::string,
                  Date&);                 // loan book from the bookshelf
  void ReturnRecord(std::string);         // return book to the bookshelf
  void WriteFile();                       // print the books on the bookshelf and 
                                          // loaned out in two seperate files
  static bool BookOrder(const Book&,      // boolean predicate for the book order
                        const Book&);     // on the bookshelf
 private:
  int records_;                           // number of records given
  std::ifstream infile_;                  // file object for reading files
  std::ofstream outfile_;                 // file object for writing files
  LinkedList<Book> book_shelf_;           // list that contains the books on the shelf
  LinkedList<Book> loaned_books_;         // list that contains the loaned books
};
#endif // LIBRARY_MANAGER_LIBRARY_MANAGER_H_