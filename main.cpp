#include <cstdio>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

string explanationDelimiter = ": ";
string wordDelimiter = ", ";
string translationDelimiter = " / ";

struct WordEntry
{
    string determiner;
    string word;
    string translation;
    string explanation;
};

vector<WordEntry> words;

void parseEntry(string line)
{
    size_t substringEndIndex = line.find(explanationDelimiter);
    string explanation = line.substr(0, substringEndIndex);
    line.erase(0, substringEndIndex + explanationDelimiter.length());
    while((substringEndIndex = line.find(wordDelimiter)) != string::npos)
    {
        string word = line.substr(0, substringEndIndex);
        size_t determinerIndex = word.find(" "); // Just get the first word, i.e. "der"
        string determiner = word.substr(0, determinerIndex);
        size_t translationIndex = word.find(translationDelimiter);
        string translation = word.substr(translationIndex + translationDelimiter.length(), word.length());
        word.erase(translationIndex, word.length());
        word.erase(0, determinerIndex + 1);
        line.erase(0, substringEndIndex + wordDelimiter.length());
        words.push_back(WordEntry{determiner, word, translation, explanation});
        printf("%s|\n", word.c_str());
        printf("%s|\n", determiner.c_str());
        printf("%s|\n", translation.c_str());
    }
    printf("%s\n", explanation.c_str());
}

int main(int argc, char** argv)
{
    printf("German Grammar Exercises Version 0.1\n");
    ifstream germanWordList{"GermanWordList.txt"};
    if(germanWordList.is_open())
    {
        string line;
        while(getline(germanWordList, line))
        {
            parseEntry(line);
        }
    }
    return 0;
}
