#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <unordered_set>
#include <vector>

using namespace std;

const unordered_set<string> reservedWords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "bool",
    "namespace", "class", "public", "private", "protected", "true", "false", "using"};

const unordered_set<string> operatorSymbols = {
    ";", ",", ".", "(", ")", "{", "}", "[", "]",
    "=", "+", "-", "*", "/", "<", ">", "!", "&", "|", ":",
    "==", "<=", ">=", "!=", "++", "--", "+=", "-=", "*=", "/="};

bool isLiteralToken(const string &tok)
{
    static const regex numberPattern(R"(^\d+(\.\d+)?$)");
    static const regex charPattern(R"(^'.'$)");
    static const regex stringPattern(R"(^".*"$)");
    return regex_match(tok, numberPattern) ||
           regex_match(tok, charPattern) ||
           regex_match(tok, stringPattern);
}

bool isValidIdentifier(const string &tok)
{
    static const regex identPattern(R"(^[A-Za-z_]\w*$)");
    return regex_match(tok, identPattern) && !reservedWords.count(tok);
}

vector<string> splitTokens(const string &text)
{
    vector<string> result;
    static const regex tokenRegex(
        R"((==|<=|>=|!=|\+\+|--|\+=|-=|\*=|/=|[;,\.\(\)\{\}\[\]=+\*/<>!&|:-]|\w+|".*?"|'.'))");

    for (auto it = sregex_iterator(text.begin(), text.end(), tokenRegex);
         it != sregex_iterator(); ++it)
    {
        result.push_back(it->str());
    }
    return result;
}

int main()
{
    ifstream srcFile("input_23BDS1172.txt");
    ofstream outFile("output_23BDS1172.txt");

    if (!srcFile.is_open())
    {
        cerr << "Error: Could not open source file.\n";
        return 1;
    }

    unordered_set<string> detectedKeywords, detectedLiterals, detectedIdentifiers, detectedOperators;
    string line;

    while (getline(srcFile, line))
    {
        // Strip single-line comments
        line = regex_replace(line, regex(R"(//.*)"), "");

        // Tokenize line
        for (const string &tok : splitTokens(line))
        {
            if (reservedWords.count(tok))
            {
                detectedKeywords.insert(tok);
            }
            else if (operatorSymbols.count(tok))
            {
                detectedOperators.insert(tok);
            }
            else if (isLiteralToken(tok))
            {
                detectedLiterals.insert(tok);
            }
            else if (isValidIdentifier(tok))
            {
                detectedIdentifiers.insert(tok);
            }
        }
    }
    outFile << "=== Lexical Analysis Result ===\n\n";
    outFile << "Keywords (" << detectedKeywords.size() << "):\n";
    for (const auto &kw : detectedKeywords)
        outFile << "  - " << kw << "\n";

    outFile << "\nLiterals (" << detectedLiterals.size() << "):\n";
    for (const auto &lit : detectedLiterals)
        outFile << "  - " << lit << "\n";

    outFile << "\nIdentifiers (" << detectedIdentifiers.size() << "):\n";
    for (const auto &id : detectedIdentifiers)
        outFile << "  - " << id << "\n";

    outFile << "\nOperators/Punctuations (" << detectedOperators.size() << "):\n";
    for (const auto &op : detectedOperators)
        outFile << "  - " << op << "\n";

    cout << "Lexical analysis completed. Results in 'output_23BDS1172.txt'.\n";
    return 0;
}
