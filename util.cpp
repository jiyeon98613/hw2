#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    //convert to lower case
    convToLower(rawWords);

    //create a set
    set<string> keywords; 

    //parse till the end of the rawWords
    int curr = 0, cntr = 0, last_punc =0;
    while(curr < rawWords.length())
    {
        //check if curr is punc or not
        if(rawWords.at(curr)<= 'z' && rawWords.at(curr) >= 'a')   //alphabet
        {
            ++cntr;
        } else                                                   //punc_mark
        {
            //debugger
            cout << "punc: '" <<rawWords.at(curr) <<"'"<< endl;
            cout << "last substr: "<<rawWords.substr(last_punc+1, cntr)<<endl;
            if(cntr >= 2)
            {
                keywords.insert(rawWords.substr(last_punc+1, cntr)) ;
            }

            //reset cntr
            cntr =0;

            //update last_punc to current punc
            last_punc = curr;

        }
        ++curr;
    }
    //check the last substring
    if(cntr >= 0 )
    {
        //debugger
        cout << "last substr: "<<rawWords.substr(last_punc+1, cntr)<<endl;
        
        keywords.insert(rawWords.substr(last_punc+1, cntr)) ;
        
    }

    //debugger
    cout << "Keywords: ";
    for(set<string>::iterator it = keywords.begin(); it != keywords.end(); ++it)
    {
        cout << *it;
    } cout << endl;
    
    return keywords;









}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
