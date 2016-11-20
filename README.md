# Brain Fuck CPP Compiler

Similar to my [previous BrainFuck Compiler](https://bitbucket.org/quaark/brainfuck-compiler), 
gets a file with brainfuck code written in it, compiles it, and either outputs the assembly file or assembles it to a binary.
However, this time, implemented int C++.

### Clone or download the repository & install package
Download the repository and run:
```sh
make install
```

### Usage
Run the command
```sh
bfcc -h
```
 And it will output the usage:
```sh
Usage: bfcc [options] input-file

Options:
  -h [ --help ]                  Print help messages
  -S [ --assembly ]              Output assembly file instead of binary file
  -t [ --tape-size ] arg (=4000) Tape size of brainfuck program
  -i [ --input-file ] arg        Input Files
  -o [ --output-file ] arg       Name of the output file

```

**Enjoy!**
