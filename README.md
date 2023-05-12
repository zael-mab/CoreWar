## CoreWar

The Corewar project is part of the 42 School curriculum. It involves building a virtual machine and an assembler that can read assembly language programs and output bytecode that can be executed on the virtual machine.

### Project Description
The goal of the project is to create a game called "Corewar" in which players write programs (called "champions") that are loaded into a virtual machine and compete against each other. Each champion tries to overwrite the memory of the other champions in the virtual machine, and the last champion standing wins.

The project has two main components: a virtual machine and an assembler.

### Virtual Machine
The virtual machine is responsible for executing the bytecode generated by the assembler. It is designed to simulate a simplified computer architecture with a set of registers and a memory. It loads the champions into memory and executes their instructions until one of the champions wins.

### Assembler
The assembler reads assembly code written by the user and generates bytecode that can be executed by the virtual machine. It is responsible for parsing the assembly code, generating the corresponding bytecode, and writing the bytecode to a file.

### Usage For The Assembler Part
run the following command:

```make```

This will generate an executable file: `asm`

To assemble a champion, run the following command:

```./asm [champion.s]```

### Acknowledgements
This project is inspired by the Core War game developed by D. G. Jones and A. K. Dewdney in 1984.
