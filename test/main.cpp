#include "library-manager/library_manager.h"

int main(int argc, char** argv) {

    LibraryManager* manager;

    manager = new LibraryManager();
    manager->Read(argc, argv);
    manager->Write();

    delete manager;

    return 0;
}