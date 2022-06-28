//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

std::vector<std::string> QueryProcessor::readingQueries(string& input) {
string andStr = "AND";
string orStr = "OR";
string notStr = "NOT";
string orgStr = "ORG";
string persStr = "PERSON";

bool isAND = false;
bool isOR = false;
bool hasNOT = false;
bool hasORG = false;
bool hasPERSON = false;

std::vector<string> ANDwordsToSearch;
std::vector<string> ORwordsToSearch;
std::vector<string> wordsToSearch;

ANDwordsToSearch.push_back(andStr);
ORwordsToSearch.push_back(orStr);

        if(input.substr(0,3) == "AND") {
            isAND = true;
        }
        else if(input.substr(0,2) == "OR") {
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

        if(isAND) {
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
                    toLower(indWord);
                    string stemmedQ = stemQuery(indWord);
                    ANDwordsToSearch.push_back(indWord);
                }
            }
            return ANDwordsToSearch;
        }

        if(isOR) {
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

void QueryProcessor::menuSystem() {
    // parse dataset first before calling this function

    cout << "Welcome to Noah and Venkat's Financial Article Search Engine" << endl;

    bool continue_running = true;

    while(continue_running) {
        cout << "A. Parse a new dataset" << endl;
        cout << "B. Enter a query" << endl;
        cout << "E. Exit Search Engine program" << endl;

        // reading in user input for menu value
        char input;
        cin >> input;

        if(input == 'E') {
            continue_running = false;
        } // end menu option -1

        // ending program if user selects -1 option
        if(!continue_running) {
            cout << "Thank you for searching. Goodbye..." << endl;
            break;
        }

        // 1. parsing new dataset
        if(input == 'A') {
            // clear wordIndex, peopleIndex, orgIndex

            // parse new dataset
            cout << "Enter path to a new dataset to parse: ";
            string newPath;

            cin >> newPath;
            // call parser test file system function and pass in new empty avl trees for
            // three indexes

            // continue and reprint menu
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
        if(input == 'B') {
            cout << "Enter a query: ";
            string query;

            getline(cin, query);
            // call readingQueries function
            std::vector<string> wordsToSearch = readingQueries(query);



            // then call searchTree function for the search string
//            // creating a string with the stemmed query word
//            string searchWord = q.readingQueries(queryString);
//
//            // unordered set to store all the paths for the word
//            unordered_set<std::pair<string, int>, pair_hash> paths;
//
//            // setting paths to the set of the unordered set that was returned from
//            // the search tree function
//            paths.operator=(wordIndex.searchTree(searchWord));

            // use relevancy ranking to print results with paths as input and
            // then list out all possible articles names with associated number menu to read particular article
            // (SIMILAR TO 3rd MENU OPTION)

            // print statistics
                // - Total number of articles indexed
                // - Total words indexed (nodes in the wordIndex avl tree)
                // - ...timing data???
                cout << "0. Return to Menu" << endl;
                cin >> input;
                if(input == 0) {
                    continue;
                }
                else {
                    cout << "Invalid entry. Please try again." << endl;
                    cin >> input;
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
