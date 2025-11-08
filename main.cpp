#ifdef MAIN

#include "ABDQ.cpp"
#include "ABQ.cpp"
#include "ABS.cpp"
#include "Interfaces.hpp"
#include "LinkedList.cpp"
#include "LLDQ.cpp"
#include "LLQ.cpp"
#include "LLS.cpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABDQ<int> myNewList(1);

    myNewList.pushFront(1);
    myNewList.pushFront(3);
    myNewList.pushBack(5);
    std::cout << myNewList.popFront() << std::endl;
    std::cout << myNewList.popBack() << std::endl;
    std::cout << myNewList.popFront() << std::endl;

    return 0;
}


#endif