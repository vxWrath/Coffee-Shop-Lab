# Lab 8 Functions

Refactoring is an important part of writing code.  When you refactor code, you are changing the code in some way to make it better.

Now that you know about functions, the goal of this lab is to take Lab Seven, and abstract away different parts of it into functions.

For example, take the code associated with taking an order, and abstract it into a function.  Example: double takeOrder(string menu, string \&order);  
string calculateReceipt(double subTotal, double tip, string name, string order);  
void printToFile(string fileName, string text);

Some of these functions can be divided into smaller functions:  
char getSize();  
char getChoice(string menu);  
void displayMenu(string menu);  
void collectMenuItem(string itemName, double small, double med, double large);

Suggested Steps:

1) Go through the code you have and look for parts that can be split off into a function–look especially carefully at anything that gets repeated.  
2) Define the function headers for those functions.  First put them all in comments, and then work on them one at a time.  
3) Put a comment above the function explaining the purpose of that function, including explaining the parameters and the return.  
4) Implement the functions.

For some of these, you will need to somehow get information out of the function beyond the return type.  There are three ways (at the moment) you can get data outside the function when you are IN the function:

1) Global variables.  Global variables should be avoided, but they can have scope within any functions they are defined above.  If they are not constants, you can change their values.  Again, you CAN do this, but it is bad practice.  
2) Passing variables by reference.  If you pass a variable by reference, you include a & in front of the variable name, for example, string \&order when it is declared in the parameter list.  This means that instead of creating a brand new variable inside the function, the variable created will be an alias of the variable passed in–it will have the same memory location.  If the value stored at that memory location is changed in the function, it will also be changed outside the function.  
3) The return value of the function.  The function can send ONE piece of data back to the part of the program that called it.

Once you have refactored your program–that is, split it into smaller functions, commented the functions, and tested it to make sure it works, you can submit the .cpp and menu.txt files to Peerceptiv.

The criteria will be:  
Functional Decomposition:  Was the main program broken up effectively into smaller functions:  
4: The decomposition was complete and thorough.  
3: The program was broken up into functions, but they remained very large.  
2: The program had some parts broken up, but not all of them.  It felt like there were some tasks that really should have been broken further.  
1: The program was not broken down into functions.

Variable Naming: Are the names of variables and functions clear and easy to understand?  
4:  Names are great, very clear.  
3:  Names are okay.  They are mostly clear, but a little confusing or vague at times.  
2:  Some names are clear, others are not.  
1:  Names are confusing.

Comments:  
4:  Comments are clear inside and above functions.  They are not too wordy or distracting, but are complete enough to make the code easy to follow.  
3:  Comments are clear above functions, but there are no comments anywhere else in the program.  OR There are some comments that are unnecessary and confusing.  
2:  The program is confusing in some places and needs comments to clarify.  Or there are pieces of code that are commented out without any explanation.  
1:  Comments are missing.

Functionality  
2: Code Works   
1: Code doesn't work.