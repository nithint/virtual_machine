
// See the comments in test.cc.

extern "C" {
#include <stdio.h>
extern void exit(int st);
}

#include "stack.h"

// The constructor for the Stack class.  Note that it doesn't have a
// return type.

Stack::Stack(int sz)
{
    if (sz < 1) {
	fprintf(stderr, "Error: Stack: size %d too small\n", sz);
	exit(1);
    }

    // Initialize the data members of the stack object.
    size = sz;
    top = 0;
    stack = new int[size];   // Let's get an array of integers.
}

// The destructor for the Stack class.  Just get rid of the array we
// allocated in the constructor.

Stack::~Stack()
{
    // Some compilers and books tell you to write this as:
    //     delete [size] stack;
    // but apparently G++ doesn't like that.

    delete stack;
}

// The rest of these member functions should be straightforward enough.

void
Stack::Push(int i)
{
    if (Full()) {
	fprintf(stderr, "Error: Stack overflow\n");
	exit(1);
    }
    
    stack[top++] = i;
}

int
Stack::Pop()
{
    if (Empty()) {
	fprintf(stderr, "Error: Stack underflow\n");
	exit(1);
    }
    
    return (stack[--top]);
}

int
Stack::Full()
{
    return (top == size);
}

int
Stack::Empty()
{
    return (top == 0);
}

// You may need the following methods 
//    if you store the local variables in the stack
int
Stack::Get_top()
{
    return top ;
}

int
Stack::Get_element(int disp)
{
  return stack[disp];
}

void
Stack::Set_element(int disp, int value)
{
  stack[disp]=value;
}







