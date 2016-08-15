#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <vector>

namespace cop4530 {

	template <typename T>
		class Stack {
			public:
				// constructor, desctructor, copy constructor
				Stack(); // default zero parameter constructor
				~Stack(); // destructor
				Stack(const Stack &rhs); // copy constructor
				Stack(Stack && rhs); // move constructor

				const Stack& operator=(const Stack &rhs); //copy assignment
				Stack & operator=(Stack && rhs);    //move assignment

				// member functions
				int size() const; // number of elements
                bool empty() const; // check if list is empty
				void clear(); // delete all elements

				T &top(); // reference to the first element
				const T& top() const;

				void push(const T & x); //copy version
				void push(T && x); // move version
				void pop(); // delete first element

				// print out all elements. ofc is deliminitor
				void print(std::ostream& os, char ofc = ' ') const;
			private:
				void init(); // initialization
				int topOfStack;
                std::vector<T> theArray;
		};

	// overloading comparison operators
	template <typename T>
		bool operator==(const Stack<T> & lhs, const Stack<T> &rhs);

	template <typename T>
		bool operator!=(const Stack<T> & lhs, const Stack<T> &rhs);

	// overloading output operator
	template <typename T>
		std::ostream & operator<<(std::ostream &os, const Stack<T> &a);

    // overloading less than operators
    template <typename T>
        bool operator<(const Stack<T>& a, const Stack<T>& b);

	// include the implementation file here
#include "stack.hpp"

} // end of namespace 4530

#endif
