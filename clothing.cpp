#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"
#include "util.h"
#include <iostream>
#include <string>

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand): 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{

}
Clothing::~Clothing()
{
    
}

std::set<std::string> Clothing::keywords() const
{
    set<string> kw;
    vector<string> sth({brand_, name_});
    for(string s : sth)
    {
        set<string> buf = parseStringToWords(s);
        kw = setUnion(kw, buf);
    }
    return kw;
}


std::string Clothing::displayString() const
{
    string str(name_  + "\nSize: " + size_ + " Brand: " + brand_ 
            + "\n" +to_string(price_)+ " " + to_string(qty_) + " left");
    return str;
}
void Clothing::dump(std::ostream& os) const
{os<<category_<<"\n" <<name_ <<"\n"<< price_ <<"\n"<< qty_ <<"\n"<<size_<<"\n"<<brand_<<"\n"<<endl;  }
std::string Clothing::getize() const
{
    return size_;
}
std::string Clothing::getBrand() const{
    return brand_;
}
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;}