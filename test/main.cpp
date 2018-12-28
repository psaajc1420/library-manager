#include "library-manager/library_manager.h"

int main(int argc, char** argv) {

    LibraryManager* manager;

    // Check for command line argument. If
    // there are more than one call overloaded
    // LibraryManager constructor otherwise
    // call the default constructor
    if(argc > 1) {
      std::string file_name = argv[1];
      manager = new LibraryManager(file_name);
    } else {
      manager = new LibraryManager();
    }

    manager->ReadFile();
    manager->WriteFile();

    delete manager;

    return 0;
}