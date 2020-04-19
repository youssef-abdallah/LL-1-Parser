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
    //eliminateLeftRecursion();
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

void ReadFile::eliminateLeftRecursion() {
    vector<vector<string>> newGrammarFile;
    vector<string> rule;
    for (unsigned int i = 0; i < GrammarFile.size(); i++) {
        for (unsigned int j = 0; j < i; j++) {
            vector<string> newProduction;
            newProduction.insert(newProduction.end(), GrammarFile[i].begin(), GrammarFile[i].begin() + 3);
            for (unsigned int k = 3; k < GrammarFile[i].size(); k++) {
                if (GrammarFile[i][k] != "|") {
                    rule.push_back(GrammarFile[i][k]);
                }
                if (k + 1 == GrammarFile[i].size() || GrammarFile[i][k] == "|") {
                    if (rule.size()) {
                        if (GrammarFile[j][1] == rule[0]) {
                            vector<string> gamma = {rule.begin() + 1, rule.end()};
                            vector<vector<string>> alphas;
                            vector<string> alpha;
                            for (unsigned int x = 3; x < GrammarFile[j].size(); x++) {
                                if (GrammarFile[j][x] != "|") {
                                    alpha.push_back(GrammarFile[j][x]);
                                }
                                if (x == GrammarFile[j].size() - 1 || GrammarFile[j][x] == "|") {
                                    if (alpha.size()) alphas.push_back(alpha);
                                    alpha.clear();
                                }
                            }
                            for (vector<string> &alpha : alphas) {
                                alpha.insert(alpha.end(), gamma.begin(), gamma.end());
                                newProduction.insert(newProduction.end(), alpha.begin(), alpha.end());
                                newProduction.push_back({"|"});
                            }
                        } else {
                            newProduction.insert(newProduction.end(), rule.begin(), rule.end());
                            newProduction.push_back({"|"});
                        }
                        if (k + 1 == GrammarFile[i].size()) newProduction.pop_back();
                        rule.clear();
                    }
                }
            }
            GrammarFile[i] = newProduction;
        }
        eliminateImmediateLeftRecursion(i + 1);
    }
}

void ReadFile::eliminateImmediateLeftRecursion(unsigned int sz) {
    for (unsigned int x = 0; x < sz; x++) {
        vector<string> &production = GrammarFile[x];
        string nonTerminal = production[1];
        vector<string> rule;
        vector<vector<string>> alphas, betas;
        for (unsigned int i = 3; i < production.size(); i++) {
            if (production[i] != "|") {
                rule.push_back(production[i]);
            }
            if (i == production.size() - 1 || production[i] == "|") {
                if (rule.size()) {
                    if (rule[0] == nonTerminal) {
                        vector<string> tmp = {rule.begin() + 1, rule.end()};
                        alphas.push_back(tmp);
                    } else {
                        betas.push_back(rule);
                    }
                    rule.clear();
                }
            }
        }
        if (alphas.size()) {
            vector<string> firstNewProduction, secondNewProduction;
            string newNonTeminal = nonTerminal + "dash";
            firstNewProduction.push_back("#");
            firstNewProduction.push_back(nonTerminal);
            firstNewProduction.push_back("=");
            for (auto beta = betas.begin(); beta != betas.end(); beta++) {
                (*beta).push_back(newNonTeminal);
                firstNewProduction.insert(firstNewProduction.end(), beta->begin(), beta->end());
                if (beta + 1 != betas.end()) firstNewProduction.push_back("|");
            }
            secondNewProduction.push_back("#");
            secondNewProduction.push_back(newNonTeminal);
            secondNewProduction.push_back("=");
            for (auto alpha = alphas.begin(); alpha != alphas.end(); alpha++) {
                (*alpha).push_back(newNonTeminal);
                secondNewProduction.insert(secondNewProduction.end(), alpha->begin(), alpha->end());
                secondNewProduction.push_back("|");
            }
            secondNewProduction.push_back("\\L");
            GrammarFile[x] = firstNewProduction;
            GrammarFile.insert(GrammarFile.begin() + x + 1, secondNewProduction);
            sz++;
        }
    }
}
