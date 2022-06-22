//
// Created by Noah Henson on 6/22/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_PARSER_H
#define INC_22SU_SEARCH_ENGINE_PARSER_H
#include <string>

using std::string;

class Parser {
public:
    //default constructor
    Parser();
    //parse json docs
    void testFileSystem(const char* path);
    void testReadJsonFile(const char* fileName);
    //tokenizer
    std::vector<string> tokenizer(const string&, const string&);
    //stop word removal + stemming

};


#endif //INC_22SU_SEARCH_ENGINE_PARSER_H
