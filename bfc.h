#ifndef BFC_H
#define BFC_H

/**
    BrainFuck Compiler Cli.
    Gets Input File, Output File, Tape Size and Output Type(Assembly or Binary).
    Outputs the compiled file.
    
    Example:
        BFC bfc("in.b", false);
        bfc.run();
*/
class BFC {
private:
// Members:

    // Input file name, for extracting BrainFuck Code.
    std::string in_file;

    // Output file name, for outputting assembly or binary file.
    std::string out_file;

    // Tape size of the BrainFuck program.
    int tape_size;

    // Wether to output Assembly or Binary.
    bool assembly;

    // Compiled Assembly code.
    std::string compiled;


// Private Methods:

    /**
        If output file was not given, Generates a output file name 
        with the original file name.
    */
    void gen_out_file_name();

    /**
        Opens the input file and compiles the BrainFuck code,
        by using the BFCompiler class form bfcompiler.h, and saves 
        it in the 'compiled' member.
    */
    void compile();

    /**
        Writes Assembly output from the 'compiled' member in the output file.
    */
    void write_as_file();

    /** 
        Creates a tmpfile to store the assembly output in.
        Then runs gcc to compile the code into the output binary file.
        Finally, deletes the tmpfile.
    */
    void assemble();

public:
// Public Methods:

    /**
        Constructor:
        Initializes with given in_file, and assembly members.
        Initializes default tape_size which is DEFAULT_TAPE_SIZE from bfcompiler.h.
        Calls gen_out_file_name() to generate a output file name.

        @param in_file: The input file name.
        @param assembly: Wether to output Assembly or Binary.
    */
    BFC(std::string in_file, bool assembly);

    /**
        Constructor:
        Initializes with given in_file, assembly and tape_size members.
        Calls gen_out_file_name() to generate a output file name.

        @param in_file: The input file name.
        @param assembly: Wether to output Assembly or Binary.
        @param tape_size: Tape size of the BrainFuck program.
    */
    BFC(std::string in_file, bool assembly, int tape_size);

    /** 
        Constructor:
        Initializes with given in_file, assembly and out_file members.
        Initializes default tape_size which is DEFAULT_TAPE_SIZE from bfcompiler.h.

        @param in_file: The input file name.
        @param assembly: Wether to output Assembly or Binary.
        @param out_file: Output file name.
    */
    BFC(std::string in_file, bool assembly, std::string out_file);

    /**
        Constructor:
        Initializes with given in_file, assembly, out_file and tape_size members.

        @param in_file: The input file name.
        @param assembly: Wether to output Assembly or Binary.
        @param out_file: Output file name.
        @param tape_size: Tape size of the BrainFuck program.
    */
    BFC(std::string in_file, bool assembly, std::string out_file, int tape_size);

    /**
        Runs the CLI with either the 
        write_as_file() if the 'assembly' member is set to true, or
        assemble() if the 'assembly' member is set to false.
    */
    void run();
};

#endif