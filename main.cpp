#include <iostream>
#include <pvm3.h>

using namespace std;

int main(int argc, char** argv) {
    char* groupName = "all";
    int myId = pvm_mytid();
    int myParent = pvm_parent();
    bool isParent = (myParent == PvmNoParent) || (myParent == PvmParentNotSet);
    pvm_exit();
    return 0;
}