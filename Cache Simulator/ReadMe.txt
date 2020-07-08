In order to compile the program, use the command "g++ *.cpp" before running it with “./a.out <input.txt>” or 
“./a.exe <input.txt>” depending on whether it is linux or windows. Upon running, the program will check whether 
or not an input.txt file is in the directory. If it is not, then the program will end. Once the program successfully 
locates <input.txt>, the program will ask for the cache configurations, and the rest follows the document. In 
order to account for RAM test cases, if the RAM does not fully utilize the 8 bit address width(ie. 256 indexes), 
it will turn all remaining slots into 0x0. Don’t put spaces in the addresses and data, as it will not be read in properly.
