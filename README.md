# Finite Automaton Comparator
Implementation of a Finite Automaton Comparator in C++. The FA's can be DFA or NFA.

The program can compare two Finite Automaton, they are equivalent if they can accept the same strings.
The result of the program is EQUIVALENT or NOT_EQUIVALENT.

If a DFA is not minimum, the program first minimize the DFA.

## Author
Ángel Luis Igareta Herráiz

## Index
* [Usage](#usage)
* [License](#license)

## Usage
To start the program first you have to compile the source with MakeFile. After that you can start it executing:

```
.bin/compareFA FA1 FA2
```
After analyzing the FA passed by argument, the result of the program is EQUIVALENTE or NOT_EQUIVALENT.
    
Finally in the test folder there is an example of DFA and NFA test and syntax.
## License
The Mit License.
