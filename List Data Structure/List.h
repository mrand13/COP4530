#ifndef DL_LIST_H
#define DL_LIST_H
#include <iostream>

namespace cop4530 {

	template <typename T>
		class List {
			private:
				// nested Node class
				struct Node {
					T data;
					Node *prev;
					Node *next;

					Node(const T & d = T{}, Node *p = nullptr, Node *n = nullptr) 
						: data{d}, prev{p}, next{n} {}
					Node(T && d, Node *p = nullptr, Node *n = nullptr)
						: data{std::move(d)}, prev{p}, next{n} {}
				};

			public:
				//nested const_iterator class
				class const_iterator {
					public:
						const_iterator(); // default zero parameter constructor
						const T & operator*() const; // operator*() to return element

						// increment/decrement operators
						const_iterator & operator++();
						const_iterator operator++(int);
						const_iterator & operator--();
						const_iterator operator--(int);

						// comparison operators
						bool operator==(const const_iterator &rhs) const;
						bool operator!=(const const_iterator &rhs) const;

					protected:
						Node *current; // pointer to node in List
						T & retrieve() const; // retrieve the element refers to
						const_iterator(Node *p); // protected constructor

						friend class List<T>;
				};

				// nested iterator class
				class iterator : public const_iterator {
					public:
						iterator();
						T & operator*();
						const T & operator*() const;

						// increment/decrement operators
						iterator & operator++();
						iterator operator++(int);
						iterator & operator--();
						iterator operator--(int);

					protected:
						iterator(Node *p);
						friend class List<T>;
				};

			public:
				// constructor, desctructor, copy constructor
				List(); // default zero parameter constructor
				List(const List &rhs); // copy constructor
				List(List && rhs); // move constructor
				// num elements with value of val
				explicit List(int num, const T& val = T{}); 
				// constructs with elements [start, end)
				List(const_iterator start, const_iterator end); 

				~List(); // destructor

				// copy assignment operator
				const List& operator=(const List &rhs);
				// move assignment operator
				List & operator=(List && rhs);

				// member functions
				int size() const; // number of elements
				bool empty() const; // check if list is empty
				void clear(); // delete all elements
				void reverse(); // reverse the order of the elements

				T &front(); // reference to the first element
				const T& front() const;
				T &back(); // reference to the last element
				const T & back() const; 

				void push_front(const T & val); // insert to the beginning
				void push_front(T && val); // move version of insert
				void push_back(const T & val); // insert to the end
				void push_back(T && val); // move version of insert
				void pop_front(); // delete first element
				void pop_back(); // delete last element

				void remove(const T &val); // remove all elements with value = val

				// print out all elements. ofc is deliminitor
				void print(std::ostream& os, char ofc = ' ') const; 

				iterator begin(); // iterator to first element
				const_iterator begin() const;
				iterator end(); // end marker iterator
				const_iterator end() const; 
				iterator insert(iterator itr, const T& val); // insert val ahead of itr
				iterator insert(iterator itr, T && val); // move version of insert
				iterator erase(iterator itr); // erase one element
				iterator erase(iterator start, iterator end); // erase [start, end)


			private:
				int theSize; // number of elements
				Node *head; // head node
				Node *tail; // tail node

				void init(); // initialization
		};

	// overloading comparison operators
	template <typename T>
		bool operator==(const List<T> & lhs, const List<T> &rhs);

	template <typename T>
		bool operator!=(const List<T> & lhs, const List<T> &rhs);

	// overloading output operator
	template <typename T>
		std::ostream & operator<<(std::ostream &os, const List<T> &l);

	// include the implementation file here
#include "List.hpp"

} // end of namespace 4530

#endif
