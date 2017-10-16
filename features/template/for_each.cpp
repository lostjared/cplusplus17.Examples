#include<iostream>
#include<vector>


template<typename Iter, typename Func>
void foreach(Iter start, Iter stop, Func f) {
    while(start != stop) {
        f(*start);
        start++;
    }
}

int main(int argc, char **argv) {
    std::vector<int> v {1,2,8,49,5920,881,2,4,1};
    foreach(v.begin(), v.end(), [](int x) { std::cout << "val: " << x << "\n"; });
    return 0;
}
