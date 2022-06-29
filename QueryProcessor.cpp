//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

struct intCmp {
    bool operator()(std::pair<string, int>& a, std::pair<string, int>& b) {
        return b.second < a.second;
    }
};

struct comparator {
    bool operator()(std::pair<string,int>& a, std::pair<string, int>& b) {
        if(b.second < a.second) {
            return a.first < b.first;
        }
        else {
            return b.first < a.first;
        }
    }
};

std::vector<std::string> QueryProcessor::readingQueries(string& input) {
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

//ANDwordsToSearch.push_back(andStr);
//ORwordsToSearch.push_back(orStr);

        if(input.substr(0,3) == "and") {
            isAND = true;
        }
        else if(input.substr(0,2) == "or") {
            isOR = true;
        }
        else {
            isAND = false;
            isOR = false;
        }

        std::stringstream query(input);

        string indWord;

        string afterNot;
        string afterOrg;
        string afterPerson;

        // AND case
        if(isAND && !isOR) {
            while(query >> indWord) {
                if(indWord == notStr) {
                    hasNOT = true;
                    ANDwordsToSearch.push_back(notStr);
                    query >> afterNot;
                    toLower(afterNot);
                    ANDwordsToSearch.push_back(afterNot);
                    ; // string with word after NOT
                }
                else if (indWord == orgStr){
                    hasORG = true;
                    ANDwordsToSearch.push_back(orgStr);
                    query >> afterOrg;
                    toLower(afterOrg);
                    ANDwordsToSearch.push_back(afterOrg);
                    ; // string with word after ORG
                }
                else if (indWord == persStr) {
                    hasPERSON = true;
                    ANDwordsToSearch.push_back(persStr);
                    query >> afterPerson;
                    toLower(afterPerson);
                    ANDwordsToSearch.push_back(afterPerson);
                    ; // string with word after PERSON
                }
                else {
                    query >> indWord;
                    toLower(indWord);
                    string stemmedQ = stemQuery(indWord);
                    ANDwordsToSearch.push_back(indWord);
                }
            }
            return ANDwordsToSearch;
        } else if(isOR && !isAND) {
            while(query >> indWord) {
                if(indWord == notStr) {
                    hasNOT = true;
                    ORwordsToSearch.push_back(notStr);
                    query >> afterNot;
                    toLower(afterNot);
                    ORwordsToSearch.push_back(afterNot);
                    ; // string with word after NOT
                }
                else if (indWord == orgStr){
                    hasORG = true;
                    ORwordsToSearch.push_back(orgStr);
                    query >> afterOrg;
                    toLower(afterOrg);
                    ORwordsToSearch.push_back(afterOrg);
                    ; // string with word after ORG
                }
                else if (indWord == persStr) {
                    hasPERSON = true;
                    ORwordsToSearch.push_back(persStr);
                    query >> afterPerson;
                    toLower(afterPerson);
                    ORwordsToSearch.push_back(afterPerson);
                    ; // string with word after PERSON
                }
                else {
//                    query >> indWord;
                    toLower(indWord);
                    string stemmedQ = stemQuery(indWord);
                    ORwordsToSearch.push_back(stemmedQ);
                }
            }
             return ORwordsToSearch;
        }

        if(!isAND && !isOR) {
            while (query >> indWord) {
                if (indWord == notStr) {
                    hasNOT = true;
                    wordsToSearch.push_back(notStr);
                    query >> afterNot;
                    toLower(afterNot);
                    wordsToSearch.push_back(afterNot);; // string with word after NOT
                } else if (indWord == orgStr) {
                    hasORG = true;
                    wordsToSearch.push_back(orgStr);
                    query >> afterOrg;
                    toLower(afterOrg);
                    wordsToSearch.push_back(afterOrg);; // string with word after ORG
                } else if (indWord == persStr) {
                    hasPERSON = true;
                    wordsToSearch.push_back(persStr);
                    query >> afterPerson;
                    toLower(afterPerson);
                    wordsToSearch.push_back(afterPerson);; // string with word after PERSON
                } else {
                    toLower(indWord);
                    string stemmedQ = stemQuery(indWord);
                    wordsToSearch.push_back(stemmedQ);
                }
            }
             return wordsToSearch;
        }

//            string word = input.substr(0, input.length());
//
//            toLower(word);
//
//            string stemmedQ = stemQuery(word);
//
//            cout << "The stemmed query is: " << stemmedQ << endl;
//            return stemmedQ;
}


