//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"
#include <chrono>
#include <unordered_map>
#include <map>

using namespace std::chrono;
using std::string;
using std::cin;
using std::cout;
using std::endl;

struct comparator {
    bool operator()(std::pair<string, int> &a, std::pair<string, int> &b) {
//        if(b.second < a.second) {
        return a.first < b.first;
//        }
//        else {
//            return b.first < a.first;
//        }
    }
};


std::vector<std::string> QueryProcessor::readingQueries(string &input) {
    string andStr = "and";
    string orStr = "or";
    string notStr = "not";
    string orgStr = "org";
    string persStr = "person";

    bool isAND = false;
    bool isOR = false;
    bool hasNOT = false;
    bool hasORG = false;
    bool hasPERSON = false;

    std::vector<string> ANDwordsToSearch;
    std::vector<string> ORwordsToSearch;
    std::vector<string> wordsToSearch;
    std::vector<string> empty;

//ANDwordsToSearch.push_back(andStr);
//ORwordsToSearch.push_back(orStr);

    if (input.substr(0, 3) == "and") {
        isAND = true;
    } else if (input.substr(0, 2) == "or") {
        isOR = true;
    } else {
        isAND = false;
        isOR = false;
    }

    std::stringstream query(input);

    string indWord;

    string afterNot;
    string afterOrg;
    string afterPerson;

    if (!isAND && !isOR) {
        while (query >> indWord) {
            if (indWord == notStr) {
                hasNOT = true;
                wordsToSearch.push_back(notStr);
                query >> afterNot;
                toLower(afterNot);
                wordsToSearch.push_back(afterNot); // string with word after NOT
            } else if (indWord == orgStr) {
                hasORG = true;
                wordsToSearch.push_back(orgStr);
                query >> afterOrg;
                toLower(afterOrg);
                wordsToSearch.push_back(afterOrg); // string with word after ORG
            } else if (indWord == persStr) {
                hasPERSON = true;
                wordsToSearch.push_back(persStr);
                query >> afterPerson;
                toLower(afterPerson);
                wordsToSearch.push_back(afterPerson); // string with word after PERSON
            } else {
                toLower(indWord);
                string stemmedQ = stemQuery(indWord);
                wordsToSearch.push_back(stemmedQ);
            }
        }
        return wordsToSearch;
    } else if (isAND && !isOR) {
        while (query >> indWord) {
            if (indWord == notStr) {
                hasNOT = true;
                ANDwordsToSearch.push_back(notStr);
                query >> afterNot;
                toLower(afterNot);
                ANDwordsToSearch.push_back(afterNot);
                // string with word after NOT
            } else if (indWord == orgStr) {
                hasORG = true;
                ANDwordsToSearch.push_back(orgStr);
                query >> afterOrg;
                toLower(afterOrg);
                ANDwordsToSearch.push_back(afterOrg);
                // string with word after ORG
            } else if (indWord == persStr) {
                hasPERSON = true;
                ANDwordsToSearch.push_back(persStr);
                query >> afterPerson;
                toLower(afterPerson);
                ANDwordsToSearch.push_back(afterPerson);
                // string with word after PERSON
            } else {
                query >> indWord;
                toLower(indWord);
                string stemmedQ = stemQuery(indWord);
                ANDwordsToSearch.push_back(indWord);
            }
        }
        return ANDwordsToSearch;
    } else if (isOR && !isAND) {
        while (query >> indWord) {
            if (indWord == notStr) {
                hasNOT = true;
                ORwordsToSearch.push_back(notStr);
                query >> afterNot;
                toLower(afterNot);
                ORwordsToSearch.push_back(afterNot);
                // string with word after NOT
            } else if (indWord == orgStr) {
                hasORG = true;
                ORwordsToSearch.push_back(orgStr);
                query >> afterOrg;
                toLower(afterOrg);
                ORwordsToSearch.push_back(afterOrg);
                // string with word after ORG
            } else if (indWord == persStr) {
                hasPERSON = true;
                ORwordsToSearch.push_back(persStr);
                query >> afterPerson;
                toLower(afterPerson);
                ORwordsToSearch.push_back(afterPerson);
                // string with word after PERSON
            } else {
//                    query >> indWord;
                toLower(indWord);
                string stemmedQ = stemQuery(indWord);
                ORwordsToSearch.push_back(stemmedQ);
            }
        }
        return ORwordsToSearch;
    } else {
        return empty;
    }
}


