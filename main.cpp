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

#include "QueryProcessor.h"

using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;

int main() {

    Parser p;

    QueryProcessor q;

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

//    AVLTree<string, int> temp;
//    string hold = "string";
//    int repeat = 0;
//    while(repeat >= 0) {
//        cin >> hold;
//        cin >>repeat;
//        temp.insert(hold);
//    }
//    temp.print();

    string input;
    q.readingQueries(input);
}