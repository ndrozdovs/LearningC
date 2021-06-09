/*
* Notes
* lvalue is something that points to a specific memory location, rvalue is something that doesn't point anywhere.
* rvalues are temporary and short lived, while lvalues live a longer life since they exist as variables
* It's also fun to think of lvalues as containers and rvalues as things contained in the containers. Without a container, they would expire.
*/


#include <iostream>

int global = 100;

int& setGlobal()
{
    return global;
}

void fnc(const int& x)
{
}

int main()
{
    // Here 666 is an rvalue; a number (technically a literal constant) has no specific memory address, 
    // except for some temporary register while the program is running. That number is assigned to x, which is a variable. 
    // A variable has a specific memory location, so its an lvalue. C++ states that an assignment requires an lvalue as its left operand
    int a = 666; // ok

    // Here I'm grabbing the the memory address of a and putting it into b, through the address-of operator &. It takes an lvalue argument and produces an rvalue. 
    // This is another perfectly legal operation: on the left side of the assignment we have an lvalue (a variable), on the right side an rvalue produced by the address-of operator.
    int* b = &a;   // ok

    // Functions returning lvalues and rvalues:
    // It works because here setGlobal returns a reference, unlike setValue() above. 
    // A reference is something that points to an existing memory location (the global variable) thus is an lvalue, so it can be assigned to. 
    // Watch out for & here: it's not the address-of operator, it defines the type of what's returned (a reference)
    setGlobal() = 400; // OK
    std::cout << global; // prints 400

    // Lvalue to rvalue conversion:
    // An lvalue may get converted to an rvalue: that's something perfectly legit and it happens quite often. 
    // Let's think of the addition + operator for example. According to the C++ specifications, it takes two rvalues as arguments and returns an rvalue
    // x and y have undergone an implicit lvalue-to-rvalue conversion
    int x = 1;
    int y = 3;
    int z = x + y; // OK

    // Lvalue references:
    // What about the opposite? Can an rvalue be converted to lvalue? Nope. It's not a technical limitation, though: it's the programming language that has been designed that way.
    // you are declarying cref as of type int&: a reference to c. It's called an lvalue reference. Now you can happily change the value of c through its reference cref.
    int c = 10;
    int& cref = c;
    cref++; // c is now 11

    // Now, what if I shortcut the whole thing and try to assign 10 directly to my reference, without the object that holds it?
    // int& yref = 10;  // This won't work
    // On the right side we have a temporary thing, an rvalue that needs to be stored somewhere in an lvalue
    // On the left side we have the reference (an lvalue) that should point to an existing object. But being 10 a numeric constant, i.e. without a specific memory address, i.e. an rvalue, 
    // the expression clashes with the very spirit of the reference.

    // Const lvalue reference to the rescue
    // According to the language specifications, you are allowed to bind a const lvalue to an rvalue. So the following snippet works like a charm:
    const int& ref = 10;  // OK!
    fnc(10);  // OK!
    // The idea behind is quite straightforward. The literal constant 10 is volatile and would expire in no time, so a reference to it is just meaningless. 
    // Let's make the reference itself a constant instead, so that the value it points to can't be modified. Now the problem of modifying an rvalue is solved for good
    // This makes possible the very common C++ idiom of accepting values by constant references into functions, 
    // as I did in the previous snipped above, which avoids unnecessary copying and construction of temporary objects
    // Under the hood the compiler creates an hidden variable for you (i.e. an lvalue) where to store the original literal constant, and then bounds that hidden variable to your reference. 
    // That's basically the same thing I did manually in a couple of snippets above. For example:
    // the following...
    const int& ref = 10;

    // ... would translate to:
    int __internal_unique_name = 10;
    const int& ref = __internal_unique_name;

    // Now your reference points to something that exists for real (until it goes out of scope) and you can use it as usual, except for modifying the value it points to:
    const int& moreRef = 10;
    std::cout << moreRef << "\n";   // OK!
    // std::cout << ++moreRef << "\n"; // error: increment of read-only reference ‘ref’
}
