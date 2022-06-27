//
// Created by Venkat Vellanki on 6/26/22.
//

#ifndef INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H
#define INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H

#include "AVLTree.h"
#include "QueryProcessor.h"
#include "Parser.h"

class SearchEngine {
    void searchForQuery(const char* query, const char* dataset);
};


#endif //INC_22SU_SEARCH_ENGINE_SEARCHENGINE_H
