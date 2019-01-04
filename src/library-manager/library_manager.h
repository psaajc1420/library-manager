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
  // type aliases for Book smart pointers 
  using BookPtr = std::unique_ptr<Book>;
  using BookList = LinkedList<BookPtr>;
  using BookPtrIterator = BookList::iterator;

 public:
  // Opens a file and allows the user to input the files
  void Open();         

  // Opens file by file name                   
  void Open(std::string);

  // reads contents of the file to call the apppropiate methods            
  void Read(int, char**);

  // reads contents of the file to call the apppropiate methods 
  void ReadBooks(std::string);

  // reads contents of the file to call the apppropiate methods 
  void ReadAuthors();

  // add book to the bookshelf
  void AddRecord();     

  // loan book from the bookshelf                
  void LoanRecord(); 

  // return book to the bookshelf                     
  void ReturnRecord();

  // print the books on the bookshelf and loaned out in 
  // two seperate files            
  void Write();                           

   // boolean predicate to order books on the bookshelf                               
  static bool BookShelfOrder(const BookPtr&, const BookPtr&);

  // boolean predicate to order loaned books 
  static bool LoanedBookOrder(const BookPtr&, const BookPtr&);     
 private:
  std::ifstream infile_;                      // file object for reading files
  std::ofstream outfile_;                     // file object for writing files
  std::istringstream line_;                   // string stream object to parse lines
  BookList book_shelf_;                       // list that contains the books on the shelf
  BookList loaned_books_;                     // list that contains the loaned books
  BookPtrIterator FindBook(std::string);  
};
#endif // LIBRARY_MANAGER_LIBRARY_MANAGER_H_