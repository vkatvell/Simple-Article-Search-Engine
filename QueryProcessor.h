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

class QueryProcessor {
private:

public:

std::string readingQueries(std::string& input); // stem and lowercase queries too

std::string stemQuery(const std::string& input);

static void toLower(std::string & input);
// void printResults(const char* pathtoarticle);


};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPROCESSOR_H
