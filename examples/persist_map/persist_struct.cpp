#include"permap.hpp"
#include<iostream>
#include<algorithm>
#include<cstdlib>
#include<cstring>
#include<vector>


struct User {
    char first[50];
    char last[50];
    char id[50];
};

void printSorted(persist::PersistMap<User> &u);
std::ostream &operator<<(std::ostream &out, const User &u);

int main() {
    
    
    persist::PersistMap<User> user_db("users.dat", persist::GenericRead<User>, persist::GenericWrite<User>);
    
    bool active = true;
    
    while(active) {
        std::string item;
        std::cout << "1) Add User 2) Print User 3) Print Users Sorted 4) Remove User 5) Clear File 6) Exit\n";
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
                snprintf(u.first, 50, "%s", first.c_str());
                snprintf(u.last, 50, "%s", last.c_str());
                std::string id;
                std::cout << "Enter user ID: ";
                std::getline(std::cin, id);
                snprintf(u.id, 50, "%s", id.c_str());
                user_db[id] = u;
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
                printSorted(user_db);
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

void printSorted(persist::PersistMap<User> &u) {
    std::vector<std::string> keys;
    u.GetSortedKeys(keys);
    for(unsigned int q = 0; q < keys.size(); ++q) {
        std::cout << u[keys[q]] << "\n";
    }
}

std::ostream &operator<<(std::ostream &out, const User &value) {
    out << "-------------------------------\n";
    out << "User ID: " << value.id << "\n";
    out << "Name: " << value.last << ", " << value.first << "\n";
    out << "-------------------------------\n";
    return out;
}
