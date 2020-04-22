#include <ReadFile.h>

ReadFile::ReadFile()
{
    vector<std::string> Current_Production, Next_Production;
    string line;
    ifstream myfile ("./test/Grammar6.txt");
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
    eliminateLeftRecursion();
    EliminateLeftFactoring();
    AddProductions();
    for (unsigned i = 0; i < LLGrammarFile.size(); i++){
        vector<std::string> temp =  LLGrammarFile[i];
        for(unsigned j = 0; j < temp.size(); j++){
            cout << temp[j] << " ";
        }
        cout << '\n';
    }
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
    for (unsigned int i = 0; i < LLGrammarFile.size(); i++){
        vector<std::string> temp = LLGrammarFile[i];
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
            if (temp[j] == "|" || ((temp[j].find("\\L")) != std::string::npos)){
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

void ReadFile::EliminateLeftFactoring(){
    vector<vector<FactorNode>> Eliminations;
    for (unsigned i = 0; i < GrammarFile.size(); i++){
        vector<std::string> Current_Production = GrammarFile[i];
        vector<vector<std::string>> Productions = SplitProduction(Current_Production);
        for (unsigned j = 0; j < Productions.size() - 1; j++){
            auto temp = Used_Production.find(j);
            if (temp == Used_Production.end()){
                for (unsigned k = j + 1; k < Productions.size(); k++){
                    auto temp = Used_Production.find(k);
                    if (temp == Used_Production.end()){
                        vector<std::string> CommonString = GetCommon(Productions[j], Productions[k]);
                        if (CommonString.size() != 0){
                            InsertNode(j, k, CommonString);
                        }
                    }
                }
                sort(nodes.begin(), nodes.end(), CompareSize);
                if (nodes.size() != 0){
                    Eliminations.push_back(nodes);
                    nodes.clear();
                }
            }
        }
        if (Eliminations.size() != 0){
            AddLeftFactoring(Eliminations, Productions, Current_Production[1]);
            Used_Production.clear();
            Eliminations.clear();
        } else {
            LLGrammarFile.push_back(Current_Production);
        }

    }
}

vector<vector<std::string>> ReadFile::SplitProduction(vector<std::string> Production){
    vector<vector<std::string>> Result;
    vector<std::string> Temp;
    for (unsigned i = 3; i < Production.size(); i++){
        if (Production[i] == "|"){
            Result.push_back(Temp);
            Temp.clear();
        } else {
            Temp.push_back(Production[i]);
        }
    }
    Result.push_back(Temp);
    return Result;
}

vector<std::string> ReadFile::GetCommon(vector<std::string> v1, vector<std::string> v2){
    vector<std::string> result;
    int Size1 = v1.size(), Size2 = v2.size(), Size;
    if (Size1 < Size2){
        Size = Size1;
    } else {
        Size = Size2;
    }
    for (int i = 0; i < Size; i++){
        if (v1[i] == v2[i] && ((v1[i].find("\\")) == std::string::npos)){
            result.push_back(v1[i]);
        } else {
            break;
        }
    }
    return result;
}

bool CompareSize(FactorNode n1, FactorNode n2){
    return (n1.GetSize() < n2.GetSize());
}

void ReadFile::InsertNode(int ProductionNum1 , int ProductionNum2, vector<std::string> Common){
    int Check = -1;
    for(unsigned i = 0; i < nodes.size(); i++){
        if (Common.size() == nodes[i].GetSize()){
            Check = i;
            break;
        }
    }
    if (Check != -1){
        nodes[Check].AddNumOfProduction(ProductionNum2);
    } else {
        FactorNode temp(Common.size(), Common);
        temp.AddNumOfProduction(ProductionNum1);
        temp.AddNumOfProduction(ProductionNum2);
        nodes.push_back(temp);
    }
    Used_Production.emplace(ProductionNum1, true);
    Used_Production.emplace(ProductionNum2, true);
}

void ReadFile::AddLeftFactoring(vector<vector<FactorNode>> Elemination, vector<vector<std::string>> Productions, std::string NonTerminal){
    unordered_map <int, bool> Used;
    for(unsigned i = 0; i < Elemination.size(); i++){
        vector<FactorNode> temp = Elemination[i];
        for (int j = temp.size() - 2; j >= 0; j --){
            vector<int> tt = temp[j + 1].GetProductions();
            vector<int> tt2 = temp[j].GetProductions();
            for (unsigned k = 0; k < tt2.size(); k++){
                Used.emplace(tt2[k], true);
            }
            for (unsigned k = 0; k < tt.size(); k++){
                auto te = Used.find(tt[k]);
                if (te == Used.end()){
                    ((Elemination[i])[j]).AddNumOfProduction(tt[k]);
                }
            }
            Used.clear();
        }
    }
    int index = 1;
    vector<std::string> FirstProduction;
    bool FirstSet[Productions.size()];
    FirstProduction.push_back("#");
    FirstProduction.push_back(NonTerminal);
    FirstProduction.push_back("=");
    for (unsigned i = 0; i < Elemination.size(); i++){
        vector<FactorNode> temp = Elemination[i];
        vector<int> Nums= temp[0].GetProductions();
        for (unsigned j = 0; j < Nums.size(); j++){
            FirstSet[Nums[j]] = true;
        }
        vector <string> t = temp[0].GetCommonString();
        FirstProduction.insert(FirstProduction.end(), t.begin(), t.end());
        stringstream ss;
        ss << index;
        string str = ss.str();
        FirstProduction.push_back(NonTerminal + str);
        FirstProduction.push_back("|");
        index = index + temp.size();
    }
    for (unsigned i = 0; i < Productions.size(); i++){
        if (!FirstSet[i]){
            FirstProduction.insert(FirstProduction.end(), Productions[i].begin(), Productions[i].end());
            FirstProduction.push_back("|");
        }
    }
    FirstProduction.pop_back();
    LLGrammarFile.push_back(FirstProduction);
    index = 1;
    for(unsigned i = 0; i < Elemination.size(); i++){
        vector<FactorNode> temp = Elemination[i];
        if (i == 0){
            index = temp.size();
        }
        for (int j = temp.size() - 1; j >= 0; j --){
            vector<std::string> Production;
            Production.push_back("#");
            stringstream ss;
            ss << index;
            string str = ss.str();
            Production.push_back(NonTerminal + str);
            Production.push_back("=");
            vector<int> Nums= temp[j].GetProductions();
            int CheckFirst = 0;
            bool Enter = true;
            for (unsigned k = 0; k < Nums.size(); k++){
                auto ptr = Used.find(Nums[k]);
                if (ptr == Used.end()){
                    Used.emplace(Nums[k], true);
                    Enter = true;
                } else if (ptr != Used.end() && CheckFirst == 0){
                    Enter = true;
                    CheckFirst++;
                } else {
                    Enter = false;
                }
                if (Enter){
                        Enter = false;
                    unsigned CurrentSize = temp[j].GetCommonString().size();;
                    unsigned previousSize;
                    if (j == ((int)temp.size() - 1)){
                        previousSize = (Productions[Nums[k]]).size();
                    } else {
                        previousSize = temp[j + 1].GetCommonString().size();
                    }
                    vector<std::string> res;
                    if (j == ((int)temp.size() - 1)){
                        res = SubVector(CurrentSize, previousSize, Productions[Nums[k]]);
                    } else {
                        res = SubVector(CurrentSize, previousSize, Productions[Nums[k]]);
                    }
                    if (res.size() == 0){
                        res.push_back("\\L");
                    }
                    Production.insert(Production.end(), res.begin(), res.end());
                    if (CheckFirst == 1){
                        CheckFirst++;
                        stringstream ss;
                        ss << index + 1;
                        string str = ss.str();
                        Production.push_back(NonTerminal + str);
                    }
                    Production.push_back("|");
                }
            }
            Production.pop_back();
            LLGrammarFile.push_back(Production);
            Production.clear();
            index--;
        }
        index = index + temp.size() + 1;
    }
}

vector<std::string> ReadFile::SubVector(unsigned Size, unsigned Limit, vector<std::string> test){
    vector<std::string> result;
    for (unsigned i = 0; i < test.size(); i++){
        if (i >= Size && i < Limit){
            result.push_back(test[i]);
        }
    }
    return result;
}
