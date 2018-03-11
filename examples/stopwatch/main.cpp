#include<iostream>
#include"stopwatch.hpp"


void testFunc() {
    StopWatch<HighResolutionClock> start("testFunc");
    char a[2];
    for(unsigned int i = 0; i < 100000; ++i)
        a[0] = a[1] = 0;
}

int main(int argc, char **argv) {
    for(unsigned int i = 0; i < 100; ++i)
        testFunc();
    
    return 0;
}
