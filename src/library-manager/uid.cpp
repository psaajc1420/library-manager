#include "library-manager/uid.h"

std::size_t UID::next_id_ = 0;
 
const UID& UID::operator=(const UID& original) {
   id_ = original.id_;
   return *this;
}
    