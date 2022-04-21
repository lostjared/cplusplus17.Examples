#include "scan_exception.hpp"

namespace scan {
    ScanException::ScanException(const std::string &txt) : text {txt} {}
    std::string ScanException::error() { return text; }
}