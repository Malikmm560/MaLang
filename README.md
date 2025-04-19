# MalLang Syntax Guide

Welcome to **MalLang**! This guide covers some of the most important functions and syntax used in **MalLang**. Below you'll find explanations, syntax, and examples for each function.

---

### **`print.now()`**

The `print.now()` function is used to print content immediately to the console. It can handle both **strings** and **variables**.

#### **Syntax:**
```mal
print.now(<content>);
<content>: The content to print. Can be a string (enclosed in quotes) or a variable.

Example:

public class main

public start()
    publicvar greeting = "Hello, MalLang!"
    print.now(greeting)
Output:


Hello, MalLang!
print.prompt()
The print.prompt() function is used to print a message and then wait for the user to provide input. This is useful for creating interactive programs.

Syntax:

print.prompt(<message>);
<message>: The message to show before waiting for user input.

Example:

public class main

public start()
    print.prompt("What is your name?")
Behavior: The program will print the message "What is your name?" and then wait for the user to enter a response.

print.wait(<seconds>)
The print.wait(<seconds>) function prints content after a delay, measured in seconds. This is helpful for creating timed outputs.

Syntax:

print.wait(<seconds>, <content>);
<seconds>: The delay in seconds before printing.

<content>: The content (string or variable) to print after the delay.

Example:

public class main

public start()
    print.wait(2, "This message appears after 2 seconds.")
Output (after 2 seconds):

text

This message appears after 2 seconds.
public function <name>()
The public function declaration is used to define reusable functions in MalLang. These functions can be called to execute certain actions within the program.

Syntax:

public function <function_name>()
    // function body
Example:

public class main

public function test()
    print.now("This is the test function!")

public start()
    test()
Output:

text

This is the test function!
choose()
The choose() function is used for making random selections or decision-making based on conditions. It evaluates a condition and chooses between two options.

Syntax:

choose(<condition>, <option1>, <option2>);
<condition>: A condition to evaluate.

<option1>: The option to choose if the condition is true.

<option2>: The option to choose if the condition is false.

Example:

public class main

public start()
    publicvar isHappy = true
    choose(isHappy, print.now("I'm happy!"), print.now("I'm sad."))
Output:

I'm happy!
Combining Functions in a Program
Here’s an example of how you might combine the functions above in a single MalLang program:


public class main

public function test()
    publicvar message = "This is a test message!"
    print.now(message)
    print.wait(3, "This message will appear after 3 seconds.")
    print.prompt("What is your name?")
    
public start()
    test()
    choose(true, print.now("True branch executed."), print.now("False branch executed."))
Expected Output:


This is a test message!
This message will appear after 3 seconds.
What is your name?
True branch executed.
