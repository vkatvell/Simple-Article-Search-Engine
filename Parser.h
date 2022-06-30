//
// Created by Noah Henson on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_PARSER_H
#define INC_22SU_SEARCH_ENGINE_PARSER_H
#include <string>
#include <unordered_map>
#include <map>

// for converting string to wstring then back to string
#include <codecvt>
#include "olestem/stemming/english_stem.h"
#include "AVLTree.h"

using std::string;

class Parser {
public:
    //default constructor
    Parser();
    //parse json docs
    void testFileSystem(const char* path, AVLTree<string, string> &, AVLTree<string, string> &, AVLTree<string, string> &, int&, std::unordered_map<string, int>&);
    static void testReadJsonFile(AVLTree<string, string> &, AVLTree<string, string> &, AVLTree<string, string> &, const char* fileName,const std::unordered_map<string, int>& stopWords, int &counter, std::unordered_map<string, int>&);
    //tokenizer
    static std::unordered_map<string, int> tokenizer(string&, const string&);
    //stop word reading + removal
    static std::unordered_map<string, int> readingStopWords(const char* stopwordsfile);
    static void removeStopWords(std::unordered_map<string, int>& source, const std::unordered_map<string, int>& stopwords);
    //stemming
    static std::unordered_map<string, int> stemmer(const std::unordered_map<string, int> & source);

};


#endif //INC_22SU_SEARCH_ENGINE_PARSER_H
