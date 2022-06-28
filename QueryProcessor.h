//
// Created by Venkat Vellanki on 6/23/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_QUERYPROCESSOR_H
#define INC_22SU_SEARCH_ENGINE_QUERYPROCESSOR_H
#include <iostream>
#include <string>
#include "olestem/stemming/english_stem.h"
#include <algorithm>
#include <sstream>
#include "Parser.h"

class QueryProcessor {
private:

public:
    //process the user input queries and search
    std::string readingQueries(std::string& input); // stem and lowercase queries too
    //stem the user input
    std::string stemQuery(const std::string& input);
    //make the user input lowercase
    static void toLower(std::string & input);
    // void printResults(const char* pathtoarticle);

    void menuSystem();

};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPROCESSOR_H
