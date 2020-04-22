#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include<string>
#include<sstream>
struct Node {
private:
	int State_Name;
	std::string Differ = "";
	int Color;
public:
    Node();
    ~Node();
	Node(int StateName, int Color) {
		this->State_Name = StateName;
		this->Color = Color;
	}

	int GetStateName() {
		return this->State_Name;
	}

	int GetColor() {
		return this->Color;
	}

	void AppendString(int index) {
	    std::stringstream temp;
	    temp << index;
	    std::string str;
	    temp>>str;
		Differ.append(str);
	}

	std::string GetString() {
		return this->Differ;
	}

	void SetColor(int Color) {
		this->Color = Color;
	}

	void ClearString() {
		this->Differ = "";
	}
};


#endif // NODE_H_INCLUDED
