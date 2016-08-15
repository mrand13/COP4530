/*
    Project 2:  Doubly-Linked List Container
    Date:       10/2/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
#include "List.h"
template <typename T>
List<T>::const_iterator::const_iterator() : current{nullptr}{}
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current{p}{}

template <typename T>
const T & List<T>::const_iterator::operator*() const{
    return retrieve();
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++(){
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    List<T>::const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--(){
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    List<T>::const_iterator old = *this;
    --(*this);
    return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator &rhs) const{
    return (current == rhs.current);
}

template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator &rhs) const{
    return !(*this == rhs);
}

template <typename T>
T & List<T>::const_iterator::retrieve() const{
    return current->data;
}

template <typename T>
List<T>::iterator::iterator(){}

template <typename T>
T & List<T>::iterator::operator*(){
    return List<T>::const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const{
    return List<T>::const_iterator::operator*();
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){
    List<T>::iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    List<T>::iterator old = *this;
    --(*this);
    return old;
}

template <typename T>
List<T>::iterator::iterator(Node *p) : List<T>::const_iterator::const_iterator(p){}

template <typename T>
List<T>::List(){
    init();
}

template <typename T>
List<T>::List(const List<T> &rhs){
    init();
    for (auto & x: rhs)
        push_back(x);
}

template <typename T>
List<T>::List(List<T> && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>
List<T>::List(int num, const T& val){
    init();
    for(int i = 0; i<num; i++)
        push_back(val);
}

template <typename T>
List<T>::List(List<T>::const_iterator start, List<T>::const_iterator end){
    init();
    //Initialize list from range of data
    while(start != end){
        push_back(start.current->data);
        ++start;
    }
}

template <typename T>
List<T>::~List<T>(){
    clear();
    delete head;
    delete tail;
}

template <typename T>
void List<T>::init(){
    //Initialize empty double linked list with 2 nodes H,T
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template <typename T>
const List<T> &List<T>::List::operator=(const List<T> &rhs){
    List<T> copy = rhs;
    std::swap(*this,copy);
    return *this;
}

template <typename T>
List<T> &List<T>::List::operator=(List<T> && rhs){
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
}

template <typename T>
int List<T>::size() const{
    return theSize;
}

template <typename T>
bool List<T>::empty() const{
    return (size()==0);
}

template <typename T>
void List<T>::clear(){
    while(!empty())
        pop_front();
}

template <typename T>
void List<T>::reverse(){
    if(head == NULL)
        return;
    //Swap Head and tail
    Node *temp = head;
    head = tail;
    tail = temp;
    //Reverse nodes
    Node *tHead = head;
    while(tHead != NULL){
        temp = tHead->prev; //Temp Re-use
        tHead->prev = tHead->next;    //Previous = Next
        tHead->next = temp; //Next = Previous
        tHead = tHead->next;  //Shift tHead to next node, not prev cause head/tail has been swapped
    }
}

template <typename T>
T & List<T>::front(){
    return *begin();
}

template <typename T>
const T& List<T>::front() const{
    return *begin();
}

template <typename T>
T & List<T>::back(){
    return *--end();
}

template <typename T>
const T& List<T>::back() const{
    return *--end();
}

template <typename T>
void List<T>::push_front(const T &val){
    insert(begin(), val);
}

template <typename T>
void List<T>::push_front(T && val){
    insert(begin(), std::move(val));
}

template <typename T>
void List<T>::push_back(const T &val){
    insert(end(), val);
}

template <typename T>
void List<T>::push_back(T && val){
    insert(end(), std::move(val));
}

template <typename T>
void List<T>::pop_front(){
    erase(begin());
}

template <typename T>
void List<T>::pop_back(){
    erase(--end());
}

template <typename T>
void List<T>::remove(const T &val){
    for(List<T>::iterator itr = begin(); itr!=end(); ++itr){
        if(itr.current->data == val)
            erase(itr);
    }
}

template <typename T>
void List<T>::print(std::ostream& os, char ofc) const{
    //Prints out the given type data for every element in list
    for(List<T>::const_iterator itr = begin(); itr!= end(); ++itr){
        os << itr.current->data << ofc;
    }
}

template <typename T>
typename List<T>::iterator List<T>::begin(){
    return {head->next};
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return {head->next};
}

template <typename T>
typename List<T>::iterator List<T>::end(){
    return {tail};
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const{
    return {tail};
}

template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T &val){
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{std::move(val),p->prev,p}};
}

template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T && val){
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{std::move(val),p->prev,p}};
}

template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr){
    Node *p = itr.current;
    List<T>::iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end){
    for(List<T>::iterator itr = start; itr != end;)
        itr = erase(itr);
    return end;
}

//Non-Class Global Overloaded Functions
template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs){
    //Compares if two lists are equal
    if(lhs.size() == rhs.size()){
        for(auto & itr: lhs){
            for(auto & itr2: rhs){
                if(itr != itr2) //If invalid equivalent, return false
                    return false;
            }
        }
        return true;    //Return true if both are equal
    }
    else return false;
}

template <typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs){
    return (!(lhs == rhs)); //Return opposite of == operator
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l){
    //Call print function of list
    l.print(os);
    return os;
}
