#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

static inline bool isQuoteChar(char ch)
{
    return ch == '"' || ch == '\'';
}

string stripComments23BDS1172(const string &src)
{
    string out;
    bool singleLine = false, multiLine = false, insideString = false;
    char quoteType = 0;

    for (size_t idx = 0; idx < src.size(); ++idx)
    {
        char curr = src[idx];
        char nxt = (idx + 1 < src.size()) ? src[idx + 1] : '\0';

        if (!insideString && !singleLine && !multiLine && isQuoteChar(curr))
        {
            insideString = true;
            quoteType = curr;
            out.push_back(curr);
        }
        else if (insideString && curr == quoteType && src[idx - 1] != '\\')
        {
            insideString = false;
            out.push_back(curr);
        }
        else if (!insideString && !singleLine && !multiLine && curr == '/' && nxt == '/')
        {
            singleLine = true;
            ++idx;
        }
        else if (!insideString && !singleLine && !multiLine && curr == '/' && nxt == '*')
        {
            multiLine = true;
            ++idx;
        }
        else if (singleLine && curr == '\n')
        {
            singleLine = false;
            out.push_back('\n');
        }
        else if (multiLine && curr == '*' && nxt == '/')
        {
            multiLine = false;
            ++idx;
        }
        else if (!singleLine && !multiLine)
        {
            out.push_back(curr);
        }
    }
    return out;
}

string removeExtraSpaces(const string &txt)
{
    istringstream reader(txt);
    ostringstream writer;
    string prevNonEmpty, current;

    while (getline(reader, current))
    {
        size_t first = current.find_first_not_of(" \t\r\n");
        size_t last = current.find_last_not_of(" \t\r\n");
        string cleaned = (first == string::npos) ? "" : current.substr(first, last - first + 1);

        if (cleaned.empty() && prevNonEmpty.empty())
            continue;
        writer << cleaned << '\n';
        prevNonEmpty = cleaned;
    }
    return writer.str();
}

int main()
{
    const string sourceFile = "input.txt";
    const string destFile = "output.txt";

    ifstream check(sourceFile);
    if (!check.is_open())
    {
        cerr << "Cannot locate " << sourceFile << "!\n";
        return 1;
    }

    stringstream srcBuffer;
    srcBuffer << check.rdbuf();

    string noComments = stripComments23BDS1172(srcBuffer.str());
    string neatCode = removeExtraSpaces(noComments);

    ofstream output(destFile);
    output << neatCode;

    cout << "Created file: " << destFile << endl;
    return 0;
}
