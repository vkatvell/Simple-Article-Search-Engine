//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

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

        if(isAND == false && isOR == false) {
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

            // doing set operations if vector is AND case
            if(isAND == true && isOR == false) {

                cout << "AND case boolean values - isAND: " << isAND << " isOR: " << isOR <<  endl;

                for (auto words : wordsToSearch) {
                    cout << words << endl;
                }

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
                //TODO SET SUBTRACTION WITH ALL TERMS AFTER NOT

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if(itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));
                //TODO intersection with person index paths

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));
                //TODO interesection with org index paths


                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int i = 2;

                unordered_set<std::pair<string, int>, pair_hash> paths;

               paths.operator=(wordIndex.searchTree(wordsToSearch[1]));

                for(const auto& files : paths) {
                    cout << files.first << ": " << files.second << std::endl;
                }

                while (wordsToSearch[i] != "not" && wordsToSearch[i] != "person" && wordsToSearch[i] != "org") {
                    if(!hasNOT && !hasORG && !hasPERSON) {
                        break;
                    }
                    // set intersection using for loop
                    unordered_set<std::pair<string, int>, pair_hash> temp;

                    // setting paths to the set of the unordered set that was returned from
                    // the search tree function
                    temp.operator=(wordIndex.searchTree(wordsToSearch[i]));

                    auto temp_end = temp.end();
                    for(auto pairs = temp.begin(); pairs != temp_end; ++pairs) {
                        for(auto pathsPair = paths.begin(); pathsPair != paths.end(); ++pathsPair) {
                        auto it = std::find_if(paths.begin(), paths.end(),
                                               [&pairs](auto& el){ return el.first == pairs->first; });
                            if(it == paths.end()) {
                                ;
                            }
                            else {
                                paths.erase(it);
                            }
                        }
                    }
                    i++;
                }

                // getting the words after NOT, PERSON, and ORG
                hasORG = false;
                hasPERSON = false;
                hasNOT = false;

            }

            // doing operations if set operation is OR case
            else if(isOR == true && isAND == false) {

                cout << "OR case boolean values - isAND: " << isAND << " isOR: " << isOR <<  endl;

                for (auto words : wordsToSearch) {
                    cout << words << endl;
                }

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

                //TODO SET SUBTRACTION WITH ALL TERMS AFTER NOT

                std::vector<string>::iterator itPerson;
                itPerson = std::find(wordsToSearch.begin(), wordsToSearch.end(), "person");
                if(itPerson != wordsToSearch.end()) {
                    hasPERSON = true;
                    afterPerson = wordsToSearch[(itPerson - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> personPaths;
                personPaths.operator=(person.searchTree(afterPerson));
                //TODO union with person index paths

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));
                //TODO union with org index paths


                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
                int i = 2;

                unordered_set<std::pair<string, int>, pair_hash> paths;

                paths.operator=(wordIndex.searchTree(wordsToSearch[1]));

                for(const auto& files : paths) {
                    cout << files.first << ": " << files.second << std::endl;
                }


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
                        cout << files.first << ": " << files.second << endl;
                    }

                    auto temp_end = temp.end();
                    for(auto pairs = temp.begin(); pairs != temp_end; ++pairs) {
                        for(auto pathsPair = paths.begin(); pathsPair != paths.end(); ++pathsPair) {
                            auto it = std::find_if(paths.begin(), paths.end(),
                                                   [&pairs](auto& el){ return el.first == pairs->first; });
                            if(it == paths.end()) {
                                std::pair<string, int> newPair;
                                newPair.first = pairs->first;
                                newPair.second = pairs->second;
                                paths.insert(newPair);
                            }
                            else {
                                ; // do nothing
                            }
                        }
                    }
                    i++;
                }
            }


            if(isAND == false && isOR == false) {
                // afterNot is the word that appears after NOT operator
                string afterNot;

                // afterPerson is the person that appears after PERSON operator
                string afterPerson;

                // afterOrg is the organization that appears after ORG operator
                string afterOrg;

                testCase.operator=(wordIndex.searchTree(wordsToSearch[0]));

                for(const auto& files : testCase) {
                    cout << files.first << ": " << files.second << std::endl;
                }

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
                for(const auto& paths : personPaths) {
                    cout << paths.first << ": " << paths.second << endl;
                }
                //TODO if after NOT subtract set from wordIndex paths

                std::vector<string>::iterator itOrg;
                itOrg = std::find(wordsToSearch.begin(), wordsToSearch.end(), "org");
                if(itOrg != wordsToSearch.end()) {
                    hasORG = true;
                    afterOrg = wordsToSearch[(itOrg - wordsToSearch.begin()) + 1];
                }
                unordered_set<std::pair<string, int>, pair_hash> orgPaths;
                orgPaths.operator=(orgs.searchTree(afterOrg));
                for(const auto& paths : orgPaths) {
                    cout << paths.first << ": " << paths.second << endl;
                }

                //TODO if after NOT subtract set org from wordIndex paths

                // while loop that starts calling searchTree function for each word until it reaches NOT, PERSON, or ORG
                // then performs set intersection
//                int i = 1;
//                unordered_set<std::pair<string, int>, pair_hash> paths;
//                while (wordsToSearch[i] != "NOT" || wordsToSearch[i] != "PERSON" || wordsToSearch[i] != "ORG") {
//                    if( i == wordsToSearch.size()) {
//                        break;
//                    }
//
//                    paths.operator=(wordIndex.searchTree(wordsToSearch[i]));
//
//                    // getting the words after NOT, PERSON, and ORG
//
//                    i++;
//                }

            }



            //TODO use relevancy ranking to print results with paths as input and
            // then list out all possible articles names with associated number menu to read particular article

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



} // end function

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
