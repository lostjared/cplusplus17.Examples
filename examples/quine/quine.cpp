#include<iostream>
int main(int argc, char **argv) 
{
    char quote = 34;
    const char *arr[] = {
        "#include<iostream>",
        "int main(int argc, char **argv)",
        "{",
        "	char quote = 34;",
        "	const char *arr[] = {",
        " 	",
        "	};",
        "	for(int i = 0; i < 5; ++i)",
        "		std::cout << arr[i] << std::endl;",
        "	for(int i = 0; i < 15; ++i)",
        "		std::cout << arr[5] << quote << arr[i] << quote << ',' << std::endl;",
        "	for(int i = 5; i < 15; ++i)",
        "		std::cout << arr[i] << std::endl;",
        "	return 0;",
        "}"};
    for(int i = 0; i < 5; ++i)
        std::cout << arr[i] << std::endl;
    for(int i = 0; i < 15; ++i)
        std::cout << arr[5] << quote << arr[i] << quote << "," << std::endl;
    for(int i = 5; i < 15; ++i)
        std::cout << arr[i] << std::endl;
    return 0;
}
