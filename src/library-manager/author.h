#ifndef LIBRARY_MANAGER_AUTHOR_H
#define LIBRARY_MANAGER_AUTHOR_H

#include <string>
#include <vector>

#include "library-manager/person.h"
#include "library-manager/uid.h"

class Author: public Person {
  private:
    UID book_id_;
};
#endif // LIBRARY_MANAGER_AUTHOR_H