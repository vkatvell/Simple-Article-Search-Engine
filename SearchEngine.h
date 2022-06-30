//
// Created by Venkat Vellanki on 6/26/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H
#define INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H

#include "AVLTree.h"
#include "QueryProcessor.h"
#include "Parser.h"

class SearchEngine {
private:

public:
    //Controller for calling the functions of the search engine (query, indexer, parser)
    void searchForQuery(const char* dataset);
};


#endif //INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H
