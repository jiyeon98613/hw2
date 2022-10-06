#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> newSet;
    typename std::set<T> buffer;
    typename std::set<T> buffer1;
    if(s1.size() != 0)
    {
        buffer = s1;
        buffer1 = s2;
    }
    else
    {
        buffer = s2;
        buffer1 = s1;
    }
    
    for(typename std::set<T>::iterator it1 = buffer.begin(); it1 != buffer.end(); ++it1)
    {
        if(buffer1.find(*it1) != buffer1.end()) // if there is *it1 in s2
        {
            newSet.insert(*it1);
        }
    }
    return newSet;
}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    typename std::set<T> newSet;
    typename std::set<T> buffer = s2;
    for(typename std::set<T>::iterator it1 = s1.begin(); it1 != s1.end(); ++it1)
    {
        if(s2.find(*it1) != s2.end()) //if there is *it1 in s2
        {
            buffer.erase(*it1);
        }
        
    }
    newSet = s1;
    newSet.insert(buffer.begin(), buffer.end());
    
    return newSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
