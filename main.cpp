#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    ABS<std::string> abs;
    abs.push("hello");
    abs.push("mythical");
    abs.push("rocket");
    abs.PrintForward();

    ABQ<double> abq;
    abq.enqueue(5.55);
    abq.enqueue(6.66);
    abq.enqueue(7.27);
    abq.PrintForward();

    
    LLS<char> lls;
    lls.push('A');
    lls.push('B');
    lls.push('C');
    lls.PrintForward();
    
    LLQ<float> llq;
    llq.enqueue(1.1f);
    llq.enqueue(2.2f);
    llq.enqueue(3.3f);
    llq.PrintForward();
    
    LLDQ<std::string> lldq;
    lldq.pushFront("a");
    lldq.pushBack("b");
    lldq.pushFront("c");
    lldq.PrintForward();
    
    ABDQ<int> abdq;
    abdq.pushBack(20);
    abdq.pushFront(10);
    abdq.pushBack(20);
    abdq.pushFront(5);
    abdq.pushBack(30);
    abdq.PrintForward();
    return 0;
}


#endif