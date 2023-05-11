
# Translation Methods

- # Lab 1 - Done
```
Translated programming language:    Java
Instrumental programming language:  C++
```
#
- # Lab 2 - Lexical Analyser

```
The main task purpose is to create a program using C++ 
to translate Java program (input.java) to stream of lexeme (tokens).
Finally we get a lexical analyser, that group program code and separate it to following groups:
- Key words
- Operators
- Variables (names)
- Variables types
- Constants

If program has an undefined 'token', it will be added to errors table.

Current stage: Done.
```
#
- # Lab 3 - Syntax Analyser

```
Here we will create an abstract syntax tree to check our tokens stream to compliance with syntactic norms.
Our token expressions will be grouped into grammatical phrases.

Current stage: Done.
```
#
- # Lab 4 - Semantic Analyser

```
Semantic analyser is used for semantic errors detection. 
What called semantic error ? 

1) Logical errors 
    Example: 
        -Trying to access a variable out the scope
        -Wrong amount/type of function arguments
2) Type erros
    Example: 
        -int value + bool value 
        -string + int 
        ...and else..

Semantic analyser works with Lexical and Syntax analyser as well.
Lexical analyser gives a tokens list to syntax analyser.
Syntax analyser create an abstract syntax tree. 
What about semantic analyser? 
This analyser will parse tree and analyse each tree node (construction).
For each error, of course. 

Current stage: Done.
```

