# Circuit-Simulator
This is a program created to simulate a circuit. It takes two arguments: The circuit description, and the circuit inputs to be tested.

The first file is the circuit description and is formatted in the following manner:
The first line gives which identifiers are to be input variables. The line begins with INPUTVAR then gives the number and   the identifiers. The second line does the same with output variables.

From then on, each line is a gate that begins with the type of gate, and how many inputs it takes. Then identifiers are   given for the inputs [single characters...can also be 0/1]

The second file is the inputs for the circuit to be tested. Each line represents one set of inputs, and each whitespace separated token represents an input. For each line in this file the program will output the resultant output variables according to the circuit described by the first file.

Gates allowed: AND, OR, NOT, MULTIPLEXER, DECODER.


An example for clarity:
File1:
  INPUTVAR 8 A B C D E F G H
  OUTPUTVAR 2 X Y
  AND A B k
  OR E F 1
  NOT H m
  MULTIPLEXER 8 0 A B C D E 1 G k l m X
  AND H m Y
File2:
  0 1 1 1 0 1 0 1
  0 1 0 1 0 1 0 0
  0 0 0 0 0 0 0 0
  1 1 1 1 1 1 0 1
  0 1 0 1 1 1 0 0
  1 0 1 0 1 0 1 0
  0 1 1 0 0 0 1 1
Output:
  1 0
  1 0
  0 0
  1 0
  1 0
  0 0
  0 0
