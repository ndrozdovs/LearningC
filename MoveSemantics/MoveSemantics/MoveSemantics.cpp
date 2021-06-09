/*
* C++ rvalue references and move semantics
* rvalues: The core idea is that in C++ you will find such temporary, short-lived values that you cannot alter in any way
* Modern C++ has introduced rvalue references: a new type that can bind to temporary objects, giving you the ability to modify them
* C++0x has introduced a new type called rvalue reference, denoted by placing a double ampersand && after some type. 
* Such rvalue reference lets you modify the value of a temporary object: it's like removing the const attribute
* rvalue references pave the way for the implementation of move semantics, a technique which can significantly increase the performance of your applications
* Move semantics is a new way of moving resources around in an optimal way by avoiding unnecessary copies of temporary objects, based on rvalue references
*/

#include <iostream>
#include "Header.h"

Holder createHolder(int size)
{
    return Holder(size);
}

int main()
{
    // The traditional C++ rules say that you are allowed to take the address of an rvalue only if you store it in a const (immutable) variable.
    // More technically, you are allowed to bind a const lvalue to an rvalue. Consider the following example:
    // int& x = 666; // Error
    const int& x = 666; // OK

    // rvalue reference:
    // Now aref is a reference to a temporary object, or an rvalue reference
    // To better distinguish it, we refer to traditional C++ references(the single - ampersand one) as lvalue references
    int&& aref = 10;
    std::cout << ++aref;

    
    
    // OLD DESIGN

    // Implementing the copy constructor (in Header.h):
    Holder h1(10000); // regular constructor
    Holder h2 = h1;   // copy constructor
    Holder h3(h1);    // copy constructor (alternate syntax)

    // Implementing the assignment operator:
    // It's now time for the assignment operator, used to replace an existing object with another existing object. For example:
    Holder h4(10000);  // regular constructor
    Holder h5(60000);  // regular constructor
    h4 = h5;           // assignment operator
    // The key point of the copy constructor and the assignment operator is that they both receive a const reference to an object in input and 
    // make a copy out of it for the class they belong to. The object in input, being a constant reference, is of course left untouched

    // The limitations of our current class design
    // Consider createHolder,It returns a Holder object by value. We know that when a function returns an object by value, the compiler has to create a temporary — yet fully-fledged — object (rvalue)
    // Now, our Holder is a heavy-weight object due to its internal memory allocation, which is a very expensive task: returning such things by value with our current class design would trigger 
    // multiple expensive memory allocations, which is rarely a great idea

    // Consider this:
    Holder h = createHolder(1000);
    // A temporary object coming out from createHolder() is passed to the copy constructor. According to our current design, the copy constructor allocates its own m_data pointer 
    // by copying the data from the temporary object. Two expensive memory allocations: a) during the creation of the temporary, b) during the actual object copy-construct operation.
    // The same copy procedure occurs within the assignment operator

    
    
    // MOVE SEMANTICS

    // In a nutshell, we will steal existing data from temporary objects instead of making useless clones. Don't copy, just move, because moving is always cheaper
    // The idea is to add new versions of the copy constructor and assignment operator so that they can take a temporary object in input to steal data from. 
    // To steal data means to modify the object the data belongs to, by using rvalue reference
    // Any class for which move semantics are desirable, has to declare two additional member functions: move constructor and move assignment operator 

    // Move Constructor: to construct new objects by stealing data from temporaries
    // Takes in input an rvalue reference to another Holder object. This is the key part: being an rvalue reference, we can modify it
    // See Header.h

    // Move Assignment Operator: to replace existing objects by stealing data from temporaries.
    // We steal data from the other object coming in as an rvalue reference, after a cleanup of the existing resources

    // Now that we have our new methods in place, the compiler is smart enough to detect whether you are creating an object with a temporary value (rvalue) 
    // or a regular one (lvalue) and trigger the proper constructor/operator accordingly. For example:
    Holder h6(1000);                // regular constructor
    Holder h7(h6);                  // copy constructor (lvalue in input)
    Holder h8 = std::move(createHolder(2000)); // move constructor (rvalue in input) (1) 

    h7 = h8;                        // assignment operator (lvalue in input)
    h7 = createHolder(500);         // move assignment operator (rvalue in input)

    // Move lvalues:
    // With the utility function std::move from the Standard Library
    Holder a1(1000);     // a1 is an lvalue
    Holder a2(a1);       // copy-constructor invoked (because of lvalue in input)
    Holder a3(1000);           // a1 is an lvalue
    Holder a4(std::move(a3));  // move-constructor invoked (because of rvalue in input)
    // Here std::move has converted the lvalue h1 into an rvalue: the compiler sees such rvalue in input and then triggers the move constructor on h2. 
    // The object h2 will steal data from h1 during its construction stage

    return 0;
}


