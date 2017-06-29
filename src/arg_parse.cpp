/*
 * Implementation of arge_parse.h
 */

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "arg_parse.h"

using std::cout;
using std::endl;
using std::exit;
using std::vector;
using std::string;

Args ArgParse::parseArgs(int argc, char* argv[]) {
    Options options("kleuren", "A colored de Bruijn graph implementation using dbgfm.");

    this->args = Args();

    try {
        // set up each argument
        options.add_options()
            ("c,colorsFilePath", "Path to the file that holds the paths to the individual colors.",
                cxxopts::value<string>())
            ("k,kmerLen", "Kmer length to use when querying the colors.", cxxopts::value<size_t>(),
                "31")
            ("h,help", "Print help")
        ;

        // specify required arguments
        vector<string> required;
        required.push_back("colorsFilePath");
        required.push_back("kmerLen");

        // parse the arguments
        options.parse(argc, argv);

        // print the help menu
        if(options.count("help")) {
            cout << options.help() << endl;
            exit(0);
        }

        check_required(options, required);

        setArgs(options);

    } catch(const cxxopts::OptionException& e) {
        cout << options.help() << endl;
        cout << "Error parsing options: " << e.what() << endl;
        exit(1);
    }

    return args;
}

void ArgParse::setArgs(Options options) {
    args.setColorsFilePath(options["colorsFilePath"].as<string>());
    args.setKmerLen(options["kmerLen"].as<size_t>());
}