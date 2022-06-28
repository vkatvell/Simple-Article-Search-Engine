//
// Created by Venkat Vellanki on 6/26/22.
//

#include "SearchEngine.h"


void SearchEngine::searchForQuery(const char* query, const char* dataset) {

    // creating inverted index for all of the words
    AVLTree<string, string> wordIndex;

    // creating parser object and query processor object
    Parser p;
    QueryProcessor q;

    // calling testFileSystem and getting all the words inserted into wordIndex
    p.testFileSystem(dataset, wordIndex);

    // making char* query into a string
    string queryString = query;

    // creating a string with the stemmed query word
    string searchWord = q.readingQueries(queryString);

    // unordered set to store all the paths for the word
    unordered_set<std::pair<string, int>, pair_hash> paths;

    // setting paths to the set of the unordered set that was returned from
    // the search tree function
    paths.operator=(wordIndex.searchTree(searchWord));

    // printing out all possible paths for the files that the word has appeared in
    for(const auto& files : paths) {
        cout << files.first << ": " << files.second << std::endl;
    }

}
