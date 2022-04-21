#ifndef __SCAN_CRUNCH_H__
#define __SCAN_CRUNCH_H__


#include<iostream>
#include<string>
#include<fstream>

namespace scan {
    class Scanner;
    void crunch(Scanner *scan, std::ostream &out);
    void uncrunch(std::istream &in);
}


#endif
