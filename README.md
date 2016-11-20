# Stacy-s-matriarch
Repository for final year project
In this project, we present Stacy - a tool that statically detects potential security vulnerabilities present in input source code. Static program analysis is the examination of source code prior to its execution. Our tool attempts to predict the behavior of a program before it is deployed. Stacy uses novel techniques to detect the primary sources of vulnerability in the source code of a program and informs the developer. 
A good static analysis tool is one that would reduce the burden of trivial debugging, that the compiler does not include, off the shoulders of the developer. As the developer writes code, it is being evaluated, giving information that would help the developer.
The scope includes finding the occurence of memory leaks, buffer overflows and uninitialized variables, among others.

This project utilizes the following files:
1. Lexical analyzer - Converts input source code, written in C, into a sequence of tokens.
2. YACC - Accepts tokens from Lex and matches constructs formed in the Abstract Syntax Tree (AST). 
3. AST_Traversals.c - Traverses the AST formed by YACC and performs the core static analysis functions of Stacy.
4. Header_file.h - Header file used by the above files. 

