//
// Created by Noah Henson on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_PARSER_H
#define INC_22SU_SEARCH_ENGINE_PARSER_H
#include <string>

// for converting string to wstring then back to string
#include <codecvt>
#include "olestem/stemming/english_stem.h"

using std::string;

class Parser {
public:
    //default constructor
    Parser();
    //parse json docs
    void testFileSystem(const char* path);
    void testReadJsonFile(const char* fileName);
    //tokenizer
    std::vector<string> tokenizer(string&, const string&);
    //stop word reading + removal
    std::vector<string> readingStopWords(const char* stopwordsfile);
    std::vector<string> removeStopWords(const std::vector<string>& source, const std::vector<string>& stopwords);
    //stemming
    std::vector<string> stemmer(const std::vector<string> &);

};


#endif //INC_22SU_SEARCH_ENGINE_PARSER_H
