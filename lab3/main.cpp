#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

struct SymbolEntry
{
    int id;
    string name;
    string datatype;
    string assignedValue;
};

struct ErrorEntry
{
    string name;
    string message;
};

int main()
{
    ifstream inputFile("lab3_23BDS1172.txt");
    ofstream symFile("symbol_table.txt");
    ofstream errFile("error_table.txt");

    if (!inputFile)
    {
        cerr << "Error: lab3.txt not found!\n";
        return 1;
    }

    unordered_set<string> seenIdentifiers;
    vector<SymbolEntry> symbols;
    vector<ErrorEntry> errors;

    string currentLine;
    int symbolIndex = 1;

    while (getline(inputFile, currentLine))
    {
        if (currentLine.find_first_not_of(" \t\r\n") == string::npos)
            continue;

        istringstream parser(currentLine);
        string type, name, value;

        if (!(parser >> type >> name >> value))
        {
            errors.push_back({name, "Malformed declaration"});
            continue;
        }

        if (seenIdentifiers.count(name))
        {
            errors.push_back({name, "Identifier already declared"});
            continue;
        }

        seenIdentifiers.insert(name);
        symbols.push_back({symbolIndex++, name, type, value});
    }

    symFile << "Index\tIdentifier\tType\tValue\n";
    for (auto &entry : symbols)
    {
        symFile << entry.id << "\t" << entry.name << "\t"
                << entry.datatype << "\t" << entry.assignedValue << "\n";
    }

    errFile << "Identifier\tReason\n";
    for (auto &entry : errors)
    {
        errFile << entry.name << "\t" << entry.message << "\n";
    }

    cout << "Symbol table and error table have been created successfully.\n";
    return 0;
}
