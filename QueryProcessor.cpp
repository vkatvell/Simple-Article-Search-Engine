//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

std::string QueryProcessor::readingQueries(string& input) {
//    const char AND[] = "AND";
//    const char OR[] = "OR";
//    const char NOT[] = "NOT";
//    const char ORG[] = "ORG";
//    const char PERSON[] = "PERSON";


        // if statement for AND comparison
        if (input.substr(0, 3) == "AND") {
            cout << "Read in the AND of query only" << endl;

            string word = input.substr(4, input.length());

            // converting word to lowerCase
            toLower(word);

            string stemmedQ = stemQuery(word);

            cout << "The stemmed query is: " << stemmedQ << endl;
            return stemmedQ;
        }
        else {
            string word = input.substr(0, input.length());

            toLower(word);

            string stemmedQ = stemQuery(word);

            cout << "The stemmed query is: " << stemmedQ << endl;
            return stemmedQ;
        }
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
        cout << "1. Clear current index" << endl;
        cout << "2. Parse a new dataset" << endl;
        cout << "3. Read 15 articles from dataset" << endl;
        cout << "4. Enter a query" << endl;
        cout << "-1. Exit Search Engine program" << endl;

        // reading in user input for menu value
        int input{0};
        cin >> input;

        if(input == -1) {
            continue_running = false;
        } // end menu option -1

        // ending program if user selects -1 option
        if(!continue_running) {
            cout << "Thank you for searching. Goodbye..." << endl;
            break;
        }

        // 1. clearing current index
        if(input == 1) {
            // clear wordIndex, peopleIndex, orgIndex

            // parse new dataset
            cout << "Enter path to a new dataset to parse: ";
            string newPath;

            cin >> newPath;
            // call parser test file system function and pass in new empty avl trees for
            // three indexes

            // continue and reprint menu
        } // end menu option 1

        // 2. parse a new dataset
        if(input == 2) {

            AVLTree<string, string> wordIndex;

            Parser p;

            // parse new dataset
            cout << "Enter path to a new dataset to parse: ";
            string newPath;

            cin >> newPath;

            p.testFileSystem(newPath.c_str(), wordIndex);
            // call parser test file system function and pass in new empty avl trees for
            // three indexes

            // continue and reprint menu
        } // end menu option 2

        // 3. read top 15 files
        if (input == 3) {
            cout << "15 articles from dataset to peruse:" << endl;
            // //open an ifstream on the file of interest and check that it could be opened.
            //    ifstream input(fileName);
            //    if(!input.is_open())
            //        std::cerr << "cannot open file" << endl;
            //
            //    //Create a RapidJSON IStreamWrapper using the file input stream above.
            //    IStreamWrapper isw(input);
            //
            //    //Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
            //    Document d;
            //    d.ParseStream(isw);
            //
            //    //Now that the document is parsed, we can access different elements the JSON using
            //    //familiar subscript notation.
            //
            //    //This accesses the -title- element in the JSON. Since the value associated with title is a string (rather than
            //    // an array or something else), we call the GetString() function to return the actual title of the article
            //    // as a c-string.
            //    //
            //    auto val = d["title"].GetString();
            ////    cout << "Title: " << val << endl;
            //
            //    //The Persons entity for which you're building a specific inverted index is contained in
            //    // top level -entities- element.  So that's why we subscript with ["entities"]["persons"].
            //    // The value associated with entities>persons is an array.  So we call GetArray() to get
            //    // an iterable collection of elements
            //    auto persons = d["entities"]["persons"].GetArray();
            //
            //    //We iterate over the Array returned from the line above.  Each element kind of operates like
            //    // a little JSON document object in that you can use the same subscript notation
            //    // to access particular values.
            ////    cout << "  Person Entities:" << endl;
            ////    for (auto& p : persons) {
            ////        cout << "    > " << setw(30) << left << p["name"].GetString() << endl;
            ////    }
            //
            //    auto organizations = d["entities"]["organizations"].GetArray();
            ////    cout << " Organization Entities" << endl;
            ////    for(auto& o : organizations) {
            ////        cout << "    > " << setw(30) << left << o["name"].GetString() << endl;
            ////    }
            //
            //    string text = d["text"].GetString();
            //    //cout << text << endl;
        } // end menu option 3

        if(input == 4) {
            cout << "Enter a query: ";
            // call readingQueries function

            // then call searchTree function for the search string
//            // creating a string with the stemmed query word
//            string searchWord = q.readingQueries(queryString);
//
//            // unordereed set to store all the paths for the word
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
        } // end menu option 4


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
