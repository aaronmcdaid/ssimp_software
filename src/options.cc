#include "options.hh"

#include <getopt.h>
#include <iostream>

#include "bits.and.pieces/DIE.hh"
#include "bits.and.pieces/utils.hh"

using std:: string;

namespace options {

        std:: string            opt_raw_ref;
        std:: string            opt_gwas_filename;
        std:: string            opt_out;
        int                     opt_window_width = 1'000'000;
        int                     opt_flanking_width = 250'000;
        double                  opt_lambda  = 0.0;

        std:: string            opt_impute_range;
        std:: string            opt_impute_snps;
        std::unordered_set<std::string>    opt_impute_snps_as_a_uset;
        double                  opt_impute_maf =0.0;

        // The next few are like the --impute.* above, but applying to tags instead
        std:: string            opt_tags_range;
        std:: string            opt_tags_snps;
        std::unordered_set<std::string>    opt_tags_snps_as_a_uset;
        double                  opt_tags_maf =0.0; // target not imputed unless maf (in reference) is at least this.

void read_in_all_command_line_options(int argc, char **argv) {
    while(1) { // while there are still more options to be processed
        int long_option_index;
        static struct option long_options[] = {
            //{"header.in",  no_argument, &opt_headerin,  1 }, // a boolean flag
            {"ref"                ,  required_argument, 0,  2 }, // last arg on each line must be greater than 1
            {"window.width"       ,  required_argument, 0,  3 },
            {"flanking.width"     ,  required_argument, 0,  4 },
            {"gwas"               ,  required_argument, 0,  5 },
            {"lambda"             ,  required_argument, 0,  6 },
            {"out"                ,  required_argument, 0,  7 },
            {"impute.range"       ,  required_argument, 0,  8 },
            {"impute.snps"        ,  required_argument, 0,  9 },
            {"impute.maf"         ,  required_argument, 0, 10 },
            {"tags.range"         ,  required_argument, 0, 11 },
            {"tags.snps"          ,  required_argument, 0, 12 },
            {"tags.maf"           ,  required_argument, 0, 13 },
            {0                    ,  0                , 0,  0 } // must have this line of zeroes at the end
        };
        int c = getopt_long(argc, argv, "-", long_options, &long_option_index);
        if (c == -1)
            break;
        if (c == 1) { // non-option
            DIE("There shouldn't be any non-options args to this program: ["<<optarg<<"]");
        }
        if (c == 2) {
            assert(string("ref") == long_options[long_option_index].name);
            options:: opt_raw_ref = optarg;
        }
        if (c == 3) {
            assert(string("window.width") == long_options[long_option_index].name);
            options::  opt_window_width  = utils:: lexical_cast<int>(optarg);
        }
        if (c == 4) {
            assert(string("flanking.width") == long_options[long_option_index].name);
            options::  opt_flanking_width  = utils:: lexical_cast<int>(optarg);
        }
        if (c == 5) {
            assert(string("gwas") == long_options[long_option_index].name);
            options::  opt_gwas_filename = optarg;
        }
        if (c == 6) {
            assert(string("lambda") == long_options[long_option_index].name);
            options::  opt_lambda  = utils:: lexical_cast<double>(optarg);
        }
        if (c == 7) {
            assert(string("out") == long_options[long_option_index].name);
            options::  opt_out = optarg;
        }
        if (c == 8) {
            options:: opt_impute_range.empty() || DIE("--impute.range specified twice?");
            assert(string("impute.range") == long_options[long_option_index].name);
            options::  opt_impute_range = optarg;
        }
        if (c == 9) {
            options:: opt_impute_snps.empty() || DIE("--impute.snps specified twice?");
            assert(string("impute.snps") == long_options[long_option_index].name);
            options::  opt_impute_snps = optarg;
        }
        if (c == 10) {
            options:: opt_impute_maf == 0.0 || DIE("--impute.maf specified twice?");
            assert(string("impute.maf") == long_options[long_option_index].name);
            options::  opt_impute_maf = utils:: lexical_cast<double>(optarg);
        }
        if (c == 11) {
            options:: opt_tags_range.empty() || DIE("--tags.range specified twice?");
            assert(string("tags.range") == long_options[long_option_index].name);
            options::  opt_tags_range = optarg;
        }
        if (c == 12) {
            options:: opt_tags_snps.empty() || DIE("--tags.snps specified twice?");
            assert(string("tags.snps") == long_options[long_option_index].name);
            options::  opt_tags_snps = optarg;
        }
        if (c == 13) {
            options:: opt_tags_maf == 0.0 || DIE("--tags.maf specified twice?");
            assert(string("tags.maf") == long_options[long_option_index].name);
            options::  opt_tags_maf = utils:: lexical_cast<double>(optarg);
        }
    }
}

} // namespace options
