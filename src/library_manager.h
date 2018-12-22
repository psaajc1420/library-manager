#ifndef _LIBRARY_MANAGER__
#define _LIBRARY_MANAGER__

#include <fstream>
#include <string>
#include <sstream>

#include "linked-lists/linked_list.h"
#include "book.h"
#include "date.h"

class LibraryManager {
          
 public:
  LibraryManager();   
  LibraryManager(std::string);    
  void ReadFile();                // read contents of the file to call the 
                                  // apppropiate methods
  void AddRecord(Book&);          // add book to the bookshelf
  void LoanRecord(std::string,
                  std::string,
                  Date&);         // loan book from the bookshelf
  void ReturnRecord(std::string); // return book to the bookshelf
  void WriteFile();               // print the books on the bookshelf and 
                                  // loaned out in two seperate files
 private:
  int records_;                    // number of records given
  std::ifstream infile_;           // file object for reading files
  std::ofstream outfile_;          // file object for writing files
  LinkedList<Book> book_shelf_;     // list that contains the books on the shelf
  LinkedList<Book> loaned_books_;   // list that contains the loaned books
};
#endif