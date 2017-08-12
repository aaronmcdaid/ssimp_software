#include <iostream>
#include <fstream>
#include <set>

#include "../src/bits.and.pieces/PP.hh"
#include "../src/bits.and.pieces/DIE.hh"
#include "../src/bits.and.pieces/utils.hh"

using std:: ifstream;
using std:: cout;
using std:: string;
using std:: set;

int main(int argc, char **argv) {
    argc == 4 || DIE("needs 4 args");

    string line;
    set<int> all_rs_in_any_file;

    ifstream  fs_1kg(argv[1]);

    while(getline( fs_1kg, line)) {
        if(line == "#CHROM\tPOS\tID")
            continue;
        //PP(line);
        auto tokens = utils:: tokenize(line, '\t');
        auto third = tokens.at(2);

        for(auto split_on_semicolons : utils:: tokenize(third, ';')) {
            if(split_on_semicolons.substr(0, 2) == "rs") {
                split_on_semicolons = split_on_semicolons.substr(2);
                auto rs_1kg = utils:: lexical_cast<int>(split_on_semicolons);
                //PP(split_on_semicolons); PP(rs_1kg);
                all_rs_in_any_file.insert(rs_1kg);
            }
        }

    }
    PP(all_rs_in_any_file.size());
}
