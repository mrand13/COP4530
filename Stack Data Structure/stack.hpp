/*
    Project 3:  Stack Container
    Date:       10/16/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
#include "stack.h"
//Constructor
template <typename T>
Stack<T>::Stack(){
    init();
}
//Copy Constructor
template <typename T>
Stack<T>::Stack(const Stack<T> &rhs){
    init();
    for(auto itr = rhs.theArray.begin(); itr != rhs.theArray.end(); ++itr)
        push(*itr);
}
//Move Constructor
template <typename T>
Stack<T>::Stack(Stack<T> && rhs) : topOfStack{rhs.topOfStack}, theArray{rhs.theArray}{
    rhs.topOfStack = -1;
    rhs.theArray = std::vector<T>();
}
//Destructor
template <typename T>
Stack<T>::~Stack<T>(){
    clear();
}
//Member Function Init
template <typename T>
void Stack<T>::init(){
    //Initialize empty double linked list with 2 nodes H,T
    topOfStack = -1;
}
//Copy Assignment Operator
template <typename T>
const Stack<T> &Stack<T>::Stack::operator=(const Stack<T> &rhs){
    Stack<T> copy = rhs;
    std::swap(*this,copy);
    return *this;
}
//Move Assignment Operator
template <typename T>
Stack<T> &Stack<T>::Stack::operator=(Stack<T> && rhs){
    std::swap(topOfStack, rhs.topOfStack);
    std::swap(theArray, rhs.theArray);
}
//Member Size
template <typename T>
int Stack<T>::size() const{
    return (theArray.size());
}
//Member Empty
template <typename T>
bool Stack<T>::empty() const{
    return (size()<=0);
}
//Function Clear
template <typename T>
void Stack<T>::clear(){
    while(!empty())
        pop();
}
//Top of Stack
template <typename T>
T & Stack<T>::top(){
    return theArray[topOfStack];
}
//Top of Stack Const
template <typename T>
const T& Stack<T>::top() const{
    return theArray[topOfStack];
}
//Copy version of push to stack
template <typename T>
void Stack<T>::push(const T &x){
    topOfStack++;
    theArray.push_back(x);
    //std::cout << "\nCopy Push: " << x << " | " << topOfStack << std::endl;
}
//Move version of push to stack
template <typename T>
void Stack<T>::push(T && val){
    topOfStack++;
    theArray.push_back(std::move(val));
    //std::cout << "\nVal push" << val << " | " << topOfStack << " || " << theArray[topOfStack] << std::endl;
}
//Pop last element
template <typename T>
void Stack<T>::pop(){
    theArray.pop_back();
    topOfStack--;
}
//Print out elements in opposite order of Stack, oldest first
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const{
    //Prints out the given type data for every element in list
    for(auto itr = theArray.begin(); itr!= theArray.end(); ++itr){
        os << *itr << ofc;
    }
}

//Non-Class Global Overloaded Functions
template <typename T>
bool operator==(const Stack<T> &lhs, const Stack<T> &rhs){
    //Compares if two lists are equal
    if(lhs.size() == rhs.size()){
        Stack<T> lTemp = lhs, rTemp = rhs;
        while(!lTemp.empty() && !rTemp.empty()){
            if(lTemp.top() != rTemp.top())
                return false;
            lTemp.pop();
            rTemp.pop();
        }
        return true;
    }
    else return false;
}

template <typename T>
bool operator!=(const Stack<T> &lhs, const Stack<T> &rhs){
    return (!(lhs == rhs)); //Return opposite of == operator
}

template <typename T>
bool operator<=(const Stack<T>& a, const Stack<T> & b){
    if(a==b)
        return true;
    Stack<T> lTemp = a, rTemp = b;
    while(!lTemp.empty()){
        if(rTemp.empty())
            return true;
        if(lTemp.top() > rTemp.top())
            return false;
        lTemp.pop();
        rTemp.pop();
    }
    return true;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const Stack<T> &a){
    //Call print function of Stack
    a.print(os);
    return os;
}
