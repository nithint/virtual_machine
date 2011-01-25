/*
 * jc.h
 *
 *  Created on: Jan 23, 2011
 */
class jc
{
public:
	jc(int sz);
	jc();
	virtual ~jc();

	//INSTR:p:Just print the tos without popping
	void printTOS();
	// div: pop two from stack and do integer division
	void jc_div();
	// mul: pop two from stack and multiply
	void jc_mul();
	// sub: pop two from stack and subtract
	void jc_sub();
	//INSTR:add:pop tos twice and adds the elements and push result onto tos
	void jc_add();
	//INSTR: load n:Load the local variable n onto the stack
	void jc_load(int n);
	//INSTR:store n:pop tos and store the value into local map at n
	void jc_store(int n);
	//INSTR :pop :Pop the element at tos and return
	int jc_pop();
	//INSTR: const x: push the const integer onto the stack ( bounds check performed by Stack's member fns)
	void jc_push(int x);
	// main function: reads instructions from commandline one by one and executes them
	static int main(int argc, char *argv[]);

private:
	Stack * stackPtr = null; //The Stack class provided
	//Local variable mapping container
	std::map<unsigned int, int> localVars;
	/**
	 * Lookup table of supported opcodes
	 */
	String validOpcodes[] =
	{ "const", "pop", "store", "load", "add", "sub", "mul", "div", "p" };
	/**
	 * array to store instructions
	 */
	vector<String> instructions;
};
