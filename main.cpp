#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>

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
        // printf("%s|\n", word.c_str());
        // printf("%s|\n", determiner.c_str());
        // printf("%s|\n", translation.c_str());
    }
    // printf("%s\n", explanation.c_str());
}

int main(int argc, char** argv)
{
    printf("German Grammar Exercises Version 0.1\n");

    srand(time(NULL));

    ifstream germanWordList{"GermanWordList.txt"};
    if(germanWordList.is_open())
    {
        string line;
        while(getline(germanWordList, line))
        {
            parseEntry(line);
        }
    }
    if (words.size() == 0)
    {
        printf("Could not parse GermanWordList.txt. Exiting program...\n");
        return 0;
    }
    int questionNum = 1;
    int score = 0;
    while(true)
    {
        size_t randIndex = rand() % words.size();
        WordEntry wordEntry = words.at(randIndex);
        printf("\nQuestion %d:\n___ %s.\nEnter 1 for der, 2 for die, 3 for das, q to Quit: ", questionNum, wordEntry.word.c_str());
        string response;
        getline(cin, response);
        if(response == "q")
        {
            return 0;
        }
        else
        {
            string responseDeterminer;
            if(response == "1") responseDeterminer = "der";
            else if(response == "2") responseDeterminer = "die";
            else if(response == "3") responseDeterminer = "das";
            if(responseDeterminer == wordEntry.determiner)
            {
                printf("!! Correct !! %s %s.\nEnglish: %s.\nRule: %s\n", wordEntry.determiner.c_str(), wordEntry.word.c_str(), wordEntry.translation.c_str(), wordEntry.explanation.c_str());
                score++;
            }
            else
            {
                printf("!!! Incorrect !!! %s %s.\nEnglish: %s.\nRule: %s\n", wordEntry.determiner.c_str(), wordEntry.word.c_str(), wordEntry.translation.c_str(), wordEntry.explanation.c_str());
            }
            printf("Score: %d/%d\n", score, questionNum);
            questionNum++;
        }
    }
    return 0;
}
