#include<iostream>
#include"stopwatch.hpp"


void testFunc() {
    char a[2];
    for(unsigned int i = 0; i < 1920*1080; ++i)
        a[0] = a[1] = rand()%255;
}

void averageTest() {
    std::cout << "Testing: ";
    long counter = 0;
    for(int index = 0; index < 100; ++index) {
        SystemClock clock;
    	clock.start();
    	testFunc();
    	clock.stop();
        counter += clock.timePassed();
        std::cout << ".";
        fflush(stdout);
    }
    std::cout << "\n";
    counter /= 100;
    std::cout << "Average time for testFunc: " << counter << " milliseconds\n";
}

void testFunc2() {
    StopWatch<HighResolutionClock> counter("testFunc");
    testFunc();
}

int main(int argc, char **argv) {
    averageTest();
    testFunc2();
    return 0;
}
