#ifndef BFCOMPILER_H
#define BFCOMPILER_H

#include <iostream>
#include <string>
#include <stack>


const int DEFAULT_TAPE_SIZE = 4000;


class BFCompiler {
private:
    int cond_id;
    int loop_id;
    int tape_size;
    std::stack<int> loop_stack;
    std::string tokens;

    std::string format_template(std::string content);
    std::string token_doc(std::string token);

    std::string add();
    std::string sub();
    std::string increment();
    std::string decrement();
    std::string putch();
    std::string getch();
    std::string start_loop();
    std::string end_loop();

    std::string compile_tokens();

public:
    BFCompiler(std::string tokens);
    BFCompiler(std::string tokens, int tape_size);
    std::string compile();
};

#endif