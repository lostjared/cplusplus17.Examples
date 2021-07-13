// $ cat text_file | ./word_count

#include<iostream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<unordered_map>
#include<vector>
#include<algorithm>

void sort_and_print(std::unordered_map<std::string, unsigned int> &words);

int main(int argc, char **argv) {
    std::string token;
    bool on = true;
    std::unordered_map<std::string, unsigned int> words;
    while(!std::cin.eof()) {
        char c = std::cin.get();
        c = tolower(c);
        if(c >= 'a' && c <= 'z') {
            if(on == true) {
                token += c;
            } else {
                words[token]++;
                token = "";
                token += c;
                on = true;
            }
        } else {
            on = false;
        }
    }
    sort_and_print(words);
    return 0;
}

void sort_and_print(std::unordered_map<std::string, unsigned int> &words) {
    std::vector<std::string> keys;
    for(auto &i : words) {
        keys.push_back(i.first);
    }
    std::sort(keys.begin(), keys.end());
    for(auto &i : keys) {
        std::cout << i << "  " << words[i] << "\n";
    }
}
