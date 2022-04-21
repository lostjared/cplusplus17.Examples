#ifndef _SCAN_EX_H_
#define _SCAN_EX_H_

#include<iostream>

namespace scan {
    class ScanException {
    public:
        ScanException(const std::string &txt);
        std::string error();
    protected:
        std::string text;
    };
}


#endif