#include "library-manager/uid.h"

std::size_t UID::next_id_ = 0;
 
const UID& UID::operator=(const UID& original) {
  id_ = original.id_;
  return *this;
}

bool UID::operator== (const UID& id) const {
  if (this->id_ == id.id_) return true;
  return false;
}