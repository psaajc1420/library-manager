#ifndef LIBRARY_MANAGER_BOOK_H_
#define LIBRARY_MANAGER_BOOK_H_

#include <iostream>
#include <string>

#include "library-manager/author.h"
#include "library-manager/date.h"

class Book {
 public:
  explicit Book(int pages=0, float length=0, float width=0, 
                float height=0, std::string title="", 
                std::string author_name="", std::string borrower_name="", 
                bool is_loaned=false);
                
  int GetPages() const ;
  void SetPages(int);
  float GetLength() const;
  void SetLength(float);
  float GetWidth() const;
  void SetWidth(float);
  float GetHeight() const;
  void SetHeight(float);
  std::string GetTitle() const;
  void SetTitle(const std::string);
  std::string GetAuthorName() const;
  void SetAuthorName(const std::string);
  std::string GetBorrowerName() const;
  void SetBorrowerName(const std::string);
  void SetDate(const Date&);
  Date GetDate() const;
  bool GetIsLoaned() const;
  void SetIsLoaned(bool);

  int GetArea() const;  // get surface area of the book
  void Print();         // print out a book

  bool operator<= (const Book&) const;
  bool operator== (const Book&) const;
  friend std::ostream& operator<< (std::ostream&, const Book&);

 private:
  int pages_;                    // number of pages in a book
  float height_;                 // height of a book
  float length_;                 // length of a book
  float width_;                  // width of a book
  Date date_;                    // date object that stores day, month and year
                                 // of return
  std::vector<Author> authors_;  // list of authors
  std::string title_;            // title of a book
  std::string author_name_;      // name of the books author
  std::string borrower_name_;    // name of the borrower 
  bool is_loaned_;               // true if book is loaned out false otherwise
};

// Standard getters and setters
inline int Book::GetPages() const { return pages_; }
inline void Book::SetPages(int pages) { pages_ = pages; } 
inline float Book::GetLength() const { return length_; }
inline void Book::SetLength(float length) { length_ = length; }
inline float Book::GetWidth() const { return width_; }
inline void Book::SetWidth(float width) { width_ = width; }
inline float Book::GetHeight() const { return height_; }
inline void Book::SetHeight(float height) { height_ = height; }
inline std::string Book::GetTitle() const { return title_; }
inline void Book::SetTitle(std::string title) { title_ = title; }
inline std::string Book::GetAuthorName() const { return author_name_; }
inline void Book::SetAuthorName(std::string author_name) { 
  author_name_ = author_name; 
}
inline std::string Book::GetBorrowerName() const { return borrower_name_; }
inline void Book::SetBorrowerName(std::string borrower_name) { 
  borrower_name_ = borrower_name; 
}
inline void Book::SetDate(const Date& date) { date_ = date; }
inline Date Book::GetDate() const { return date_; }
inline bool Book::GetIsLoaned() const { return is_loaned_; }
inline void Book::SetIsLoaned(bool is_loaned) { is_loaned_ = is_loaned; }
inline int Book::GetArea() const { return height_*width_; }

#endif // LIBRARY_MANAGER_BOOK_H_
