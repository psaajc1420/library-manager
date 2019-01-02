#include "library-manager/uid.h"

std::size_t UID::next_id_ = 0;

UID::UID() {
   id_ = ++next_id_;
}

UID::UID(const UID& original) {
   id_ = original.id_;
}

const UID& UID::operator=(const UID& original) {
   id_ = original.id_;
   return(*this);
}
    