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
#include <vector>
#include "Parser.h"
#include <numeric>
#include <fstream>

// rapidJSON headers
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

class QueryProcessor {
private:

public:

std::vector<std::string> readingQueries(std::string& input); // stem and lowercase queries too

std::string stemQuery(const std::string& input);

static void toLower(std::string & input);
// void printResults(const char* pathtoarticle);

void menuSystem(AVLTree<string, string> &, AVLTree<string, string> &, AVLTree<string, string> &);

std::vector<std::pair<string, int>> eliminateVectorDupes(std::vector<std::pair<string, int>>& pathsVec);

void resultArticles(const string& inputPath);


};


#endif //INC_22SU_SEARCH_ENGINE_QUERYPROCESSOR_H
