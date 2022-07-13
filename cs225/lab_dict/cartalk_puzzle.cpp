 /**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"
#include <iostream> 

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;
    /* Your code goes here! */
    ifstream wordsFile(word_list_fname);
    string word;
    if (wordsFile.is_open()) {
        /* Reads a line from `wordsFile` into `word` until the file ends. */
        while (getline(wordsFile, word)) {
            string s = word;
            if (s.length() >= 3 && d.homophones(s, s.substr(1, s.npos))) {
                if (d.homophones(s, s.substr(0, 1) + s.substr(2, s.npos))) {
                    std::tuple<std::string, std::string, std::string> t(s, s.substr(1, s.npos), s.substr(0, 1) + s.substr(2, s.npos));
                    ret.push_back(t);
                }
            }
        }
    }
    return ret;
}
