#ifndef BFC_H
#define BFC_H

class BFC {
private:
    std::string in_file;
    std::string out_file;
    int tape_size;
    bool assembly;
    std::string compiled;

    void gen_out_file_name();
    void compile();
    void write_as_file();
    void assemble();

public:
    BFC(std::string in_file, bool assembly);
    BFC(std::string in_file, bool assembly, std::string out_file);
    BFC(std::string in_file, bool assembly, int tape_size);
    BFC(std::string in_file, bool assembly, std::string out_file, int tape_size);
    void run();
};

#endif