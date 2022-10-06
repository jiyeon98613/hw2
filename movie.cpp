#include <sstream>
#include <iomanip>
#include "product.h"
#include "movie.h"
#include "util.h"

using namespace std;
Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating):
    Product(category, name, price, qty),
    genre_(genre),
    rating_(rating)
{

}
Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
    set<string> kw;
    vector<string> sth({genre_, name_});
    for(string s : sth)
    {
        set<string> buf = parseStringToWords(s);
        kw = setUnion(kw, buf);
    }
    
    return kw;
}


std::string Movie::displayString() const
{
    string str(name_  + "\nGenre: " + genre_ + " Rating: " + rating_ 
            + "\n" +to_string(price_)+ " " + to_string(qty_) + " left");
    return str;
}

void Movie::dump(std::ostream& os) const
{os<<category_ <<"\n"<<name_ <<"\n"<< price_ <<"\n"<< qty_<<"\n" <<genre_<<"\n"<<rating_<<"\n"<<endl;  }
std::string Movie::getGenre() const
{
    return genre_;
}

std::string Movie::getRating() const
{
    return rating_;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const
{
    return false;
}