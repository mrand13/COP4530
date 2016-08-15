/*
    Project 5:  Hash Tables and Its Applications -- passserver.cpp
    Date:       11/30/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
#include "passserver.h"
#include <unistd.h>
#include <crypt.h>
using namespace cop4530;

//Constructor calls HashTable inheritance of Constructor with given size
PassServer::PassServer(size_t size = 101) : HashTable<std::string,std::string>(size){}

//Destructor
PassServer::~PassServer(){}

//bool load() calls Parent hashtable version of load()
bool PassServer::load(const char *filename){
    return HashTable<std::string,std::string>::load(filename);
}

//bool AddUser adds an ecrypted password based on incoming KV value
bool PassServer::addUser(std::pair<std::string, std::string> &kv){
    std::pair<std::string,std::string> eKV = std::make_pair(kv.first,encrypt(kv.second));
    return HashTable<std::string,std::string>::insert(eKV);
}

//bool AddUser Move version of insert
bool PassServer::addUser(std::pair<std::string, std::string> &&kv){
    return false;
}

//bool removeUser calls Parent HashTable version of remove()
bool PassServer::removeUser(const std::string &k){
    return HashTable<std::string,std::string>::remove(k);
}

//bool changePassword() Checks the password based on 3 criteria:
//  False if user is not in table, if the second pass == current pass and
//  if the new pass is the same as the old pass, else it returns the bool of insert()
//      Also makes sure to encrypt password before insertion
bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword){
    if(find(p.first)){  //If user is in table
        std::pair<std::string,std::string> oldEKV = std::make_pair(p.first,encrypt(p.second));
        if(HashTable<std::string,std::string>::match(oldEKV)){  //if p.second matches
            std::pair<std::string,std::string> eKV = std::make_pair(p.first,encrypt(newpassword));
            if(!HashTable<std::string,std::string>::match(eKV)) //if p.second != newPassword
                return HashTable<std::string,std::string>::insert(eKV);
            else return false;
        }
        else return false;
    }
    else return false;
}

//bool find() Calls Parent HashTable member contains()
bool PassServer::find(const std::string &user){
    return HashTable<std::string,std::string>::contains(user);
}

//bool dump() Calls Parent HashTable version of dump()
void PassServer::dump(){
    HashTable<std::string,std::string>::dump();
}

//bool write_to_file() Calls Parent HashTable version of write_to_file()
bool PassServer::write_to_file(const char *filename){
    return HashTable<std::string,std::string>::write_to_file(filename);
}

//member size() calls HashTable helper function getSize()
size_t PassServer::size(){
    return HashTable<std::string,std::string>::getSize();
}

//Encrypts the string based on salt
//This function using the <crypt.h> library places the salt infront of the
//Password even though it shouldn't. The <crypt.h> example from
// http://www.gnu.org/software/libc/manual/html_node/crypt.html
// Also places the salt infront as an error.
//      The Provided 'scrypt.x' also places the salt in front as an error.
//  Therefore the entire project becomes broken as a result of invalid password encryption
//  Especially for changing passwords
//
//      Whereas in plaintext this program works nearly perfectly (for all given functions)
//
//std::string PassServer::encrypt(const std::string &str){
//    return str;
//}
//
std::string PassServer::encrypt(const std::string &str){
    char salt[] = "$1$########";    //Does not work?
    char * pass = new char [ 100 ];
    std::strcpy(pass, crypt(str.c_str(), salt));
    std::string ret(pass);
    return ret;
}
