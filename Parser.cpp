//
// Created by Noah Henson on 6/22/22.
//

#include "Parser.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

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

//default constructor
Parser::Parser() = default;


/**
 * example code for how to traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */
void Parser::testFileSystem(const char *path) {

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);

    //loop over all the entries.
    for(const auto& entry : it) {

        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        //We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            testReadJsonFile(entry.path().c_str());
        }

    }
}

/**
 * example code that reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void Parser::testReadJsonFile(const char *fileName) {

    //open an ifstream on the file of interest and check that it could be opened.
    ifstream input(fileName);
    if(!input.is_open())
        std::cerr << "cannot open file" << endl;

    //Create a RapidJSON IStreamWrapper using the file input stream above.
    IStreamWrapper isw(input);

    //Create a RapidJSON Document object and use it to parse the IStreamWrapper object above.
    Document d;
    d.ParseStream(isw);

    //Now that the document is parsed, we can access different elements the JSON using
    //familiar subscript notation.

    //This accesses the -title- element in the JSON. Since the value associated with title is a string (rather than
    // an array or something else), we call the GetString() function to return the actual title of the article
    // as a c-string.
    //
    auto val = d["title"].GetString();
    cout << "Title: " << val << endl;

    //The Persons entity for which you're building a specific inverted index is contained in
    // top level -entities- element.  So that's why we subscript with ["entities"]["persons"].
    // The value associated with entities>persons is an array.  So we call GetArray() to get
    // an iterable collection of elements
    auto persons = d["entities"]["persons"].GetArray();

    //We iterate over the Array returned from the line above.  Each element kind of operates like
    // a little JSON document object in that you can use the same subscript notation
    // to access particular values.
    cout << "  Person Entities:" << endl;
    for (auto& p : persons) {
        cout << "    > " << setw(30) << left << p["name"].GetString()
             << setw(10) << left << p["sentiment"].GetString() << endl;
    }

    auto organizations = d["entities"]["organizations"].GetArray();
    cout << " Organization Entities" << endl;
    for(auto& o : organizations) {
        cout << "    > " << setw(30) << left << o["name"].GetString()
             << setw(10) << left << o["sentiment"].GetString() << endl;
    }

    string text = d["text"].GetString();
    //cout << text << endl;
    std::unordered_map<string, int> text_map = tokenizer(text, " \n\t\r\f");

    std::vector<string> stopWords = readingStopWords("sample_data/stopwords.txt");

    removeStopWords(text_map, stopWords);

    //std::vector<string> stemmedText = stemmer(tokenized);

    //printing tokenized text
    for (const auto& i : text_map)
        cout << i.first << "      " << i.second << endl;

    input.close();
}

//string tokenizer using iterators
std::unordered_map<string, int> Parser::tokenizer(string& arg, const string& delim) {
    std::vector<string> hold;
    std::unordered_map<string, int> umap;
    //remove punctuation from the original string (before tokenizing)
    arg.erase(std::remove_if(arg.begin(), arg.end(), ispunct), arg.end());

    //iterator set to the first character in the string
    auto first = std::cbegin(arg);

    //while first it does not equal end char of the string
    while(first != std::cend(arg)) {

        //second iterator finds the end of the token by comparing chars to delimiter values
        auto second = std::find_first_of(first, std::cend(arg), std::cbegin(delim), std::cend(delim));
        //push back
        hold.emplace_back(first, second);
        //if second is equal to the end, restart the loop
        if(second == std::cend(arg)){
            break;
        }
        first = next(second); //otherwise continue the loop
    }

    for(auto & i : hold){
        umap[i]++;
    }
    return umap;
}

// reading in stop words file and returning a vector of all stopwords to remove
std::vector<string> Parser::readingStopWords(const char* stopwordsfile) {
    std::vector<string> stopVec;

    std::ifstream file_in(stopwordsfile);
        if (!file_in.is_open()) {
        std::cout << "Error opening stopwords file" << std::endl;
        exit(1);
    }
    char buffer[50];

    while (file_in.getline(buffer, 500)) {
        string cmpStop(buffer);
        stopVec.push_back(cmpStop);
    }
    file_in.close();

    return stopVec;
}

// removing stop words from vector of strings and returning new vector of cleaned words
void Parser::removeStopWords(std::unordered_map<string, int>& source, const std::vector<string>& stopwords) {
    std::vector<string> retVal;
    int i = 0;

    //for all stop words in the list
    while(i < stopwords.size()){
        //if key is present(find stops before end of list)
        if(!(source.find(stopwords.at(i)) == source.end())) {
            source.erase(stopwords.at(i));
        }
        ++i;
    }
}

// stemmer function that returns a vector of stemmed words
std::vector<string> Parser::stemmer(const std::vector<string> &arg) {
    std::vector<string> temp;
    std::string sourceText;
    for (int i = 0; i < arg.size(); i++) {
        sourceText = arg[i];

        std::wstringstream cls;
        cls << sourceText.c_str();
        std::wstring total= cls.str();
        // converting string to wstr
//        std::wstring wstr(sourceText.begin(), sourceText.end());

        // creating stemming object
        stemming::english_stem<> Stem;

        // stemming the wstring
        Stem(total);

        // converting the wstring back into a string using a wstring_convert from the codecvt library
        std::string str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(total);
        temp.push_back(str);
    }
    return temp;
}
