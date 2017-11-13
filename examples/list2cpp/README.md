Simple program that outputs header files using C++17's
inline variables to use:


to use const char *:

list2cpp inputfile outputfile variable_name c

to use std::string:

list2cpp inputfile outputfile variable_name s

or

cat sourcefile  | list2cpp variable_name s

or

cat sourcefile  | list2cpp variable_name c


