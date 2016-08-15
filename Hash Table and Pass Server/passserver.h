/*
    Project 5:  Hash Tables and Its Applications -- passserver.h
    Date:       11/30/2015
    Name:       Michael Rand
    Class:      COP 4530
*/
#ifndef PASSSERVER_H
#define PASSSERVER_H
#include "hashtable.h"

namespace cop4530{
    //Adapter class PassServer inherits HashTable implementation via std::string
    class PassServer : public HashTable <std::string, std::string> {
    public:
        PassServer(size_t size);  //constructor
        ~PassServer();  //destructor

        bool load(const char *filename);    //load pass file into table
        bool addUser(std::pair<std::string, std::string> &kv);    //add a new user/pass, encrypt
        bool addUser(std::pair<std::string, std::string> &&kv);   //move version of addUser
        bool removeUser(const std::string &k);   //delete existing user with name K
        bool changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword); //change pass
        bool find(const std::string &user);  //check if a user exists in table
        void dump();    //show the structore and contetns of table
        bool write_to_file(const char *filename);   //save user/pass to file
        size_t size();  //return size of HashTable
    private:
        std::string encrypt(const std::string & str); //encrypt the str using crypt()
    };
}
#endif
