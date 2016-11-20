#ifndef BFCOMPILER_H
#define BFCOMPILER_H

#include <iostream>
#include <string>
#include <stack>


// Constants:
const int DEFAULT_TAPE_SIZE = 4000;

/**
    BrainFuck Compiler.
    Gets a string of tokens and a tape size.
    Returns a string of assembly output of compiled code.

    Example:
        BFCompiler compiler ("+++[>++<-].,.", 4000);
        compiled = compiler.compile();
*/
class BFCompiler {
private:
// Members:

    // Used to count ammount of conditions in the assembly code.
    // Initialized to 0.
    int cond_id;

    // Used to count ammount of loops in the assembly code.
    // Initialized to 0.
    int loop_id;

    // Defined Tape Size for the program.
    int tape_size;

    // Stack for following the scope of loops in the BrainFuck Code.
    std::stack<int> loop_stack;

    // BrainFuck tokens string to compile.
    std::string tokens;


// Private Methods:

    /** 
        Formats the assembly template with the compiled code,
        and the tape size.

        @param content: The compiled code to put in the template.

        @return: Full templated assembly code.
    */
    std::string format_template(std::string content);

    /**
        Gets a BrainFuck token and creates an assembly comment.

        @param token: BrainFuck token.

        @return: Assembly comment with the BrainFuck token.
    */
    std::string token_doc(std::string token);


    /**
        Creates the assembly code equivelent to '+' in BrainFuck,
        which is adding 1 to the char to whom the pointer is pointing.
        Adds at the top of the string a doc with the token.

        @return: Assembly code for this function.
    */
    std::string add();

    /**
        Creates the assembly code equivelent to '-' in BrainFuck,
        which is subtracting 1 from the char to whom the pointer is pointing.
        Adds at the top of the string a doc with the token.

        @return: Assembly code for this function.
    */
    std::string sub();

    /**
        Creates the assembly code equivelent to '>' in BrainFuck,
        which is adding 1 to the pointer and incrementing it's 
        position on the tape.
        Adds at the top of the string a doc with the token.

        @return: Assembly code for this function.
    */
    std::string increment();

    /**
        Creates the assembly code equivelent to '<' in BrainFuck,
        which is subtracting 1 from the pointer and decrementing it's 
        position on the tape.
        Adds at the top of the string a doc with the token.

        @return: Assembly code for this function.
    */
    std::string decrement();

    /**
        Creates the assembly code equivelent to '.' in BrainFuck,
        which is to put the char to whom the pointer is pointing
        to the stdout.
        Adds at the top of the string a doc with the token.

        @return: Assembly code for this function.
    */
    std::string putch();

    /**
        Creates the assembly code equivelent to ',' in BrainFuck,
        which is getting a single char from the stdin and putting it
        in the position to whom the pointer is pointing.
        Adds at the top of the string a doc with the token.

        The 'cond_id' member is incremented once, and the formatted into
        the assembly code.

        @return: Assembly code for this function.
    */
    std::string getch();

    /**
        Creates the assembly code equivelent to '[' in BrainFuck,
        which is to start a loop.
        Adds at the top of the string a doc with the token.

        The 'loop_id' member is incremented and pushed into the loop_stack,
        Then it is ormatted into the assembly code.

        @return: Assembly code for this function.
    */
    std::string start_loop();

    /**
        Creates the assembly code equivelent to ']' in BrainFuck,
        which is to end a loop.
        Adds at the top of the string a doc with the token.

        The top of the loop_stack is formatted into the assembly code,
        and the popped.

        @return: Assembly code for this function.
    */
    std::string end_loop();


    /**
        Loops over the 'tokens' member's chars. For each token,
        runs the appropriate function and concatinates the output to
        the compiled string.
        Adds at the top of the string a doc with the token.

        @return: A string of assembly code equivalent to the BrainFuck code.
    */
    std::string compile_tokens();

public:
// Public Methods:

    /**
        Constructor:
        Initializes with given tokens member.
        Initializes cond_id to 0, loop_id to 0 and
        default tape_size which is DEFAULT_TAPE_SIZE.

        @param tokens: BrainFuck tokens string to compile.
    */
    BFCompiler(std::string tokens);

    /**
        Constructor:
        Initializes with given tokens and tape_size members.
        Initializes cond_id to 0 and loop_id to 0.

        @param tokens: BrainFuck tokens string to compile.
        @param tape_size: Tape Size for the BrainFuck program.
    */
    BFCompiler(std::string tokens, int tape_size);


    /**
        Calls compile_tokens() and formats the output into the template
        by calling format_template().

        @return: Fully compiled and templated assembly code. 
    */
    std::string compile();
};

#endif