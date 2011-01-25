
// Here is the definition for the Stack class.  The functions are
// implemented in the file stack.cc.
//
// A stack requires one parameter in its constructor: the number of elements
// it can hold.  The element type is integer.

class Stack {
  public:
    Stack(int sz);    // Constructor:  initialize variables, allocate space.
    ~Stack();         // Destructor:   deallocate space allocated above.
    
    void Push(int i); // Push an integer, checking for overflow.
    int Pop();        // Pop an integer, checking for underflow.
    
    int Full();       // Returns non-0 if the stack is full, 0 otherwise.
    int Empty();      // Returns non-0 if the stack is empty, 0 otherwise.

    // You may need the following methods 
    //    if you store the local variables in the stack
    int Get_top();    // return the value of the private member: top
    int Get_element(int disp); // get the value of the stack element 
    void Set_element(int disp, int value); // directly set the value of the stack
    
  private:
    int size;         // The maximum capacity of the stack.
    int top;          // Index of the lowest unused position.
    int* stack;       // A pointer to an array that holds the contents.
};
