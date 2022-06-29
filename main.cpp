/**
 * Summer 2022 Search Engine Template
 * includes some example code related to 2341 final project for summer 2022
 */
#include <iostream>
#include <iomanip>

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

    SearchEngine s;

    //p.testReadJsonFile("sample_data/news_0064570.json");


    //p.testFileSystem("sample_data/");
//    p.testFileSystem("/Users/noahhenson/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a");

    // absolute path
//    p.testFileSystem("/Users/venkatsvellanki/Downloads/financial_articles/2018_01_112b52537b67659ad3609a234388c50a/");

//    p.testFileSystem("/Users/venkatsvellanki/Downloads/sample_data_sets/size-6000/");

    s.searchForQuery(argv[1], argv[2]);


return 0;
}