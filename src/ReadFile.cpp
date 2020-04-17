#include <ReadFile.h>

ReadFile::ReadFile()
{
    vector<std::string> Current_Production, Next_Production;
    string line;
    ifstream myfile ("./test/Grammar3.txt");
    if (myfile.is_open()){
        while ( getline (myfile,line) ){
            Next_Production = ExractStrings(line);
            if (NewProduction(Next_Production[0])){
                if (Current_Production.size() > 0){
                    GrammarFile.insert(GrammarFile.end(), Current_Production);
                }
                Current_Production = Next_Production;
            } else {
                Current_Production.insert(Current_Production.end(), Next_Production.begin(), Next_Production.end());
            }
        }
        GrammarFile.insert(GrammarFile.end(), Current_Production);
        myfile.close();
    } else {
        cout << "Unable to open file";
    }
    AddProductions();
    /*for (int i = 0; i < GrammarFile.size(); i++){
        vector<std::string> temp = GrammarFile[i];
        for(int j = 0; j < temp.size(); j++){
            cout << temp[j] << " ** ";
        }
        cout << '\n';
    }*/
}

ReadFile::~ReadFile()
{
    //dtor
}

vector <std::string> ReadFile::ExractStrings(std::string str){
    std::regex Split_Space("\\s+");
    std::vector<std::string> result{std::sregex_token_iterator(str.begin(), str.end(), Split_Space, -1), {}};
    if (result[0] == ""){
        result.erase (result.begin());
    }
    return result;
}

bool ReadFile::NewProduction(std::string first_element){
    if (first_element == "#"){
        return true;
    }
    return false;
}

void ReadFile::AddProductions(){
    int index = 0;
    vector <vector <shared_ptr<Token>>> productions;
    vector <shared_ptr<Token>> production;
    for (unsigned int i = 0; i < GrammarFile.size(); i++){
        vector<std::string> temp = GrammarFile[i];
        auto t = Non_Terminals.find(temp[1]);
        shared_ptr<NonTerminal> p;
        if (t == Non_Terminals.end()){
            p = make_shared<NonTerminal>(temp[1]);
            Non_Terminals.emplace(temp[1], p);
        } else {
            p = t->second;
        }
        if (i == 0){
            grammar.setStartingSymbol(p);
        }

        for(unsigned int j = 3; j < temp.size(); j++){
            if (temp[j] == "|" || ((temp[j].find("\\")) != std::string::npos)){
                vector <shared_ptr<Token>> Temp = production;
                production.clear();
                productions.push_back(Temp);
                grammar.addProduction(p,productions[index]);
                index++;
            } else {
                if ((temp[j].find("'")) != std::string::npos){
                    // then this Token
                    auto t = Tokens.find((temp[j].substr(1,temp[j].length() - 2)));
                    if (t == Tokens.end()){
                        shared_ptr<Token> token = make_shared<Terminal>(temp[j].substr(1,temp[j].length() - 2));
                        Tokens.emplace((temp[j].substr(1,temp[j].length() - 2)), token);
                        production.push_back(token);
                        Terminals.push_back(token);
                    } else {
                        production.push_back(t->second);
                    }
                } else {
                    // this terminal
                    auto t = Non_Terminals.find(temp[j]);
                    if (t == Non_Terminals.end()){
                        shared_ptr<NonTerminal> nonTerminal = make_shared<NonTerminal>(temp[j]);
                        Non_Terminals.emplace(temp[j], nonTerminal);
                        production.push_back(nonTerminal);
                    } else {
                        production.push_back(t->second);
                    }
                }
            }
        }
        vector <shared_ptr<Token>> Temp = production;
        production.clear();
        productions.push_back(Temp);
        grammar.addProduction(p,(productions[index]));
        NonTerminals.push_back(p);
        index++;
    }
}

Grammar ReadFile::GetGrammar(){
    return grammar;
}

vector<shared_ptr<Token>> ReadFile::GetTerminals(){
    return Terminals;
}

vector<shared_ptr<NonTerminal>> ReadFile::GetNonTerminals(){
    return NonTerminals;
}
