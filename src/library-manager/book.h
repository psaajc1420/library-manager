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
                std::string subject="", bool is_fiction=false,
                bool is_loaned=false)
      : pages_(pages),
        length_(length),
        width_(width),
        height_(height),
        title_(title),
        subject_(subject),
        is_loaned_(is_loaned),
        is_fiction_(is_fiction) {}
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
  std::string GetSubject() const;
  void SetSubject(const std::string);
  bool GetIsLoaned() const;
  void SetIsLoaned(bool);
  bool GetIsFiction() const;
  void SetIsFiction(bool);
  const std::vector<Author>& GetAuthors() const;
  const Borrower& GetBorrower() const;
  void SetDate(const Date&);
  Date GetDate() const;

  // Creates an author passing a first, middle, and last name
  void AddAuthor(std::string, std::string, std::string);

  // Creates an borrower passing a first, middle, and last name
  void AddBorrower(std::string, std::string, std::string);

  // Calculates the area of a book by multiplying
  // the length and width.
  float GetArea() const;          

  // Shows equivalence of two books by comparing book titles
  bool operator== (const Book&) const;
  
  // Overload stream extraction operators to display 
  // book content
  friend std::ostream& operator<< (std::ostream&, const Book&);
  friend std::ostream& operator<< (std::ostream&, const std::unique_ptr<Book>&);  
 private: 
  int pages_;
  float length_;
  float width_;
  float height_;
  std::string title_;
  std::string subject_;
  bool is_loaned_;
  bool is_fiction_;
  Date date_;
  std::vector<Author> authors_;
  Borrower borrower_;
  UID uid_;
};
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
inline std::string Book::GetSubject() const { return subject_; }
inline void Book::SetSubject(std::string subject) { subject_ = subject; }
inline bool Book::GetIsLoaned() const { return is_loaned_; }
inline void Book::SetIsLoaned(bool is_loaned) { is_loaned_ = is_loaned; }
inline bool Book::GetIsFiction() const { return is_fiction_; }
inline void Book::SetIsFiction(bool is_fiction) { is_fiction_ = is_fiction; }
inline float Book::GetArea() const { return height_*width_; }
inline const std::vector<Author>& Book::GetAuthors() const { return authors_; }
inline const Borrower& Book::GetBorrower() const { return borrower_; }
inline void Book::SetDate(const Date& date) { date_ = date; }
inline Date Book::GetDate() const { return date_; }
#endif // LIBRARY_MANAGER_BOOK_H_
