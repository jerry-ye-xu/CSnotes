#include <stdio.h>

// [3] Effectively a global variable.
static int incrementer = 0;

// [4] Visible to all program files.
//     The variable CANNOT be initialised.
extern void global_function();
/*
    Extern is used to declare a global var/func
    in another file.

    Most commonly used when 2 or more files share the
    same thing.
*/

int main(int argc, char** argv) {
    // [1] "int" defaults to "auto int"
    int bob;
    auto int bobg;

    // [2] register
    register int gg_bob_g;
    /*
        Define variables to store in register.

        You cannot find its location in memory with "&" because
        it's not there.

        The variable must have limted size.

        This is merely a suggestion. Just because you ask C to do it
        doesn't mean it will.
    */

   // [3] static
   static int counter = 0;
   /*
        Allows compiler to keep var even after it goes out of scope.

        This means you can create a static var in a function and it will
        stay alive. The alternative is, of course, allocating memory on
        a heap.
   */


    return 0;
}
