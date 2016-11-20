#include "boost/program_options.hpp"
#include "bfc.h"
#include "bfcompiler.h"

#include <iostream> 
#include <string> 


namespace { 
  const size_t ERROR_IN_COMMAND_LINE = 1; 
  const size_t SUCCESS = 0; 
  const size_t ERROR_UNHANDLED_EXCEPTION = 2; 
}

std::string app_name;
namespace po = boost::program_options;
po::options_description desc("Options");


void print_help(bool error) {
    if (error) {
        std::cerr << "Usage: " << app_name << " [options] input-file" << std::endl;
        std::cerr << std::endl << desc << std::endl;
    } else {
        std::cout << "Usage: " << app_name << " [options] input-file" << std::endl;
        std::cout << std::endl << desc << std::endl;
    }
}

boost::program_options::variables_map parse_arguments(int argc, char** argv) {
    desc.add_options() 
        ("help,h", "Print help messages") 
        ("assembly,S", "Output assembly file instead of binary file") 
        ("tape-size,t", po::value<int>()->default_value(DEFAULT_TAPE_SIZE),
            "Tape size of brainfuck program")
        ("input-file,i", po::value<std::string>()->required(), "Input Files")
        ("output-file,o", po::value<std::string>(), "Name of the output file");

    po::positional_options_description positional_options;
    positional_options.add("input-file", 1);

    po::variables_map variables_map;
    po::store(po::command_line_parser(argc, argv).
        options(desc).positional(positional_options).run(), 
        variables_map);

    return variables_map;
}
 
int cli(int argc, char** argv) { 
    po::variables_map variables_map;
    try { 
        app_name = argv[0]; 
        variables_map = parse_arguments(argc, argv);

        if (variables_map.count("help")) {
            print_help(false);
            return SUCCESS; 
        }

        po::notify(variables_map);
    } catch(po::error& e) { 
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl; 
        print_help(true);
        return ERROR_IN_COMMAND_LINE; 
    } 
    
    if (variables_map.count("output-file")) {
        BFC b (variables_map["input-file"].as<std::string>(),
               variables_map.count("assembly"),
               variables_map["output-file"].as<std::string>(),
               variables_map["tape-size"].as<int>());
        b.run();
    } else {
        BFC b (variables_map["input-file"].as<std::string>(),
               variables_map.count("assembly"),
               variables_map["tape-size"].as<int>());
        b.run();
    }
 
    return SUCCESS; 
}


int main(int argc, char** argv) {
    try {
        return cli(argc, argv);
    } catch(std::exception& e) { 
        std::cerr << "Unhandled Exception reached the top of main: " 
                  << e.what() << ", application will now exit" << std::endl; 
        return ERROR_UNHANDLED_EXCEPTION; 
    } 
}