std::string QueryProcessor::stemQuery(const std::string& input) {

    // converting string to wstring
    std::wstringstream cls; // TODO can do this without stringstream?
    cls << input.c_str();
    std::wstring total= cls.str();

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
                   [](unsigned char c){ return std::tolower(c); });
}

void QueryProcessor::menuSystem(AVLTree<string, string> &wordIndex, AVLTree<string, string> &person, AVLTree<string, string> &orgs) {
    // parse dataset first before calling this function

    cout << "Welcome to Noah and Venkat's Financial Article Search Engine" << endl;

    bool continue_running = true;

    while(continue_running) {
        cout << "a. Parse a new dataset" << endl;
        cout << "b. Enter a query" << endl;
        cout << "e. Exit Search Engine program" << endl;

        // reading in user input for menu value
        char input;
        cin >> input;

        if(input == 'E' || input == 'e') {
            continue_running = false;
        } // end menu option -1

        // ending program if user selects -1 option
        if(!continue_running) {
            cout << "Thank you for searching. Goodbye..." << endl;
            break;
        }

        // 1. parsing new dataset
        if(input == 'A' || input == 'a') {
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
            // call parser test file system function and pass in new empty avl trees for
            // three indexes
            p.testFileSystem(newPath.c_str(), newWordIndex, newPersonIndex, newOrgIndex, newCount);
            // continue and reprint menu
            cout << "Done parsing new dataset. Returning you to main menu..." << endl;
            menuSystem(newWordIndex, newPersonIndex, newOrgIndex);
            break;
        } // end menu option 1


       // goal search queries:
       // markets
       // AND social network
       // AND social network PERSON cramer
       // AND social network ORG facebook PERSON cramer
       // OR snap facebook
       // OR facebook meta NOT profits
       // bankruptcy NOT facebook
       // OR facebook instagram NOT bankruptcy ORG snap PERSON cramer
        if(input == 'B' || input == 'b') {

            cin.ignore();
            cout << "Enter a query: ";
            string query;

            getline(cin, query);
            // call readingQueries function
            std::vector<string> wordsToSearch = readingQueries(query);

            unordered_set<std::pair<string, int>, pair_hash> testCase;

//            testCase.operator=(wordIndex.searchTree(wordsToSearch[0]));
//
//            for(const auto& files : testCase) {
//                cout << files.first << ": " << files.second << std::endl;
//            }


            bool isAND = false;
            bool isOR = false;
            bool hasNOT = false;
            bool hasPERSON = false;
            bool hasORG = false;

            // first word of the vector is either AND, OR, or neither
            // so setting booleans for each case
            if(wordsToSearch[0] == "and") {
                isAND = true;
                isOR = false;
            } else if(wordsToSearch[0] == "or") {
                isOR = true;
                isAND = false;
            }
            else {
                isAND = false;
                isOR = false;
            }

            // doing set operations if vector is AND case INTERSECTION
            if(isAND == true && isOR == false) {

                // afterNot is the word that appears after NOT operator
                string afterNot;

                // afterPerson is the person that appears after PERSON operator
                string afterPerson;

                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if(itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }
                //TODO SET SUBTRACTION WITH TERM AFTER NOT

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if(itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));
                //TODO intersection with person index paths
                std::vector<std::pair<string, int>> personPath;
                for(const auto& file : personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(personPath.begin(), personPath.end());

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));
                //TODO interesection with org index paths
                std::vector<std::pair<string, int>> orgPath;
                for(const auto& file : orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(orgPath.begin(), orgPath.end());

                std::vector<std::pair<string, int>> cleanedVec;

                // intersection of person and org paths and cases
                if(hasPERSON && hasORG) {
                    std::vector<std::pair<string,int>> personOrgs;
                    std::set_intersection(personPath.begin(), personPath.end(),
                                                       orgPath.begin(), orgPath.end(),
                                                       std::back_inserter(personOrgs), comparator{});

//                    personOrgs.resize(poItr - personOrgs.begin());

                    cleanedVec = eliminateVectorDupes(personOrgs);
                } else if(hasPERSON && !hasORG) {
                    cleanedVec = personPath;
                } else if(hasORG && !hasPERSON) {
                    cleanedVec = orgPath;
                }
                else {
                   hasPERSON = false;
                   hasORG = false;
                }

                std::sort(cleanedVec.begin(), cleanedVec.end());

                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int i = 2;

                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[1]));

                std::vector<std::pair<string,int>> firstWordPaths;

                for(const auto& files : paths) {
                    firstWordPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                }

                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                std::vector<std::pair<string, int>> whileLoopPaths;

                if(!hasNOT && !hasORG && !hasPERSON) {
                    while(i < wordsToSearch.size()) {
                        // set intersection using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }
                else {
                    while (wordsToSearch[i] != "not" && wordsToSearch[i] != "person" && wordsToSearch[i] != "org") {
                        if(!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set intersection using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }

                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                //std::vector<std::pair<string, int>> wordPaths(100000);
                std::vector<std::pair<string, int>> wordPaths;
                //std::vector<std::pair<string, int>>::iterator it;

                std::set_intersection(firstWordPaths.begin(), firstWordPaths.end(),
                                    whileLoopPaths.begin(), whileLoopPaths.end(), std::back_inserter(wordPaths), comparator{}); //TODO figure out why this isn't working

                //wordPaths.resize(it - wordPaths.begin());

                if(hasPERSON || hasORG) {
                    std::vector<std::pair<string, int>> intersectPaths;
                    std::set_intersection(wordPaths.begin(), wordPaths.end(),
                                          cleanedVec.begin(), cleanedVec.end(),
                                          std::back_inserter(intersectPaths), comparator{});

                    auto removedDupes = eliminateVectorDupes(intersectPaths);

                    std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                        return right.second < left.second;
                    });

                    if(removedDupes.size() > 15) {
                        std::vector<std::pair<string, int>> indices(15);
                        std::partial_sort_copy(std::begin(removedDupes), std::end(removedDupes),
                                               std::begin(indices), std::end(indices), intCmp{}
                        );

                        cout << "The top 15 paths are: " << endl;
                        for(const auto& path : indices) {
                        cout << path.first << " with relevancy score: " << path.second << endl;
                            resultArticles(path.first);
                        }
                    }
                    else {
                        cout << "The paths that contain all search terms are: " << endl;
                        for(const auto& path : removedDupes) {
                        cout << path.first << " and the relevancy score: " << path.second << endl;
                            resultArticles(path.first);
                        }
                    }
                }
                else {
                    auto removedDupes = eliminateVectorDupes(wordPaths);

                    std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                        return right.second < left.second;
                    });

                    if(removedDupes.size() > 15) {
                        std::vector<std::pair<string, int>> indices(15);
                        std::partial_sort_copy(std::begin(removedDupes), std::end(removedDupes),
                                               std::begin(indices), std::end(indices), intCmp{}
                        );

                        cout << "The top 15 paths are: " << endl;
                        for(const auto& path : indices) {
//                        cout << path.first << " with relevancy score: " << path.second << endl;
                            resultArticles(path.first);
                        }
                    }
                    else {
                        cout << "The paths that contain all search terms are: " << endl;
                        for(const auto& path : removedDupes) {
//                        cout << path.first << " and the relevancy score: " << path.second << endl;
                            resultArticles(path.first);
                        }
                    }
                }

                // getting the words after NOT, PERSON, and ORG
                hasORG = false;
                hasPERSON = false;
                hasNOT = false;

            }

            // doing operations if set operation is OR case UNION
            else if(isOR == true && isAND == false) {
                // afterNot is the word that appears after NOT operator
                string afterNot;

                // afterPerson is the person that appears after PERSON operator
                string afterPerson;

                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                // getting the words after NOT, PERSON, and ORG
                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if(itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }

                //TODO SET SUBTRACTION WITH TERM AFTER NOT

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if(itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));

                std::vector<std::pair<string, int>> personPath;
                for(const auto& file : personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(personPath.begin(), personPath.end());

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));

                std::vector<std::pair<string, int>> orgPath;
                for(const auto& file : orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(orgPath.begin(), orgPath.end());

                // union of person and org paths
                std::vector<std::pair<string,int>> personOrgs(100000);
                auto poItr = std::set_union(personPath.begin(), personPath.end(),
                                                   orgPath.begin(), orgPath.end(), personOrgs.begin());

                personOrgs.resize(poItr - personOrgs.begin());

                auto cleanedVec = eliminateVectorDupes(personOrgs);


                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int i = 2;

                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[1]));

                std::vector<std::pair<string,int>> firstWordPaths;

                for(const auto& files : paths) {
                    firstWordPaths.emplace_back(files.first, files.second);
                }

                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                std::vector<std::pair<string, int>> whileLoopPaths;

                if(!hasNOT && !hasORG && !hasPERSON) {
                    while (i < wordsToSearch.size()) {
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }
                else {
                    while (wordsToSearch[i] != "not" && wordsToSearch[i] != "person" && wordsToSearch[i] != "org") {
                        if(!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }

                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                std::vector<std::pair<string, int>> wordPaths(100000);
                std::vector<std::pair<string, int>>::iterator it;

                it = std::set_union(firstWordPaths.begin(), firstWordPaths.end(),
                                           whileLoopPaths.begin(), whileLoopPaths.end(), wordPaths.begin());
                wordPaths.resize(it - wordPaths.begin());

                std::vector<std::pair<string, int>> unionPaths(100000);

                auto itr = std::set_union(wordPaths.begin(), wordPaths.end(),
                                    cleanedVec.begin(), cleanedVec.end(), unionPaths.begin());
                unionPaths.resize(itr - unionPaths.begin());

                auto removedDupes = eliminateVectorDupes(unionPaths);

//                auto removedDupes = eliminateVectorDupes(wordPaths);

                std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                    return right.second < left.second;
                });

                if(removedDupes.size() > 15) {
                    std::vector<std::pair<string, int>> indices(15);
                    std::partial_sort_copy(std::begin(removedDupes), std::end(removedDupes),
                                           std::begin(indices), std::end(indices), intCmp{}
                    );

                    cout << "The top 15 paths are: " << endl;
                    for(const auto& path : indices) {
//                        cout << path.first << " with relevancy score: " << path.second << endl;
                        resultArticles(path.first);
                    }
                }
                else {
                    cout << "The paths that contain all search terms are: " << endl;
                    for(const auto& path : removedDupes) {
//                        cout << path.first << " and the relevancy score: " << path.second << endl;
                        resultArticles(path.first);
                    }
                }

            }

            // neither AND nor OR case
            if(isAND == false && isOR == false) {
                // afterNot is the word that appears after NOT operator
                string afterNot;

                // afterPerson is the person that appears after PERSON operator
                string afterPerson;

                // afterOrg is the organization that appears after ORG operator
                string afterOrg;


                hasNOT = false;
                hasPERSON = false;
                hasORG = false;

                std::vector<string>::iterator itNot;
                itNot = std::find(wordsToSearch.begin(), wordsToSearch.end(), "not");
                if(itNot != wordsToSearch.end()) {
                    hasNOT = true;
                    afterNot = wordsToSearch[(itNot - wordsToSearch.begin()) + 1];
                }
                //TODO SET SUBTRACTION FOR ALL TERMS AFTER NOT

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if(itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));

                std::vector<std::pair<string, int>> personPath;
                for(const auto& file : personPaths) {
                    personPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(personPath.begin(), personPath.end());

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));

                std::vector<std::pair<string, int>> orgPath;
                for(const auto& file : orgPaths) {
                    orgPath.emplace_back(std::pair<string, int>(file.first, file.second));
                }
                std::sort(orgPath.begin(), orgPath.end());

                // union of person and org paths
                std::vector<std::pair<string,int>> personOrgs(100000);
                auto poItr = std::set_union(personPath.begin(), personPath.end(),
                                            orgPath.begin(), orgPath.end(), personOrgs.begin());

                personOrgs.resize(poItr - personOrgs.begin());

                auto cleanedVec = eliminateVectorDupes(personOrgs);

                //TODO union with wordIndex paths


                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[0]));

                std::vector<std::pair<string,int>> firstWordPaths;

                for(const auto& files : paths) {
                    firstWordPaths.emplace_back(files.first, files.second);
                }

                std::sort(firstWordPaths.begin(), firstWordPaths.end());

                std::vector<std::pair<string, int>> whileLoopPaths;

                int i = 1;

                if(!hasNOT && !hasORG && !hasPERSON) {
                    while (i < wordsToSearch.size()) {
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }
                else {
                    while (wordsToSearch[i] != "not" && wordsToSearch[i] != "person" && wordsToSearch[i] != "org") {
                        if(!hasNOT && !hasORG && !hasPERSON) {
                            break;
                        }
                        // set union using for loop
                        unordered_set<std::pair<string, int>, pair_hash> temp;

                        // setting temp to the set of the unordered set that was returned from
                        // the search tree function
                        temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                        for(const auto& files : temp) {
                            whileLoopPaths.emplace_back(std::pair<string, int>(files.first, files.second));
                        }
                        i++;
                    }
                }

                std::sort(whileLoopPaths.begin(), whileLoopPaths.end());

                std::vector<std::pair<string, int>> wordPaths(100000);
                std::vector<std::pair<string, int>>::iterator it;

                it = std::set_union(firstWordPaths.begin(), firstWordPaths.end(),
                                    whileLoopPaths.begin(), whileLoopPaths.end(), wordPaths.begin());
                wordPaths.resize(it - wordPaths.begin());

                std::vector<std::pair<string, int>> unionPaths(100000);

                auto itr = std::set_union(wordPaths.begin(), wordPaths.end(),
                                          cleanedVec.begin(), cleanedVec.end(), unionPaths.begin());
                unionPaths.resize(itr - unionPaths.begin());


                auto removedDupes = eliminateVectorDupes(unionPaths);

                std::sort(removedDupes.begin(), removedDupes.end(), [](auto &left, auto &right) {
                    return right.second < left.second;
                });

                if(removedDupes.size() > 15) {
                    std::vector<std::pair<string, int>> indices(15);
                    std::partial_sort_copy(std::begin(removedDupes), std::end(removedDupes),
                                           std::begin(indices), std::end(indices), intCmp{}
                    );

                    cout << "The top 15 paths are: " << endl;
                    for(const auto& path : indices) {
                        cout << path.first << " with relevancy score: " << path.second << endl;
                        resultArticles(path.first);

                        // TODO allow picking the result to read text from that article
                    }
                }
                else {
                    cout << "The paths that contain all search terms are: " << endl;
                    for(const auto& path : removedDupes) {
                        cout << path.first << " and the relevancy score: " << path.second << endl;
                        resultArticles(path.first);
                        // TODO allow picking the result to read text from that article
                    }
                }
            }

            // print statistics
                // - Total number of articles indexed
                // - Total words indexed (nodes in the wordIndex avl tree)
                // - ...timing data???

                while (true ) {
                    cout << "k. Return to Menu" << endl;
                    cin >> input;
                    if(input == 'K' || input == 'k') {
                        break;
                    }
                    else {
                        cout << "Invalid entry. Please try again." << endl;
                        continue;
                    }
                }

        } // end menu option 2


    } // end while loop



}

