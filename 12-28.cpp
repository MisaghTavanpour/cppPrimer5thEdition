#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <memory>

using namespace std;
    using line_no = vector<string>::size_type;

class QueryResult {
    friend ostream& print(ostream&, const QueryResult&);
public:
    QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f): sought(s), lines(p), file(f) { }
private:
    string sought; // word this query represents
    shared_ptr<set<line_no>> lines; // lines it's on
    shared_ptr<vector<string>> file; // input file
};

/* ############################################################################# */

class TextQuery {
public:
    TextQuery(ifstream&);
    QueryResult query(const string&) const;
private:
    shared_ptr<vector<string>> file; // input file
    // map of each word to the set of the lines in which that word appears
    map<string,
    shared_ptr<set<line_no>>> wm;
};

// read the input file and build the map of lines to line numbers
TextQuery::TextQuery(ifstream &is): file(new vector<string>) {
    string text;
    while (getline(is, text)) {     // for each line in the file
        file->push_back(text);      // remember this line of text
        int n = file->size() - 1;   // the current line number
        istringstream line(text);   // separate the line into words
        string word;
        while (line >> word) {      // for each word in that line
            // if word isn't already in wm, subscripting adds a new entry
            auto &lines = wm[word]; // lines is a shared_ptr
            if (!lines) // that pointer is null the first time we see word
                lines.reset(new set<line_no>); // allocate a new set
            lines->insert(n);       // insert this line number
        }
    }
}

QueryResult TextQuery::query(const string &sought) const {
    // we'll return a pointer to this set if we don't find sought
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found
    else
        return QueryResult(sought, loc->second, file);
}

/* ############################################################################# */

ostream &print(ostream & os, const QueryResult &qr) {
    // if the word was found, print the count and all occurrences
    os << qr.sought 
       << " occurs "
       << qr.lines->size()
       << " " 
       << "time" // make_plural(qr.lines->size(), "time", "s")
       << endl;

    // print each line in which the word appeared
    for (auto num : *qr.lines) // for every element in the set
        // don't confound the user with text lines starting at 0
        os << "\t(line "
           << num + 1
           << ") "
           << *(qr.file->begin() + num)
           << endl;

    return os;
}

void runQueries(ifstream &infile) {
    // infile is an ifstream that is the file we want to query
    TextQuery tq(infile); // store the file and build the query map
    // iterate with the user: prompt for a word to find and print results
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        // stop if we hit end-of-file on the input or if a 'q' is entered
        if (!(cin >> s) || s == "q") break;
        // run the query and print the results
        print(cout, tq.query(s)) << endl;
    }
}

int main() {
    ifstream in("12-28.cpp");
    runQueries(in);
    return 0;
}
