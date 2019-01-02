#ifndef LIBRARY_MANAGER_UID_H_
#define LIBRARY_MANAGER_UID_H_

#include <cstdlib>

class UID {
 public:
  std::size_t id_;
  UID();
  UID(const UID&);
  const UID& operator=(const UID&);  
 protected:
  static std::size_t next_id_;
};
#endif