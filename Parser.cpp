//
// Created by Noah Henson on 6/22/22.
//

#include "Parser.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
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

//default constructor
Parser::Parser() = default;


/**
 * traverse the filesystem using std::filesystem
 * @param path an absolute or relative path to a folder containing files
 * you want to parse.
 */
void Parser::testFileSystem(const char *path, AVLTree<string, string> & wordIndex, AVLTree<string, string> & personIndex, AVLTree<string, string> & orgIndex, int &counter) {

    //recursive_director_iterator used to "access" folder at parameter -path-
    //we are using the recursive iterator so it will go into subfolders.
    auto it = std::filesystem::recursive_directory_iterator(path);

    //read in stop words to be removed
    std::unordered_map<string, int> stopWords = readingStopWords("sample_data/stopwords.txt");

    //loop over all the entries.
    for(const auto& entry : it) {

//        cout << "--- " << setw(60) << left << entry.path().c_str() << " ---" << endl;

        //We only want to attempt to parse files that end with .json...
        if (entry.is_regular_file() && entry.path().extension().string() == ".json") {
            counter++; //counter for total docs
            testReadJsonFile(wordIndex, personIndex, orgIndex, entry.path().c_str(), stopWords, counter);
        }

    }

    cout << endl;
}

/**
 * reads and parses a json file and extracts the title and person
 * entities.
 * @param fileName filename with relative or absolute path included.
 */
void Parser::testReadJsonFile(AVLTree<string, string> & wordIndex, AVLTree<string, string> & personIndex,AVLTree<string, string> & orgIndex, const char *fileName, const std::unordered_map<string, int> & stopWords, int &counter) {

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
//    cout << "Title: " << val << endl;

    //The Persons entity for which you're building a specific inverted index is contained in
    // top level -entities- element.  So that's why we subscript with ["entities"]["persons"].
    // The value associated with entities>persons is an array.  So we call GetArray() to get
    // an iterable collection of elements
    auto persons = d["entities"]["persons"].GetArray();

    //We iterate over the Array returned from the line above.  Each element kind of operates like
    // a little JSON document object in that you can use the same subscript notation
    // to access particular values.
    std::unordered_map<string, int> person_map;
    for (auto& p : persons) {
        string temp = p["name"].GetString();
        std::transform(temp.begin(), temp.end(), temp.begin(), [](unsigned char c){ return std::tolower(c); });
        ++person_map[temp];
    }

    auto person_it = person_map.begin();
    std::pair<string, int> p_results;
    p_results.first = fileName;
    while(person_it != person_map.end()) {
        p_results.second = person_it->second;
        personIndex.insert(person_it->first, p_results); //filepath becomes a pair with filepath and it->second
        person_it++;
    }


    auto organizations = d["entities"]["organizations"].GetArray();
//    cout << " Organization Entities" << endl;
    std::unordered_map<string, int> org_map;
    for(auto& o : organizations) {
        string temp = o["name"].GetString();
        std::transform(temp.begin(), temp.end(), temp.begin(), [](unsigned char c) {return std::tolower(c);});
        ++org_map[temp];
    }

    auto org_it = org_map.begin();
    std::pair<string, int> o_results;
    o_results.first = fileName;
    while(org_it != org_map.end()) {
        o_results.second = org_it->second;
        orgIndex.insert(org_it->first, o_results); //filepath becomes a pair with filepath and it->second
        org_it++;
    }



    string text = d["text"].GetString();

    std::unordered_map<string, int> text_map = tokenizer(text, " \n\t\r\f");

    removeStopWords(text_map, stopWords);

    std::unordered_map<string, int> stemmed_map = stemmer(text_map);

    auto it = stemmed_map.begin();

    string filePath = fileName;



    //every 10000 documents parsed, print an * to show loading progress
    if(counter % 10000 == 0) {
        cout << "*";
        cout.flush();
    }

    //creates a pair with string filepath and int number of frequencies in the document, insert into AVL Tree
    std::pair<string, int> results;
    results.first = fileName;
    while(it != stemmed_map.end()) {
        results.second = it->second;
        wordIndex.insert(it->first, results); //filepath becomes a pair with filepath and it->second
        it++;
    }

    input.close();
}

//string tokenizer using iterators
std::unordered_map<string, int> Parser::tokenizer(string& arg, const string& delim) {
    std::vector<string> hold;
    std::unordered_map<string, int> umap;
    //remove punctuation from the original string (before tokenizing)
    arg.erase(std::remove_if(arg.begin(), arg.end(), ispunct), arg.end());
    std::transform(arg.begin(), arg.end(), arg.begin(), [](unsigned char c){ return std::tolower(c);});

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

    //insert each string into the map
    for(string& i : hold) {
        ++umap[i];
    }

    return umap;



}

// reading in stop words file and returning a vector of all stopwords to remove
std::unordered_map<string, int> Parser::readingStopWords(const char* stopwordsfile) {

    //map to hold stop words
    std::unordered_map<string, int> umap;

    std::ifstream file_in(stopwordsfile);
        if (!file_in.is_open()) {
        std::cout << "Error opening stopwords file" << std::endl;
        exit(1);
    }

        //get first line of stop words file
    char buffer[100];
    file_in.getline(buffer, 100);

    //add stop word to the stop words map
    while(file_in.getline(buffer, 100)) {
        string cmpStop(buffer);
        umap[cmpStop]++;
    }

    file_in.close();

    return umap;
}

// removing stop words from vector of strings and returning new vector of cleaned words
void Parser::removeStopWords(std::unordered_map<string, int>& source, const std::unordered_map<string, int>& stopwords) {

    //for all stop words in the list, if present in the source map, remove it
    for(const auto& itr : stopwords) {
        if((source.find(itr.first) != source.end())) {
            source.erase(itr.first);
        }
    }

}

// stemmer function that returns a vector of stemmed words
std::unordered_map<string, int> Parser::stemmer(const std::unordered_map<string, int> & source) {

    std::unordered_map<string, int> umap;
    std::string sourceText;
    int val;

    //collect values from the source pair for stemming
    for (const auto& itr : source) {
        sourceText = itr.first;
        val = itr.second;

        // converting string to wstr
        std::wstringstream cls; // TODO can do this without stringstream?
        cls << sourceText.c_str();
        std::wstring total= cls.str();

        // creating stemming object
        stemming::english_stem<> Stem;

        // stemming the wstring
        Stem(total);

        // converting the wstring back into a string
        std::string str(total.begin(), total.end());

        // iterating with stemmed words and adding to map
        while(val > 0){
            ++umap[str];
            --val;
        }
    }

    return umap;
}
