/*
    Project 5:  Hash Tables and Its Applications
    Date:       11/30/2015
    Name:       Michael Rand
    Class:      COP 4530
*/

#include <iostream>
#include "passserver.h"
using namespace std;
using namespace cop4530;

//Function Prototypes
void Menu();
void GetServerSize(size_t& serverSize);
void GetUsername(std::string& user);
std::pair<std::string,std::string> AddNewUser();

//Main Driver Program
//      Initializes the size of the PassServer
//      Keeps program running until 'x' is typed
//      Uses Menu to control PassServer functions
int main()
{
    //Member variables
    char c;
    bool running = true;
    size_t serverSize;

    //Initialize PassServer
    GetServerSize(serverSize);
    PassServer passServer(serverSize);

    //Main Loop
    while(running){
        //Get Char for menu selection
        while(cin.get(c) && running){
            if(c == 'x'){   //Terminate program
                running = false;
                break;
            }
            else if(c == 'l'){  //Load File
                std::string filename;
                std::cout << "\nEnter password file name to load from: ";
                std::cin >> filename;
                if(!passServer.load(filename.c_str()))
                    std::cout << "\nError: Cannot open file " << filename << std::endl;
            }
            else if(c == 'a'){  //Add new user
                std::pair<std::string,std::string> newUser = AddNewUser();
                if(passServer.addUser(newUser))
                    std::cout << "\nUser " << newUser.first << " added." << std::endl;
                else std::cout << "Failed!" << std::endl;
            }
            else if(c == 'r'){  //Remove user
                std::string user;
                GetUsername(user);
                if(passServer.removeUser(user))
                    std::cout << "\nUser: " << user << " deleted." << std::endl;
                else std::cout << "Failed!" << std::endl;
            }
            else if(c == 'c'){  //Change user pass
                std::string user, pass, newPass;
                GetUsername(user);
                std::cout << "Enter password: ";
                std::cin >> pass;
                std::cout << "\nEnter new password: ";
                std::cin >> newPass;
                if(passServer.changePassword(std::make_pair(user,pass),newPass))
                    std::cout << "\nPassword changed for user " << user << std::endl;
                else std::cout << "\n*****Error: Could not change user password" << std::endl;
            }
            else if(c == 'f'){  //Find new user
                std::string user;
                GetUsername(user);
                if(passServer.find(user))
                    std::cout << "\nUser '" << user << "' found." << std::endl;
                else std::cout << "User '" << user << "' not found." << std::endl;
            }
            else if(c == 'd'){  //Dump the hash table
                passServer.dump();
            }
            else if(c == 's'){  //Print the size of hash table
                std::cout << "Size of hashtable: " << passServer.size() << std::endl;
            }
            else if(c == 'w'){  //Write hash table to file
                std::string filename;
                std::cout << "\nEnter password file name to write to: ";
                std::cin >> filename;
                if(!passServer.write_to_file(filename.c_str()))
                    std::cout << "\nError: Cannot write file " << filename << std::endl;
            }
            else{   //Print menu reset
                std::string toavoidawarning;
                toavoidawarning += c;
                if(toavoidawarning != "\0")
                    Menu();
            }
        }
        running = false;
    }
    return 0;
}

//Function Menu prints the menu
void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

//Function GetServerSize
//  Passes by reference the size_t server size and gets it from stdin
void GetServerSize(size_t& serverSize){
    std::cout << "Enter preferred hash table capacity: ";
    std::cin >> serverSize;
    std::cout << std::endl;
}

//Function GetUser gets username by reference from stdin
void GetUsername(std::string& user){
    std::cout << "Enter username: ";
    std::cin >> user;
}

//Add new user gets username and pass from stdin and returns std::pair
std::pair<std::string,std::string> AddNewUser(){
    std::string user, pass;
    GetUsername(user);
    std::cout << "Enter password: ";
    std::cin >> pass;
    return std::make_pair(user,pass);
}