std::vector<std::pair<string, int>> QueryProcessor::eliminateVectorDupes(std::vector<std::pair<string, int>>& unionPaths) {
    for(int i = 0; i < unionPaths.size(); i++)
    {
        string current = unionPaths.at(i).first;

        for(int j = i; j < unionPaths.size(); j++)
        {
            if(j == i)
            {
                continue;
            }
            else
            {
                string temp = unionPaths.at(j).first;
                if(current == temp)
                {
                    int curr = unionPaths.at(i).second;
                    int next = unionPaths.at(j).second;
                    if(curr < next) {
                        auto iter = unionPaths.begin() + i;
                        unionPaths.erase(iter);
                    }
                    else {
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

void QueryProcessor::resultArticles(const string& inputPath) {
    //open an ifstream on the file of interest and check that it could be opened.
    std::ifstream input(inputPath.c_str());
    if(!input.is_open())
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

    string text = d["text"].GetString();
}
// end function

// examples from class with stringstream
    /*
     * stringstream ss;
     * ss << "SMU TCU UTD";
     * char buffer[10];
     * ss >> buffer;
     * cout << buffer; // prints SMU
     */

    /*
     * stringstream ss = doc["text"].GetString();
     */

    /*
     * create menu system that will allow user to process queries
     * 1. parse
     * 2. Enter query
     * 3. exit
     * > 2
     *      AND Boston Chicago NOT PERSON Mark
     *
     *   (query returns a relevancy list of documents that contain the words
     *   from query and allows user to select a document -> which then would
     *   call printResult function to show user relevant information from the
     *   target
     */
