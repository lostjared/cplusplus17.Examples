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
        "	for(int i = 0; i < 6; ++i)",
        "		std::cout << arr[i] << quote << std::endl;",
        "	for(int i = 0; argv[i] != 0; ++i)",
        "		std::cout << arr[6] << quote << arr[i] << quote << \",\";",
        "	for(int i = 7; arr[i] != 0; ++i)",
        "		std::cout << arr[i] << std::endl;",
        "	return 0;",
        "}", 0};
    for(int i = 0; i < 5; ++i)
        std::cout << arr[i] << std::endl;
    for(int i = 0; arr[i] != 0; ++i)
        std::cout << arr[5] << quote << arr[i] << quote << "," << std::endl;
    for(int i = 6; arr[i] != 0; ++i)
        std::cout << arr[i] << std::endl;
    return 0;
}
