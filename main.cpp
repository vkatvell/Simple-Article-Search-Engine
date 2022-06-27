/**
 * Summer 2022 Search Engine Template
 * includes some example code related to 2341 final project for summer 2022
 */
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>

#include "Parser.h"
#include "AVLTree.h"

//RapidJSON headers we need for our parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

#include "SearchEngine.h"

using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;

int main(int argc, char** argv) {

//    Parser p;
//
//    QueryProcessor q;

    SearchEngine s;


    cout << "-------------------------------------------" << endl;
    cout << "----------------- Parsing -----------------" << endl;
    cout << "-------------------------------------------" << endl;
    //p.testReadJsonFile("sample_data/news_0064570.json");

//    cout << "\n";
//    cout << "-------------------------------------------" << endl;
//    cout << "------     File System Example       ------" << endl;
//    cout << "-------------------------------------------" << endl;

    //p.testFileSystem("sample_data/");
//    p.testFileSystem("/Users/noahhenson/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a");

    // absolute path
//    p.testFileSystem("/Users/venkatsvellanki/Downloads/financial_articles/2018_01_112b52537b67659ad3609a234388c50a/");

//    p.testFileSystem("/Users/venkatsvellanki/Downloads/sample_data_sets/size-10/");

    s.searchForQuery(argv[1], argv[2]);

//    AVLTree<string, string> temp;
//    string hold = "string";
//    string buff = "clown";
//    int repeat = 0;
//    while(repeat >= 0) {
//        cin >> hold;
//        cin >> buff;
//        cin >>repeat;
//        temp.insert(hold, hold);
//    }
//    temp.print();


//    string input;
//    q.readingQueries(input, argv[1]);
return 0;
}