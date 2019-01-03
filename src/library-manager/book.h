#ifndef LIBRARY_MANAGER_BOOK_H_
#define LIBRARY_MANAGER_BOOK_H_

#include <algorithm>
#include <iostream>
#include <string>

#include "library-manager/author.h"
#include "library-manager/borrower.h"
#include "library-manager/date.h"

class Book {
 public:
  explicit Book(int pages=0, float length=0, float width=0, 
                float height=0, std::string title="", 
                bool is_loaned=false)  
      : pages_(pages), 
        length_(length),
        width_(width),
        height_(height),
        title_(title),
        is_loaned_(is_loaned) {}     
  int GetPages() const;
  void SetPages(int);
  float GetLength() const;
  void SetLength(float);
  float GetWidth() const;
  void SetWidth(float);
  float GetHeight() const;
  void SetHeight(float);
  std::string GetTitle() const;
  void SetTitle(const std::string);
  const std::vector<Author>& GetAuthors() const;
  const Borrower& GetBorrower() const;
  void AddAuthor(const Author&);
  void AddAuthor(const std::vector<Author>&);
  void AddAuthor(std::string, std::string, std::string);
  void AddBorrower(std::string, std::string, std::string);
  void SetDate(const Date&);
  Date GetDate() const;
  bool GetIsLoaned() const;
  void SetIsLoaned(bool);
  float GetArea() const;          // get surface area of the book

  bool operator== (const Book&) const;
  friend std::ostream& operator<< (std::ostream&, const Book&);
  friend std::ostream& operator<< (std::ostream&, const std::unique_ptr<Book>&);
  
 private: 
  int pages_;                    // number of pages in a book
  float length_;                 // length of a book
  float width_;                  // width of a book
  float height_;                 // height of a book
  std::string title_;            // title of a book
  bool is_loaned_;               // true if book is loaned out false otherwise
  Date date_;                    // date object that stores day, month and year
                                 // of return
  std::vector<Author> authors_;  // list of authors
  Borrower borrower_;            // borrower
  UID uid_;
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
inline const std::vector<Author>& Book::GetAuthors() const { return authors_; }
inline const Borrower& Book::GetBorrower() const { return borrower_; }
inline void Book::SetDate(const Date& date) { date_ = date; }
inline Date Book::GetDate() const { return date_; }
inline bool Book::GetIsLoaned() const { return is_loaned_; }
inline void Book::SetIsLoaned(bool is_loaned) { is_loaned_ = is_loaned; }
inline float Book::GetArea() const { return height_*width_; }
#endif // LIBRARY_MANAGER_BOOK_H_
