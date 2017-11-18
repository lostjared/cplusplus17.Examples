Simple program that outputs header files using C++17's
inline variables to use:


to use const char *:

list2cpp inputfile outputfile variable_name c

to use std::string:

list2cpp inputfile outputfile variable_name s

to use a character array char arr[]

list2cpp inputfile outputfile variable_name b

or

cat sourcefile  | list2cpp variable_name s

or

cat sourcefile  | list2cpp variable_name c

or

cat sourcefile | list2cpp variable_name b


optional sorting use g for greater than, l for less than like this

for greater than sorting use

list2cpp inputfile outputfile variable_name sg

or less than sorting use

list2cpp inputfile outputfile variablename sl

also works with pipes

cat sourcefile | list2cpp variable_name cl