std::string QueryProcessor::stemQuery(const std::string &input) {

    // converting string to wstring
    std::wstringstream cls;
    cls << input.c_str();
    std::wstring total = cls.str();

    // creating stemming object
    stemming::english_stem<> Stem;

    // stemming the wstring
    Stem(total);

    // converting the wstring back into a string
    std::string str(total.begin(), total.end());

    return str;
}

void QueryProcessor::toLower(string &input) {
    std::transform(input.begin(), input.end(), input.begin(),
                   [](unsigned char c) { return std::tolower(c); });
}

//swaps the keys and values of a map
std::multimap<int, string> swapValueAndKey(std::unordered_map<string, int> const& map) {
    std::multimap<int, string> multiMap;
    //read through unordered map and push back values and keys
    for(auto const& p : map) {
        multiMap.insert(make_pair(p.second, p.first));
    }

    return multiMap;
}



void QueryProcessor::menuSystem(AVLTree<string, string> &wordIndex, AVLTree<string, string> &person,
                                AVLTree<string, string> &orgs, std::unordered_map<string, int>& allWords) {
    // parse dataset first before calling this function
    cout << "Welcome to Noah and Venkat's Financial Article Search Engine" << endl;

    bool continue_running = true;

    // printing menu options
    while (continue_running) {
        cout << "a. Parse a new dataset" << endl;
        cout << "b. Enter a query" << endl;
        cout << "c. Display statistics" << endl;
        cout << "d. Display top 25 most frequent terms" << endl;
        cout << "e. Exit Search Engine program" << endl;

        // reading in user input for menu value
        char input;
        cin >> input;

        // error handling for invalid initial menu input
        while (true) {
            if (input != 'A' && input != 'a' && input != 'b' && input != 'B' && input != 'c' && input != 'C' &&
                    input != 'd' && input != 'D' && input != 'e' && input != 'E') {
                cout << "Invalid input. Please try again." << endl;
                cin >> input;
                continue;
            } else {
                break;
            }
        }

        // exit search menu option
        if (input == 'E' || input == 'e') {
            continue_running = false;
        } // end exit search menu option

        // ending program if user selects exit search menu option
        if (!continue_running) {
            cout << "Thank you for searching. Goodbye..." << endl;
            break;
        }

        // option a. parsing a new dataset
        if (input == 'A' || input == 'a') {
            // clear wordIndex, peopleIndex, orgIndex
            AVLTree<string, string> newWordIndex;
            AVLTree<string, string> newPersonIndex;
            AVLTree<string, string> newOrgIndex;

            Parser p;

            int newCount;

            // parse new dataset
            cin.ignore();
            cout << "Enter path to a new dataset to parse: ";
            string newPath;

            cin >> newPath;

            // time spent parsing new dataset
            auto start = high_resolution_clock::now();

            // call parser test file system function and pass in new empty avl trees for
            // three indexes
            p.testFileSystem(newPath.c_str(), newWordIndex, newPersonIndex, newOrgIndex, newCount, allWords);

            auto stop = high_resolution_clock::now();
            auto timeToExecMilli = duration_cast<milliseconds>(stop - start);
            auto timeToExecSec = duration_cast<seconds>(stop - start);
            auto timeToExecMin = duration_cast<minutes>(stop - start);

            // printing time spent parsing
            cout << "Done parsing new dataset. Time to parse: " << timeToExecMin.count() << " min "
                 << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                 << " ms. \nReturning you to main menu..." << endl;

            // continue and reprint menu
            menuSystem(newWordIndex, newPersonIndex, newOrgIndex, allWords);
            break;
        } // end menu option a


        // menu option b for entering a query to search
        if (input == 'B' || input == 'b') {

            cin.ignore();
            cout << "Enter a query: ";
            string query;

            getline(cin, query);
            // call readingQueries function and starting timer
            auto queryStart = high_resolution_clock::now();
            std::vector<string> wordsToSearch = readingQueries(query);

            // setting initial query case booleans to false
            bool isAND = false;
            bool isOR = false;
            bool hasNOT = false;
            bool hasPERSON = false;
            bool hasORG = false;

            // first word of the vector is either AND, OR, or neither
            // so setting booleans for each case
            if (wordsToSearch[0] == "and") {
                isAND = true;
                isOR = false;
            } else if (wordsToSearch[0] == "or") {
                isOR = true;
                isAND = false;
            } else {
                isAND = false;
                isOR = false;
            }

            // doing set operations if vector is AND case INTERSECTION
            if (isAND && !isOR) {

                // afterNot is the word that appears after NOT operator
                string afterNot;
                // afterPerson is the person that appears after PERSON operator
                string afterPerson;
                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                // iterating through the vector of words from query to find NOT
                // then storing the word  that appears after NOT in afterNot
                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if (itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }

                // vector of string, int pair to store all paths and frequencies for afterNot
                std::vector<std::pair<string, int>> notPath;

                // checking if query has a NOT
                if (hasNOT) {

                    // searching wordIndex AVL tree for the word and returning all of its paths
                    // into a new unordered set notPaths
                    unordered_set<std::pair<string, int>, pair_hash> notPaths;
                    notPaths.operator=(wordIndex.searchTree(afterNot));

                    // pushing back all the paths from notPaths into the vector notPath
                    for (const auto &file: notPaths) {
                        notPath.push_back(std::make_pair(file.first, file.second));
                    }

                    // sorting vector notPath for set operations
                    std::sort(notPath.begin(), notPath.end());
                }

                // iterating through the vector of words from query to find PERSON
                // then storing the word that appears after PERSON in afterPerson
                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if (itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }

                // searching wordIndex AVL tree for the person word and returning all of its paths
                // into a new unordered set personPaths
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));

                // vector of string, int pair to store all paths and frequencies for afterPerson
                std::vector<std::pair<string, int>> personPath;

                // pushing back all the paths from personPaths into the vector personPath
                for (const auto &file: personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }

                // sorting vector notPath for set operations
                std::sort(personPath.begin(), personPath.end());

                // iterating through the vector of words from query to find ORG
                // then storing the word that appears after ORG in afterOrg
                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if (itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }

                // searching wordIndex AVL tree for the org word and returning all of its paths
                // into a new unordered set orgPaths
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));

                // vector of string, int pair to store all paths and frequencies for afterOrg
                std::vector<std::pair<string, int>> orgPath;

                // pushing back all the paths from orgPaths into the vector orgPath
                for (const auto &file: orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }

                // sorting vector notPath for set operations
                std::sort(orgPath.begin(), orgPath.end());

                // vector for eliminated duplicate strings between personPath vector and orgPath vector
                std::vector<std::pair<string, int>> cleanedVec;

                // intersection of person and org paths and cases
                if (hasPERSON && hasORG) {
                    std::vector<std::pair<string, int>> personOrgs;
                    std::set_intersection(personPath.begin(), personPath.end(),
                                          orgPath.begin(), orgPath.end(),
                                          std::back_inserter(personOrgs), comparator{});

                    cleanedVec = eliminateVectorDupes(personOrgs);
                } else if (hasPERSON && !hasORG) {
                    cleanedVec = personPath;
                } else if (hasORG && !hasPERSON) {
                    cleanedVec = orgPath;
                } else {
                    hasPERSON = false;
                    hasORG = false;
                }

                // sorting cleanedVec for set operations
                std::sort(cleanedVec.begin(), cleanedVec.end());

                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int m = 2;

                // paths holds all paths and frequency for the first word in the query thats not AND or OR
                unordered_set<std::pair<string, int>, pair_hash> paths;
                paths.operator=(wordIndex.searchTree(wordsToSearch[1]));
                // vector for all of the paths from the first word
                std::vector<std::pair<string, int>> firstWordPaths;

                // pushing back all paths from unordered set into the vector
                for (const auto &files: paths) {
                    firstWordPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                }

                // sorting the vector
                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                // vector for all words after AND and first word in search query
                std::vector<std::pair<string, int>> whileLoopPaths;

                // if there is no NOT, ORG, or PERSON in query it will only perform intersection
                // with the firstWordPaths and words from whileLoopPaths
                if (!hasNOT && !hasORG && !hasPERSON) {
                    while (m < wordsToSearch.size()) {
                        // set intersection using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                } else {    // else case means that the query has one of NOT, PERSON, or org
                    while (wordsToSearch[m] != "not" && wordsToSearch[m] != "person" && wordsToSearch[m] != "org") {
                        // extra test case to break the while loop if query has PERSON, NOT, or org to make sure
                        if (!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set intersection using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                }

                // sorting all paths in teh whileLoopPaths vector
                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                // wordPaths performs set intersection between the paths in firstWordPaths and whileLoopPaths
                std::vector<std::pair<string, int>> wordPaths;
                std::set_intersection(firstWordPaths.begin(), firstWordPaths.end(),
                                      whileLoopPaths.begin(), whileLoopPaths.end(), std::back_inserter(wordPaths),
                                      comparator{});

                // removing duplicates in wordPaths and storing in a cleaned vector
                auto cleanedWordPaths = eliminateVectorDupes(wordPaths);

                // if the query has PERSON or ORG, performing intersection with the personOrg cleanedVec
                // and cleanedWordPaths
                if (hasPERSON || hasORG) {
                    std::vector<std::pair<string, int>> intersectPaths;
                    std::set_intersection(cleanedWordPaths.begin(), cleanedWordPaths.end(),
                                          cleanedVec.begin(), cleanedVec.end(),
                                          std::back_inserter(intersectPaths), comparator{});

                    // cleaning all intersected paths to ensure no duplicates after intersection
                    auto cleaningIntersectPaths = eliminateVectorDupes(intersectPaths);

                    // declaring removedDupes for results to be returned
                    std::vector<std::pair<string, int>> removedDupes;

                    // if the query has NOT, time to pereform set difference for the NOT paths
                    if (hasNOT) {
                        std::vector<std::pair<string, int>> NOTsubtracted;

                        // performing set difference and storing the result in NOTsubtracted
                        std::set_difference(cleaningIntersectPaths.begin(), cleaningIntersectPaths.end(),
                                            notPath.begin(), notPath.end(),
                                            std::back_inserter(NOTsubtracted), comparator{});

                        // removing duplicates in the NOTsubtracted and returning in removedDupes
                        removedDupes = eliminateVectorDupes(NOTsubtracted);
                    } else { // if the query does not have NOT just return the intersectedPaths in removedDupes
                        removedDupes = eliminateVectorDupes(cleaningIntersectPaths);
                    }

                    // sorting removedDupes based on second element (term frequency) for relevancy ranking
                    std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                        return right.second < left.second;
                    });

                    // if there are no search results then return message for no search results
                    if (removedDupes.size() < 1) {
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;

                        cout << "Uh oh. There are no search results for that query.\n"
                             << "Try another query." << endl;
                    } else if (removedDupes.size() > 15) {      // if there are more than 15 results than print top 15
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;
                        cout << "The top 15 results are: " << endl;
                        for (int i = 0; i < 15; ++i) {
                            cout << letters[i] << " - ";
                            resultArticles(removedDupes[i].first);
                        }
                        cout << "\nEnter the letter corresponding to the article: ";
                        string letterInput;
                        cin >> letterInput;

                        for (int i = 0; i < letters.size(); i++) {
                            if (letterInput == letters[i]) {
                                accessedArticle(removedDupes[i].first);
                            }
                        }
                    } else {    // if there are less than 15 results and greater or equal to 1 then print all results
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;
                        cout << "The results that contain all search terms are: " << endl;
                        int j = 0;
                        for (const auto &path: removedDupes) {
                            cout << letters[j] << " - ";
                            resultArticles(path.first);
                            cout << endl;
                            j++;
                        }
                        cout << "\nEnter the letter corresponding to the article: ";
                        string letterInput;
                        cin >> letterInput;

                        for (int i = 0; i < letters.size(); i++) {
                            if (letterInput == letters[i]) {
                                accessedArticle(removedDupes[i].first);
                            }
                        }
                    }
                } else {        // if the query does not have PERSON or ORG then go through test cases above with NOT
                    std::vector<std::pair<string, int>> removedDupes;
                    if (hasNOT) {
                        std::vector<std::pair<string, int>> NOTsubtracted;

                        std::set_difference(cleanedWordPaths.begin(), cleanedWordPaths.end(), notPath.begin(),
                                            notPath.end(),
                                            std::back_inserter(NOTsubtracted), comparator{});

                        removedDupes = eliminateVectorDupes(NOTsubtracted);
                    } else {
                        removedDupes = eliminateVectorDupes(cleanedWordPaths);
                    }

                    std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                        return right.second < left.second;
                    });

                    if (removedDupes.size() < 1) {
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;
                        cout << "Uh oh. There are no search results for that query.\n"
                             << "Try another query." << endl;
                    } else if (removedDupes.size() > 15) {
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;
                        cout << "The top 15 results are: " << endl;
                        for (int i = 0; i < 15; ++i) {
                            cout << letters[i] << " - ";
                            resultArticles(removedDupes[i].first);
                            cout << endl;
                        }
                        cout << "\nEnter the letter corresponding to the article: ";
                        string letterInput;
                        cin >> letterInput;

                        for (int i = 0; i < letters.size(); i++) {
                            if (letterInput == letters[i]) {
                                accessedArticle(removedDupes[i].first);
                            }
                        }
                    } else {
                        auto queryStop = high_resolution_clock::now();
                        auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                        auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                        auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                        cout << "\nThe time to search was: " << timeToExecMin.count()
                             << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                             << " ms." << std::endl;
                        cout << endl;
                        cout << "The results that contain all search terms are: " << endl;
                        int j = 0;
                        for (const auto &path: removedDupes) {
                            cout << letters[j] << " - ";
                            resultArticles(path.first);
                            cout << endl;
                            j++;
                        }
                        cout << "\nEnter the letter corresponding to the article: ";
                        string letterInput;
                        cin >> letterInput;

                        for (int i = 0; i < letters.size(); i++) {
                            if (letterInput == letters[i]) {
                                accessedArticle(removedDupes[i].first);
                            }
                        }
                    }
                }

                // setting the booleans to false for next search
                hasORG = false;
                hasPERSON = false;
                hasNOT = false;

            }

            // doing operations if set operation is OR case UNION
            else if (isOR && !isAND) {
                // afterNot is the word that appears after NOT operator
                string afterNot;
                // afterPerson is the person that appears after PERSON operator
                string afterPerson;
                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                // getting the words after NOT, PERSON, and ORG
                // and creating vector of paths for the words after each
                // operator if they are in query
                // also sorting and cleaning the vectors to perform set union operation
                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if (itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }

                std::vector<std::pair<string, int>> notPath;
                if (hasNOT) {
                    unordered_set<std::pair<string, int>, pair_hash> notPaths;
                    notPaths.operator=(wordIndex.searchTree(afterNot));
                    for (const auto &file: notPaths) {
                        notPath.push_back(std::make_pair(file.first, file.second));
                    }
                    std::sort(notPath.begin(), notPath.end());
                }

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if (itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));

                std::vector<std::pair<string, int>> personPath;
                for (const auto &file: personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(personPath.begin(), personPath.end());

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if (itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));

                std::vector<std::pair<string, int>> orgPath;
                for (const auto &file: orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(orgPath.begin(), orgPath.end());


                // union of person and org paths
                std::vector<std::pair<string, int>> personOrgs(500000); //TODO change the size aspect of this
                auto poItr = std::set_union(personPath.begin(), personPath.end(),
                                            orgPath.begin(), orgPath.end(), personOrgs.begin());

                personOrgs.resize(poItr - personOrgs.begin());

                auto cleanedVec = eliminateVectorDupes(personOrgs);


                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int m = 2;

                // getting first word in query after OR
                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[1]));

                // vector for the first word's paths
                std::vector<std::pair<string, int>> firstWordPaths;
                for (const auto &files: paths) {
                    firstWordPaths.emplace_back(files.first, files.second);
                }

                // sorting that vector of first word's paths
                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                // vector for all the words' paths that appear after first word
                // and before NOT, PERSON, or ORG
                std::vector<std::pair<string, int>> whileLoopPaths;

                // if NOT ORG PERSON not in query then just perform union
                // for first word paths and the paths of all words in while loop paths
                if (!hasNOT && !hasORG && !hasPERSON) {
                    while (m < wordsToSearch.size()) {
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                } else {    // if the word has PERSON ORG or NOT
                    while (wordsToSearch[m] != "not" && wordsToSearch[m] != "person" && wordsToSearch[m] != "org") {
                        if (!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                }

                // sorting the while loop paths for set operations
                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                // set union for all word paths with first word paths and while loop paths
                std::vector<std::pair<string, int>> wordPaths;

                std::set_union(firstWordPaths.begin(), firstWordPaths.end(), whileLoopPaths.begin(),
                               whileLoopPaths.end(), std::back_inserter(wordPaths), comparator{});

                // removing duplicates from the unionized vector of wordPaths
                auto cleaningWordPaths = eliminateVectorDupes(wordPaths);

                std::vector<std::pair<string, int>> unionPaths;

                // unionizing the cleaned vector paths
                std::set_union(cleaningWordPaths.begin(), cleaningWordPaths.end(), cleanedVec.begin(),
                               cleanedVec.end(), std::back_inserter(unionPaths), comparator{});

                // cleaning the unionized paths again
                auto cleaningUnionPaths = eliminateVectorDupes(unionPaths);

                // handling NOT case with set difference
                std::vector<std::pair<string, int>> removedDupes;
                if (hasNOT) {
                    std::vector<std::pair<string, int>> NOTsubtracted;

                    std::set_difference(cleaningUnionPaths.begin(), cleaningUnionPaths.end(), notPath.begin(),
                                        notPath.end(),
                                        std::back_inserter(NOTsubtracted), comparator{});

                    removedDupes = eliminateVectorDupes(NOTsubtracted);
                } else {
                    removedDupes = eliminateVectorDupes(cleaningUnionPaths);
                }


                std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                    return right.second < left.second;
                });

                // printing of search results
                if (removedDupes.size() < 1) {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "Uh oh. There are no search results for that query.\n"
                         << "Try another query." << endl;
                } else if (removedDupes.size() > 15) {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "The top 15 results are: " << endl;
                    for (int i = 0; i < 15; ++i) {
                        cout << letters[i] << " - ";
                        resultArticles(removedDupes[i].first);
                        cout << endl;
                    }
                    cout << "\nEnter the letter corresponding to the article: ";
                    string letterInput;
                    cin >> letterInput;

                    for (int i = 0; i < letters.size(); i++) {
                        if (letterInput == letters[i]) {
                            accessedArticle(removedDupes[i].first);
                        }
                    }
                } else {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "The results that contain one or more search terms are: " << endl;
                    int j = 0;
                    for (const auto &path: removedDupes) {
                        cout << letters[j] << " - ";
                        resultArticles(path.first);
                        cout << endl;
                        j++;
                    }
                    cout << "\nEnter the letter corresponding to the article: ";
                    string letterInput;
                    cin >> letterInput;

                    for (int i = 0; i < letters.size(); i++) {
                        if (letterInput == letters[i]) {
                            accessedArticle(removedDupes[i].first);
                        }
                    }
                }
            }

            // neither AND nor OR case
            if (!isAND && !isOR) {
                // afterNot is the word that appears after NOT operator
                string afterNot;
                // afterPerson is the person that appears after PERSON operator
                string afterPerson;
                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                hasNOT = false;
                hasPERSON = false;
                hasORG = false;

                // finding the NOT ORG PERSON cases in the search query and storing
                // for set difference operation later
                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if (itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }
                std::vector<std::pair<string, int>> notPath;
                if (hasNOT) {
                    unordered_set<std::pair<string, int>, pair_hash> notPaths;
                    notPaths.operator=(wordIndex.searchTree(afterNot));
                    for (const auto &file: notPaths) {
                        notPath.push_back(std::make_pair(file.first, file.second));
                    }
                    std::sort(notPath.begin(), notPath.end());
                }

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if (itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));

                std::vector<std::pair<string, int>> personPath;
                for (const auto &file: personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(personPath.begin(), personPath.end());

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if (itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));

                std::vector<std::pair<string, int>> orgPath;
                for (const auto &file: orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(orgPath.begin(), orgPath.end());

                // union of person and org paths
                std::vector<std::pair<string, int>> personOrgs;
                std::set_union(personPath.begin(), personPath.end(), orgPath.begin(),
                               orgPath.end(), std::back_inserter(personOrgs), comparator{});

                auto cleanedVec = eliminateVectorDupes(personOrgs);

                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[0]));

                std::vector<std::pair<string, int>> firstWordPaths;

                for (const auto &files: paths) {
                    firstWordPaths.emplace_back(files.first, files.second);
                }

                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                std::vector<std::pair<string, int>> whileLoopPaths;

                int m = 1;

                // if the query does not have NOT ORG or PERSON performing union for just the word
                if (!hasNOT && !hasORG && !hasPERSON) {
                    while (m < wordsToSearch.size()) {
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                } else {
                    while (wordsToSearch[m] != "not" && wordsToSearch[m] != "person" && wordsToSearch[m] != "org") {
                        if (!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[m]));

                        for (const auto &files: temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        m++;
                    }
                }

                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                std::vector<std::pair<string, int>> wordPaths;
                std::set_union(firstWordPaths.begin(), firstWordPaths.end(),
                               whileLoopPaths.begin(), whileLoopPaths.end(), std::back_inserter(wordPaths),
                               comparator{});

                auto cleaningWordPaths = eliminateVectorDupes(wordPaths);

                std::vector<std::pair<string, int>> unionPaths;
                std::set_union(cleaningWordPaths.begin(), cleaningWordPaths.end(),
                               cleanedVec.begin(), cleanedVec.end(), std::back_inserter(unionPaths), comparator{});

                auto cleaningUnionPaths = eliminateVectorDupes(unionPaths);

                std::vector<std::pair<string, int>> removedDupes;

                // checking and handling NOT cases
                if (hasNOT) {
                    std::vector<std::pair<string, int>> NOTsubtracted;

                    std::set_difference(cleaningUnionPaths.begin(), cleaningUnionPaths.end(), notPath.begin(),
                                        notPath.end(),
                                        std::back_inserter(NOTsubtracted), comparator{});

                    removedDupes = eliminateVectorDupes(NOTsubtracted);
                } else {
                    removedDupes = eliminateVectorDupes(cleaningUnionPaths);
                }


                std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                    return right.second < left.second;
                });

                // printing the results
                if (removedDupes.size() < 1) {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "Uh oh. There are no search results for that query.\n"
                         << "Try another query." << endl;
                } else if (removedDupes.size() > 15) {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "The top 15 results are: " << endl;
                    for (int i = 0; i < 15; ++i) {
                        cout << letters[i] << " - ";
                        resultArticles(removedDupes[i].first);
                        cout << endl;
                    }
                    cout << "\nEnter the letter corresponding to the article: ";
                    string letterInput;
                    cin >> letterInput;

                    for (int i = 0; i < letters.size(); i++) {
                        if (letterInput == letters[i]) {
                            accessedArticle(removedDupes[i].first);
                        }
                    }
                } else {
                    auto queryStop = high_resolution_clock::now();
                    auto timeToExecMilli = duration_cast<milliseconds>(queryStop - queryStart);
                    auto timeToExecSec = duration_cast<seconds>(queryStop - queryStart);
                    auto timeToExecMin = duration_cast<minutes>(queryStop - queryStart);
                    cout << "\nThe time to search was: " << timeToExecMin.count()
                         << " min " << timeToExecSec.count() % 60 << " sec " << timeToExecMilli.count() % 1000
                         << " ms." << std::endl;
                    cout << endl;
                    cout << "The results that with one or more search terms are: " << endl;
                    int j = 0;
                    for (const auto &path: removedDupes) {
                        cout << letters[j] << " - ";
                        resultArticles(path.first);
                        cout << endl;
                        j++;
                    }
                    cout << "\nEnter the letter corresponding to the article: ";
                    string letterInput;
                    cin >> letterInput;

                    for (int i = 0; i < letters.size(); i++) {
                        if (letterInput == letters[i]) {
                            accessedArticle(removedDupes[i].first);
                        }
                    }
                }
            }

            // return to menu option after reading a specific article
            while (true) {
                cout << "q. Return to Menu" << endl;
                cin >> input;
                if (input == 'q' || input == 'Q') {
                    break;
                } else {
                    cout << "Invalid entry. Please try again." << endl;
                    continue;
                }
            }
        } // end menu option b

        // menu option c for printing statistics of unique ORGs and PERSONS
        if (input == 'c' || input == 'C') {
            cout << "Number of unique organizations: " << orgs.getSize() << ". Number of unique pesons: "
                 << person.getSize() << ". Number of unique words: " << wordIndex.getSize() << "." << endl;
        }

        // menu option d for printing top 25 most frequently occurring words in the entire dataset
        if (input == 'd' || input == 'D') {
            std::multimap<int, string> display = swapValueAndKey(allWords);
            int i = 25;
            int j = 1;
            cout << "Top 25 Most Frequent Terms" << endl
                <<  "--------------------------" << endl;
            for(auto it = display.rbegin(); (i != 0); it++){
                if(i == 25) {
                    it++;
                }
                cout << j << ". Term: " << it->second << " occurs " << it->first << " times." << endl;
                i--;
                j++;
            }
        }

    } // end while loop
}

