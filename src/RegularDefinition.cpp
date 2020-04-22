#include "../include/RegularDefinition.h"

RegularDefinition::RegularDefinition() {


}

RegularDefinition::~RegularDefinition() {


}

void RegularDefinition::setValues(vector<char> v) {
	values = v;
}

vector<char> RegularDefinition::getValues() {
	return values;
}

void RegularDefinition::setDefinitionType(string type) {
	definition_type = type;
}

string RegularDefinition::getDefinitionType() {
	return definition_type;
}

void RegularDefinition::add_part_of_values(vector<char> v){
    string result = "";
	for (int i = 0; i < (int) v.size(); i++) {
		char next_value = v[i];
		result = result + next_value ;
		if (i != (int) v.size() - 1) {
			result = result + '|';
		}
	}

	result = "(" + result + ")";
	if (values_string == "")
        values_string = result;
    else
        values_string = values_string + "|" + result;


}

void RegularDefinition::set_values_string(string value){
    values_string = value;
}


string RegularDefinition::values_to_string() {
    if (values_string[0] == '|'){
        return values_string.substr(1, values_string.size() - 1);
    }
	return values_string;
}



