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

using namespace rapidjson;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::setw;
using std::left;

int main() {

    Parser p;

    cout << "-------------------------------------------" << endl;
    cout << "------ RapidJSON Doc Parsing Example ------" << endl;
    cout << "-------------------------------------------" << endl;
    //p.testReadJsonFile("sample_data/news_0064570.json");

    cout << "\n";
    cout << "-------------------------------------------" << endl;
    cout << "------     File System Example       ------" << endl;
    cout << "-------------------------------------------" << endl;

    //p.testFileSystem("sample_data/");
//    p.testFileSystem("/Users/noahhenson/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a");

    // absolute path
//    p.testFileSystem("/Users/venkatsvellanki/Downloads/financial_articles/2018_01_112b52537b67659ad3609a234388c50a/");

    AVLTree<string, int> temp;
    string hold = "string";
    int repeat = 0;
    while(repeat >= 0) {
        cin >> hold;
        cin >>repeat;
        temp.insert(hold); //TODO why does this think its an int
    }
    temp.print();


}