// eliminating duplicate vectors got code from someone on stackoverflow
// https://stackoverflow.com/questions/16476099/remove-duplicate-entries-in-a-c-vector
std::vector<std::pair<string, int>>
QueryProcessor::eliminateVectorDupes(std::vector<std::pair<string, int>> &unionPaths) {
    for (int i = 0; i < unionPaths.size(); i++) {
        string current = unionPaths.at(i).first;

        for (int j = i; j < unionPaths.size(); j++) {
            if (j == i) {
                continue;
            } else {
                string temp = unionPaths.at(j).first;
                if (current == temp) {
                    int curr = unionPaths.at(i).second;
                    int next = unionPaths.at(j).second;
                    if (curr < next) {
                        auto iter = unionPaths.begin() + i;
                        unionPaths.erase(iter);
                    } else {
                        auto iter = unionPaths.begin() + j;
                        unionPaths.erase(iter);
                    }
                    j--;
                }
            }
        }
    }
    return unionPaths;
}

// result articles returns the articles
// title, publisher, and date given a path
void QueryProcessor::resultArticles(const string &inputPath) {
    //open an ifstream on the file of interest and check that it could be opened.
    std::ifstream input(inputPath.c_str());
    if (!input.is_open())
        std::cerr << "cannot open file" << endl;

    //Create a RapidJSON IStreamWrapper using the file input stream above.
    rapidjson::IStreamWrapper isw(input);

    //Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);

    //Now that the document is parsed, we can access different elements the JSON using
    //familiar subscript notation.

    //This accesses the -title- element in the JSON. Since the value associated with title is a string (rather than
    // an array or something else), we call the GetString() function to return the actual title of the article
    // as a c-string.
    //
    auto val = d["title"].GetString();
    cout << val << endl;

    auto publisher = d["thread"]["site"].GetString();

    auto date = d["thread"]["published"].GetString();

    cout << std::setw(15) << std::right << "Publisher: " << publisher << " | Date: " << date << endl;

}

// accessed article returns the text for an article
// if user selects that specific article
void QueryProcessor::accessedArticle(const string &filePath) {
    //open an ifstream on the file of interest and check that it could be opened.
    std::ifstream input(filePath.c_str());
    if (!input.is_open())
        std::cerr << "cannot open file" << endl;

    //Create a RapidJSON IStreamWrapper using the file input stream above.
    rapidjson::IStreamWrapper isw(input);

    //Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    rapidjson::Document d;
    d.ParseStream(isw);

    //Now that the document is parsed, we can access different elements the JSON using
    //familiar subscript notation.

    //This accesses the -title- element in the JSON. Since the value associated with title is a string (rather than
    // an array or something else), we call the GetString() function to return the actual title of the article
    // as a c-string.
    //
    cout << endl << endl;
    cout << "Title: ";
    auto val = d["title"].GetString();
    cout << val << endl << endl;

    auto publisher = d["thread"]["site"].GetString();

    auto date = d["thread"]["published"].GetString();

    cout << std::setw(15) << std::right << "Publisher: " << publisher << " | Date: " << date << "\n" << endl;
    string text = d["text"].GetString();

    cout << text << "\n\n\n" << endl;

}
// end function
