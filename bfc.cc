#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

#include<sys/types.h>
#include <stdlib.h>

#include "bfc.h"
#include "bfcompiler.h"

// Private Methods:

void BFC::gen_out_file_name() {
    std::string file_name = in_file.substr(0, in_file.find("."));
    std::string suffix = ".o";
    if (assembly)
        suffix = ".s";
    out_file = file_name + suffix;
}

void BFC::compile() {
    std::string line;
    std::ifstream file_stream (in_file);
    std::stringstream string_stream;
    if (file_stream.is_open()) {
        while (getline (file_stream, line)) {
            string_stream << line << std::endl;
        }
        file_stream.close();
    } else std::cout << "Unable to open file"; 

    std::string bf_string = string_stream.str();
    BFCompiler compiler (bf_string, tape_size);
    compiled = compiler.compile();
}

void BFC::write_as_file() {
    std::ofstream file_stream (out_file);
    if (file_stream.is_open()) {
        file_stream << compiled;
        file_stream.close();
    } else std::cout << "Unable to open file";
}

void BFC::assemble() {
    char *tmp_file_name = strdup("/tmp/bfcc.XXXXXX");
    mkstemp(tmp_file_name);
    char *suffix = strdup(".s");
    strcat(tmp_file_name, suffix);
    std::ofstream file_stream (tmp_file_name);
    if (file_stream.is_open()) {
        file_stream << compiled;
        file_stream.close();
    } else std::cout << "Unable to open file";

    std::stringstream command_stream;
    command_stream << "gcc " << tmp_file_name << " -o " << out_file;
    std::string command_string = command_stream.str();

    std::system(command_string.c_str());
    std::remove(tmp_file_name);
}


// Public Methods:

// Constructor:
BFC::BFC(std::string in_file, bool assembly) 
    : in_file(in_file), tape_size(DEFAULT_TAPE_SIZE), assembly(assembly)  {
        gen_out_file_name();
    }

// Constructor:
BFC::BFC(std::string in_file, bool assembly, int tape_size)
    : in_file(in_file), tape_size(tape_size), assembly(assembly) {
        gen_out_file_name();
    }

// Constructor:
BFC::BFC(std::string in_file, bool assembly, std::string out_file)
    : in_file(in_file), out_file(out_file), tape_size(DEFAULT_TAPE_SIZE), assembly(assembly) { }

// Constructor:
BFC::BFC(std::string in_file, bool assembly, std::string out_file, int tape_size)
    : in_file(in_file), out_file(out_file), tape_size(tape_size), assembly(assembly) { }


void BFC::run() {
    compile();
    if (assembly)
        write_as_file();
    else
        assemble();
}
