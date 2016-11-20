#include "bfcompiler.h"
#include <iostream>
#include <string>
#include <sstream>


const std::string TEMPLATE_PART_ONE = 
    ".section    __TEXT,__text,regular,pure_instructions\n"
    "    .macosx_version_min 10, 12\n"
    "    .globl  _main\n"
    "    .align  4, 0x90\n"
    "\n"
    "_main:\n"
    "    .cfi_startproc\n"
    "    pushq   %rbp\n"
    "    .cfi_def_cfa_offset 16\n"
    "    .cfi_offset 6, -16\n"
    "    movq    %rsp, %rbp\n"
    "    .cfi_def_cfa_register 6\n"
    "\n"
    "    leaq    L_.str(%rip), %rdi\n"
    "    callq   _system\n"
    "    xorl    %ecx, %ecx\n"
    "\n";

const std::string TEMPLATE_PART_TWO = 
    "\n"
    "    movl    $0, %eax\n"
    "    popq    %rbp\n"
    "    .cfi_def_cfa 7, 8\n"
    "    ret\n"
    "    .cfi_endproc\n"
    "\n"
    "    .comm   _tape,";

const std::string TEMPLATE_PART_THREE =    
    ",4\n"
    "    .section    __DATA,__data\n"
    "    .globl  _i\n"
    "    .align  3\n"
    "\n"
    "_i:\n"
    "    .quad   _tape\n"
    "\n"
    "    .section    __TEXT,__cstring,cstring_literals\n"
    "L_.str:\n"
    "    .asciz  \"stty -icanon\"\n"
    "\n"
    ".subsections_via_symbols\n";

const std::string TOKEN_DOC = "# ";


BFCompiler::BFCompiler(std::string tokens) 
    : cond_id(0), loop_id(0), tape_size(DEFAULT_TAPE_SIZE), tokens(tokens) { }

BFCompiler::BFCompiler(std::string tokens, int tape_size) 
    : cond_id(0), loop_id(0), tape_size(tape_size), tokens(tokens) { }

std::string BFCompiler::format_template(std::string content) {
    std::stringstream s;
    s << TEMPLATE_PART_ONE << content << TEMPLATE_PART_TWO;
    s << tape_size << TEMPLATE_PART_THREE;
    return s.str();
}

std::string BFCompiler::token_doc(std::string token) {
    std::stringstream s;
    s << TOKEN_DOC << token << std::endl;
    return s.str();
}

std::string BFCompiler::add() {
    std::stringstream s;
    std::string compiled = 
        "    movq    _i(%rip), %rax\n"
        "    movzbl  (%rax), %edx\n"
        "    addl    $1, %edx\n"
        "    movb    %dl, (%rax)\n";
    s << token_doc("+") << compiled << std::endl;
    return s.str();
}

std::string BFCompiler::sub() {
    std::stringstream s;
    std::string compiled = 
        "    movq    _i(%rip), %rax\n"
        "    movzbl  (%rax), %edx\n"
        "    subl    $1, %edx\n"
        "    movb    %dl, (%rax)\n";
    s << token_doc("-") << compiled << std::endl;
    return s.str();
}

std::string BFCompiler::increment() {
    std::stringstream s;
    std::string compiled = 
        "    movq    _i(%rip), %rax\n"
        "    addq    $1, %rax\n"
        "    movq    %rax, _i(%rip)\n";
    s << token_doc(">") << compiled << std::endl;
    return s.str();
}

std::string BFCompiler::decrement() {
    std::stringstream s;
    std::string compiled = 
        "    movq    _i(%rip), %rax\n"
        "    subq    $1, %rax\n"
        "    movq    %rax, _i(%rip)\n";
    s << token_doc("<") << compiled << std::endl;
    return s.str();
}

std::string BFCompiler::putch() {
    std::stringstream s;
    std::string compiled = 
        "    movq    _i(%rip), %rax\n"
        "    movzbl  (%rax), %eax\n"
        "    movsbl  %al, %eax\n"
        "    movl    %eax, %edi\n"
        "    call    _putchar\n";
    s << token_doc(".") << compiled << std::endl;
    return s.str();
}

std::string BFCompiler::getch() {
    cond_id++;
    std::stringstream s;
    std::string compiled1 = 
        "    movq    _i(%rip), %rbx\n"
        "    call    _getchar\n"
        "    movb    %al, (%rbx)\n"
        "    movq    _i(%rip), %rax\n"
        "    movzbl  (%rax), %eax\n"
        "    cmpb    $4, %al\n"
        "    jne     .cond";
    std::string compiled2 =
        "\n"
        "    movq    _i(%rip), %rax\n"
        "    movb    $0, (%rax)\n"
        ".cond";
    s << token_doc(",") << compiled1 << cond_id;
    s << compiled2 << cond_id << ":\n\n";
    return s.str();
}

std::string BFCompiler::start_loop() {
    loop_id++;
    loop_stack.push(loop_id);
    std::stringstream s;
    std::string compiled1 = 
        ".loop_s";
    std::string compiled2 =
        "    movq    _i(%rip), %rax\n"
        "    movzbl  (%rax), %eax\n"
        "    cmpb    $0, %al\n"
        "    je      .loop_e";
    s << token_doc("[") << compiled1 << loop_id << ":\n";
    s << compiled2 << loop_id << "\n\n";
    return s.str();
}

std::string BFCompiler::end_loop() {
    int end_loop_id = loop_stack.top();
    loop_stack.pop();
    std::stringstream s;
    std::string compiled1 = 
        "   jmp      .loop_s";
    std::string compiled2 =
        ".loop_e";
    s << token_doc("]") << compiled1 << end_loop_id << std::endl;
    s << compiled2 << end_loop_id << ":\n\n";
    return s.str();
}

std::string BFCompiler::compile_tokens() {
    std::stringstream compile_stream;
    for (char& token : tokens) {
        switch(token) {
            case '+':
                compile_stream << add();
                break;
            case '-':
                compile_stream << sub();
                break;
            case '>':
                compile_stream << increment();
                break;
            case '<':
                compile_stream << decrement();
                break;
            case '.':
                compile_stream << putch();
                break;
            case ',':
                compile_stream << getch();
                break;
            case '[':
                compile_stream << start_loop();
                break;
            case ']':
                compile_stream << end_loop();
                break;
            default:
                break;
        }
    }
    return compile_stream.str();
}

std::string BFCompiler::compile() {
    return format_template(compile_tokens());
}