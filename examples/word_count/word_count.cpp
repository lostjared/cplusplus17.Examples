// $ cat text_file | ./word_count

#include<iostream>
#include<string>
#include<cctype>
#include<cstdlib>
#include<unordered_map>
#include<vector>
#include<algorithm>

void extract_and_fill(std::istream &in, std::unordered_map<std::string, unsigned int> &words);
void sort_and_print(std::ostream &out, std::unordered_map<std::string, unsigned int> &words);

int main(int argc, char **argv) {
    std::unordered_map<std::string, unsigned int> words;
    extract_and_fill(std::cin, words);
    sort_and_print(std::cout, words);
    return 0;
}

void extract_and_fill(std::istream &in, std::unordered_map<std::string, unsigned int> &words) {
    std::string token;
    bool on = true;
    while(!in.eof()) {
        char c = tolower(in.get());
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
    if(token != "") {
        words[token]++;
    }
}

void sort_and_print(std::ostream &out, std::unordered_map<std::string, unsigned int> &words) {
    std::vector<std::string> keys;
    for(auto &i : words) {
        keys.push_back(i.first);
    }
    std::sort(keys.begin(), keys.end());
    for(auto &i : keys) {
        out << i << "  " << words[i] << "\n";
    }
}
