Wrote this to help out with conversions of multiple files to make it easier on me

Output file list with

$ ls | grep file_type > list.txt

or

$ ls | grep png > list.txt

then use program to batch convert and resize

$ img_convert --input=list.txt --output=jpg --res=1280x720

will stretch the resolution so be aware of that

or don't change the res

$ img_convert --input=list.txt --output=png 

or output to certain path

$ img_convert --input=list.txt --output=jpg --path=/Users/jared

