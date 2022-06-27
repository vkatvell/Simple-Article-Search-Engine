//
// Created by Venkat Vellanki on 6/26/22.
//

#include "SearchEngine.h"


void SearchEngine::searchForQuery(const char* query, const char* dataset) {
    AVLTree<string, string> wordIndex;

    Parser p;
    QueryProcessor q;

    p.testFileSystem(dataset, wordIndex);

    string temp = query;

    string searchWord = q.readingQueries(temp, query);


    unordered_set<string> paths;

    wordIndex.searchTree(searchWord);

}
