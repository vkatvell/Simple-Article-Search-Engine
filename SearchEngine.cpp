//
// Created by Venkat Vellanki on 6/26/22.
//

#include "SearchEngine.h"

/**
 * Controller for calling the functions of search engine (query, indexer, parser)
 * @param query
 * @param dataset path to where data is stored
 */
void SearchEngine::searchForQuery(const char* dataset) {
    int count = 0;

    // creating inverted index for all of the words, person, orgs
    AVLTree<string, string> wordIndex;
    AVLTree<string, string> personIndex;
    AVLTree<string, string> orgIndex;

    // creating parser object and query processor object
    Parser p;
    QueryProcessor q;

    // calling testFileSystem and getting all the words inserted into wordIndex
    p.testFileSystem(dataset, wordIndex, personIndex, orgIndex, count);

    q.menuSystem(wordIndex, personIndex, orgIndex);



    // making char* query into a string
//    string queryString = query;

    // creating a string with the stemmed query word
//    string searchWord = q.readingQueries(queryString);



    // unordered set to store all the paths for the word
//    unordered_set<std::pair<string, int>, pair_hash> paths;

    // setting paths to the set of the unordered set that was returned from
    // the search tree function
//    paths.operator=(wordIndex.searchTree(searchWord));

    // printing out all possible paths for the files that the word has appeared in
//    for(const auto& files : paths) {
//        cout << files.first << ": " << files.second << std::endl;
//    }

}
