//
// Created by Venkat Vellanki on 6/23/22.
//

#include "QueryProcessor.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

std::string QueryProcessor::readingQueries(string& input, const char * arg) {
//    const char AND[] = "AND";
//    const char OR[] = "OR";
//    const char NOT[] = "NOT";
//    const char ORG[] = "ORG";
//    const char PERSON[] = "PERSON";


    string inputCmdLine = arg;

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


std::string QueryProcessor::stemQuery(std::string input) {
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
