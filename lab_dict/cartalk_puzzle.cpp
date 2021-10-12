/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

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
	std::tuple<std::string, std::string, std::string> tuple_;
	ifstream wordsFile(word_list_fname);
	string str_;
	if(wordsFile.is_open()) 
    {
		while(getline(wordsFile, str_)) 
        {
			string w1 = str_.substr(1);
			string w2 = str_[0] + str_.substr(2);
			if(d.homophones(str_, w1) && d.homophones(str_, w2) && d.homophones(w1, w2)) 
            {
				tuple_ = make_tuple(str_, w1, w2);
				ret.push_back(tuple_);
			}
		}
	}
    return ret;
}
