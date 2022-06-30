/**
 * Summer 2022 Search Engine Final Project
 * made by Noah Henson and Venkat Vellanki
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

int main(int argc, char **argv) {

    SearchEngine s;

    // absolute paths for reference
//    /Users/noahhenson/Downloads/archive/2018_01_112b52537b67659ad3609a234388c50a

//    /Users/venkatsvellanki/Downloads/financial_articles/2018_01_112b52537b67659ad3609a234388c50a/


    s.searchForQuery(argv[1]);


    return 0;
}