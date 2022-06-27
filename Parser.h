//
// Created by Noah Henson on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_PARSER_H
#define INC_22SU_SEARCH_ENGINE_PARSER_H
#include <string>
#include <unordered_map>

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
    void testFileSystem(const char* path, AVLTree<string, string> &);
    void testReadJsonFile(AVLTree<string, string> &, const char* fileName);
    //tokenizer
    std::unordered_map<string, int> tokenizer(string&, const string&);
    //stop word reading + removal
    std::unordered_map<string, int> readingStopWords(const char* stopwordsfile);
    void removeStopWords(std::unordered_map<string, int>& source, const std::unordered_map<string, int>& stopwords);
    //stemming
    std::unordered_map<string, int> stemmer(const std::unordered_map<string, int> & source);

};


#endif //INC_22SU_SEARCH_ENGINE_PARSER_H
