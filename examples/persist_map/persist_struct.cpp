#include"permap.hpp"
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>

struct User {
    char first[50];
    char last[50];
    unsigned int id;
};

int main() {
    
    
    persist::PersistMap<User> user_db("users.dat", persist::GenericRead<User>, persist::GenericWrite<User>);
    
    bool active = true;
    
    while(active) {
        std::string item;
        std::cout << "1) Add User 2) Print User 3) Print Users 4) Remove User 5) Clear File 6) Exit\n";
        std::cout << "Enter Choice: ";
        std::getline(std::cin, item);
        switch(atoi(item.c_str())) {
            case 1: {
                User u;
                std::string first,last;
                std::cout << "Enter first name (50 char max): ";
                std::getline(std::cin, first);
                std::cout << "Enter last name (50 char max): ";
                std::getline(std::cin, last);
                if(first.length()>49||last.length()>49) {
                    std::cout << "Error: name to long..\n";
                    continue;
                }
                sprintf(u.first, "%s", first.c_str());
                sprintf(u.last, "%s", last.c_str());
                std::string id;
                std::cout << "Enter user ID: ";
                std::getline(std::cin, id);
                int i = atoi(id.c_str());
                if(i > 0) {
                    user_db[id] = u;
                }
            }
                break;
            case 2: {
                std::cout << "Enter ID: ";
                std::string id;
                std::getline(std::cin, id);
                
                if(user_db.key_exisits(id)) {
                    User &value = user_db[id];
                    std::cout << "-------------------------------\n";
                    std::cout << "User ID: " << id << "\n";
                    std::cout << "Name: " << value.last << ", " << value.first << "\n";
                    std::cout << "-------------------------------\n";
                } else {
                    std::cout << "ID does not exisit.\n";
                }
                
            }
                break;
            case 3: {
                for(auto i = user_db->begin(); i != user_db->end(); ++i) {
                    auto [key,value] = *i;
                    std::cout << "-------------------------------\n";
                    std::cout << "User ID: " << key << "\n";
                    std::cout << "Name: " << value.last << ", " << value.first << "\n";
                    std::cout << "-------------------------------\n";
                }
            }
                break;
            case 4: {
                std::cout << "Enter ID: ";
                std::string id;
                std::getline(std::cin, id);
                auto i = user_db->find(id);
                if(i == user_db->end()) {
                    std::cout << "ID does not exisit.\n";
                    continue;
                }
                user_db->erase(i);
                user_db.WriteMap();
            }
                break;
            case 5:
                user_db.EraseFile();
                std::cout << "Erased..\n";
                break;
            case 6:
                active = false;
                break;
            default:
                std::cout << "Invalid choice..\n";
                break;
        }
    }
    
    
    return 0;
}
