#ifndef LIBRARY_MANAGER_LIBRARY_MANAGER_H_
#define LIBRARY_MANAGER_LIBRARY_MANAGER_H_

#include <fstream>
#include <string>
#include <sstream>

#include "linked-lists/linked_list.h"
#include "library-manager/book.h"
#include "library-manager/date.h"
#include "library-manager/uid.h"

class LibraryManager {
 public: 
  void Open();                            // Open file by user input
  void Open(std::string);                 // Open file by file name
  void Read(int, char**);                 // read contents of the file to call the 
                                          // apppropiate methods  
  void ReadBooks();
  void ReadAuthors();
  void AddRecord();                       // add book to the bookshelf
  void LoanRecord();                      // loan book from the bookshelf
  void ReturnRecord();                    // return book to the bookshelf
  void Write();                           // print the books on the bookshelf and 
                                          // loaned out in two seperate files
  static bool BookOrder(const Book&,      // boolean predicate for the book order
                        const Book&);     // on the bookshelf
 private:
  int records_;                           // number of records given
  std::ifstream infile_;                  // file object for reading files
  std::ofstream outfile_;                 // file object for writing files
  std::istringstream line_;               // string stream object to parse lines
  LinkedList<Book> book_shelf_;           // list that contains the books on the shelf
  LinkedList<Book> loaned_books_;         // list that contains the loaned books

  const Book FindBook(std::string);
};
#endif // LIBRARY_MANAGER_LIBRARY_MANAGER_H_