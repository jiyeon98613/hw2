#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include "product.h"
#include "book.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author): 
    Product(category, name, price, qty),
    ISBN_(isbn),
    author_(author)
{}
Book::~Book(){}

std::set<std::string> Book::keywords() const
{
    set<string> sth({ISBN_, author_, name_});
    return sth;
}

std::string Book::displayString() const
{
    string str(getName() +" "+ author_+ " " + ISBN_);
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

