#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>

#include "product.h"
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author): 
    Product(category, name, price, qty),
    ISBN_(isbn),
    author_(author)
{}
Book::~Book(){}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> kw;
    vector<string> sth( {author_, name_});
    for(string s : sth)
    {
        set<string> buf = parseStringToWords(s);
        kw = setUnion(kw, buf);
    }
    kw.insert(ISBN_);
    return kw;
}

std::string Book::displayString() const
{
    string str(name_  + "\nAuthor: " + author_
    + " ISBN: " + ISBN_ + "\n" + to_string(price_) + " " +to_string(qty_) + " left.");
    return str;
}
void Book::dump(std::ostream& os) const
{
    os<<category_ <<"\n"<<name_ <<"\n"<< price_ <<"\n"<< qty_ <<"\n"<<ISBN_<<"\n"<<author_<<endl;  
}
std::string Book::getISBN() const
{
    return ISBN_;
}
std::string Book::getAuthor() const
{
    return author_;
}
bool Book::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}
