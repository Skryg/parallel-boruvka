#include "program_options.h"
#include <iostream>

std::unordered_map<std::string, int> args;

int program_options::get_num(std::string arg){
    try {
        std::size_t pos;
        int x = std::stoi(arg, &pos);
        if (pos < arg.size()) {
        std::cerr << "Trailing characters after number: " << arg << '\n';
        }
    } catch (std::invalid_argument const &ex) {
        std::cerr << "Invalid number: " << arg << '\n';
    } catch (std::out_of_range const &ex) {
        std::cerr << "Number out of range: " << arg << '\n';
    }
}

void program_options::parse(int argc, char* argv[])
{
    for(int i=1;i<argc;++i){

        std::string str = argv[i];
        if(str == "--input")
        args["input"]=1;
        if(str == "--vertices")
            if(argv[i+1] != NULL)
                args["n"] = get_num(argv[i+1]);
        if(str == "--edges")
            if(argv[i+1] != NULL)
                args["m"] = get_num(argv[i+1]);
    }
}

bool program_options::has_arg(std::string s)
{
    return args.find(s) != args.end();
}
int program_options::get_arg(std::string s)
{
    if(!has_arg(s)) throw std::runtime_error("Program options: No such argument!");
    return args[s];
}