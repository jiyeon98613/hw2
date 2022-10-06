#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "util.h"
#include "datastore.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include "product.h"
#include "user.h"

class MyDataStore: public DataStore
{
public:    
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::string usr_name, Product* p);
    void viewCart(std::string usr_name);
    void buyCart(std::string usr_name);


private:
    std::set<Product*> p_set;  //should be a vector
    std::map< std::string, std::set<Product*> > p_map;
    std::set<User*> u_set;
    std::map<std::string, User*>u_map;
    std::map<std::string, std::vector<Product*>> cart;
};
// @Todo
// when user hit the wrong usr name : print out sth
// INVALID USR NAME for valid username??
#endif