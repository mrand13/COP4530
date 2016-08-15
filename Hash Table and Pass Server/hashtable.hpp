/*
    Project 5:  Hash Tables and Its Applications -- hashtable.hpp
    Date:       11/30/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
#include "hashtable.h"

//Constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size = 101){
    theList.resize(prime_below(size));  //Init to prime based on given size
    currentSize = 0;
}

//Destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable(){
    clear();    //Clear the table
}

//Member contains checks if key is in hashtable
template <typename K, typename V>
bool HashTable<K,V>::contains(const K &k){
    //Get the given chainlinked list at the hashvalue location
    auto & possibleList = theList[myhash(k)];
    //Loop through the chainlinked list to check if value is in the hashtable
    for(auto & thisList : possibleList)
        if(thisList.first == k)
            return true;    //Key is in table
    return false;
}

//Member match checks if key-value pair is in table
template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> &kv) {
    //Get the given chainlinked list at the hashvalue location
    auto & possibleList = theList[myhash(kv.first)];
    //If the list exists, loop through each Keypair to see
    // if both the Key and Value exist
    if(possibleList.size() > 0){
        for(auto & thisList : possibleList){
            if(thisList.first == kv.first)
                if(thisList.second == kv.second)
                    return true;    //Key & Value are both in table
        }
        return false;
    }
    else return false;
}

//Member Insert adds the key value pair into the hash table
template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> &kv){
    //Get the given chainlinked list at the hashvalue location
    auto & possibleList = theList[myhash(kv.first)];
    //Checks to see if KV pair is in table, updates it with proper values
    if(possibleList.size() > 0){
        for(auto & thisList : possibleList){
            if(thisList.first == kv.first)
                if(thisList.second == kv.second)
                    return false;
                else{ thisList.second = kv.second; break;}
            else{ possibleList.push_back(kv);break;}
        }
    }
    else possibleList.push_back(kv);

    //Increment current size and make sure list has not run out of bounds
    currentSize++;
    if(currentSize > theList.size())
        rehash();   //Increase size of hashtable
    return true;
}

//Move version of insert()
template <typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> &&kv){
    //Get the given chainlinked list at the hashvalue location
    auto & possibleList = theList[myhash(kv.first)];
    //Loop through list calling std::swap and std::move where appropriate
    if(possibleList.size() > 0){
        for(auto & thisList : possibleList){
            if(thisList.first == kv.first)
                if(thisList.second == kv.second)
                    return false;
                else{ std::swap(thisList.second,kv.second); break;}
            else{ possibleList.push_back(std::move(kv));break;}
        }
    }
    else possibleList.push_back(std::move(kv));

    //Increment current size and make sure list has not run out of bounds
    currentSize++;
    if(currentSize > theList.size())
        rehash();   //Increase size of hashtable
    return true;
}

//Member remove deltes the key and the corresponding value from the table
template <typename K, typename V>
bool HashTable<K,V>::remove(const K &k){
    //Get the given chainlinked list at the hashvalue location
    auto & possibleList = theList[myhash(k)];
    bool flag = false;
    unsigned int index = 0;
    //Loop through the nested list at hash position
    for(auto & thisList : possibleList){
        if(thisList.first == k){    //if Key is found
            flag = true;
            //Advance ITR to position of index and erase
            auto itr = possibleList.begin();
            std::advance(itr,index);
            possibleList.erase(itr);
            --currentSize;  //decrement cSize
            break;
        }
        index++;
    }
    return flag;
}

//Member clear calls private makeEmtpy()
template <typename K, typename V>
void HashTable<K,V>::clear(){
    makeEmpty();
}

//Member load, loads data from a filename
template <typename K, typename V>
bool HashTable<K,V>::load(const char *filename){
    //Local variables
    std::ifstream infile;
    infile.open(filename);

    //Parse the file
    std::string line;
    while(std::getline(infile,line)){
        std::istringstream iss(line);
        std::string user, pass;
        iss >> user >> pass;    //string stream to deliminator whitespace
        std::pair<std::string, std::string> p = std::make_pair (user,pass);
        insert(p);
    }
    infile.close();
    return true;
}

//Member dump sends the hash table to stdout
template <typename K, typename V>
void HashTable<K,V>::dump(){
    int gIndex = 0;
    //Loop through each chainlinked list
    for(auto & thisList : theList){
        int index = 0;
        std::cout << "v[" << gIndex++ << "]: ";
        for(auto & x : thisList){
            //Checks for semicolon output
            if(++index > 1)
                std::cout << ":";
            std::cout << x.first << " " << x.second;
        }
        std::cout << "\n";
    }
}

//Member write to file outputs the hash table to stdout
template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename){
    //Local variable
    std::ofstream ofile;
    ofile.open(filename);
    //Loop through and output
    for(auto & thisList : theList)
        for(auto & x : thisList)
            ofile << x.first << " " << x.second << "\n";
     ofile.close();
     return true;
}

//Member make empty, clears the hash table
template <typename K, typename V>
void HashTable<K,V>::makeEmpty(){
    for(auto & thisList : theList)
        thisList.clear();
    currentSize = 0;
}

//Member rehash, copies and clears the original list
//  Adds to new size double the old size
template <typename K, typename V>
void HashTable<K,V>::rehash(){
    std::vector<std::list<std::pair<K,V> > > oldTable = theList;
    oldTable.resize(prime_below(2*theList.size()));
    for(auto & thisList : theList)
        thisList.clear();

    //copy table
    currentSize = 0;
    for(auto & thisList : oldTable)
        for(auto & x : thisList)
            insert(std::move(x));

}

//My hash computes a given hash based on the characters * 37
// and returns the computed hash
template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k){
    size_t val = 0;
    for(auto ch : k)
        val = 37 * val + ch;
    return val % theList.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
