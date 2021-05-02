 for Practice
 Use
 
 ./shell-cmd path "command %f" regex_search_pattern
 ex:
 ./shell-cmd . "cat %f" .txt
 
 actual example extract all archives:
 
 $ shell-cmd . "7z e %f" .7z
 
 to execute command for each file type within directory/subdirectory
 just written to practice
