#include <sstream>
#include <iomanip>
#include "product.h"
#include "clothing.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand): 
    Product(category, name, price, qty),
    size_(size),
    brand_(brand)
{}
Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const
{
    set<string> sth({brand_, name_});
    return sth;
}


std::string Clothing::displayString() const
{
    string str(getName()+" "+ brand_ +" "+ size_);
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