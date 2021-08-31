SimCity Project #1 - CSCE 2110
Group #1
Group Members:
Ian Tharp, Michelle Cabrales, Dylan Windebank, Demir Altay

-We did not attempt the bonus for the assignment.

-Instructions on how to compile:
    With all of the files from the zip extracted, to compile the program,
    simply type "g++ *.cpp" (without the quotes) within the same directory
    where the files for the program are located.
    
-Instructions on how to run:
    Ensure that there is a .txt file for the configuration settings in the same
    directory where the files were compiled.
    Inside of the config file, the format of it should contain the following:
    
    Region Layout:
    Time Limit:
    Refresh Rate:
    
    Directly after each of the colons should be their corresponding values, 
    having no space after the colon, for example,

        Region Layout:region1.csv
        Time Limit:20
        Refresh Rate:1
        
    After compiling on the CSE servers, type "./a.out" (without the quotes) to 
    run the program. Once given the prompt to enter the config file, remember 
    to enter the .txt at the end of the file, i.e. config1.txt.