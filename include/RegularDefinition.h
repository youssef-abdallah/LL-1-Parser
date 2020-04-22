#pragma once
#include "includes.h"

class RegularDefinition
{
public:
    RegularDefinition();
    ~RegularDefinition();
	string values_to_string();
	void add_part_of_values(vector<char> v);
	void setValues(vector<char> v);
	void setDefinitionType(string type);
	vector<char> getValues();
	string getDefinitionType();
	void set_values_string(string value);

	bool operator < (RegularDefinition rd1) {
	return (rd1.getDefinitionType().size() < definition_type.size());
}


private:

	string definition_type;
	vector<char> values;
	string values_string = "";

};

