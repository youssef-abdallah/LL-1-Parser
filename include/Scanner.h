#pragma once
#include "includes.h"
#include <map>
#include "RegularDefinition.h"
#include "RegularExpression.h"

using namespace std;

class Scanner {

public:
    static Scanner& getInstance();

	void read_lexical_rules(std::string file_name);

    vector<string> keywords;
    vector<string> punctuations;

    vector<RegularDefinition> reg_definitions;
    vector<RegularExpression> reg_expressions;
    vector<string> process_input_program(string file_name);


    Scanner(Scanner const&) = delete;
    void operator=(Scanner const&) = delete;

private:
    Scanner();

    char conc_operator = '~';
    char epsilon = 0;
    bool has_definitions = false;
    vector<RegularExpression> keywords_expression;


    void space_splitter(string line, char delim);
    void regular_def_scanner(string line);
    void regular_exp_scanner(string line);
    vector<int> find_all_occurences(string line, char delim);
    vector<char> add_values(string line, int start, int end);
    string remove_plus_operator(string line, string defType);
    string replace_definitions(string line, string defType, string replacement);
    string additional_manipulations(string line);
    string handle_special_operators(string line);
    string remove_spaces(string line);
    string insert_concatination_op(string line, int st, int length);
    string add_backslash_before(string line, string s);
    void add_special_expression(bool highest_priority);
    void add_first();

};
