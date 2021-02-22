# Sectra assignment

A simple calculator created that can add, subtract and multiply values in a set of registers. The syntax is quite simple:

```
<register> <operation> <value>
print <register>
quit
```

`<value>` is an integer value or a register.

The application takes a text file as input. To run the program from the console, build the program and then run the exe-file with the file name as the second argument.

## Run application from console
```
sectra_assignment.exe filepath
```

An example is:
```
sectra_assignment.exe input_file.txt
```

## Comments
- As of now the program takes the input from a file, but it could be modified to accept input from console
- The program is easy to make changes or additions to, e.g. adding a division operator.
