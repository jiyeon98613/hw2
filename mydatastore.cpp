#include "util.h"
#include "datastore.h"
#include <string>
#include <set>
#include <map>
#include <vector>
#include <iostream>
#include "product.h"
#include "user.h"
#include "mydatastore.h"
#include "iterator"
using namespace std;

MyDataStore::MyDataStore(){}


MyDataStore::~MyDataStore()
{
    //delete prdcts and usrs
    for(Product* x : p_set) 
    {
        delete x;
    }
    // for(std::set<Product*>::iterator it = p_set.begin(); it != p_set.end(); ++it)
    // {
    //     delete *it;
    // }
    for(User* x : u_set) 
    {
        delete x;
    }
    // for(std::set<User*>::iterator it1 = u_set.begin(); it1 != u_set.end(); ++it1)
    // {
    //     delete *it1;
    // }
}
void MyDataStore::addProduct(Product* p)
{
    p_set.insert(p);
    //cout <<"p name: "<<p->getName()<<endl;
    std::set<string> keyword_set = p->keywords();
    cout << "debug: p->keyword() for " << p->getName()<< " is ";
    for( std::set<string>::iterator it = keyword_set.begin(); it != keyword_set.end(); ++it)

    {
        cout << *it <<", ";
        if(p_map.find(*it) == p_map.end()) //new term
        {
            std::set<Product*> buf_set = {p};
            p_map.insert(pair<string, set<Product*>>(*it,  buf_set));
        }
        else //have the term
        {
            p_map[*it].insert(p);
        }
    }
    cout << endl;
}


void MyDataStore::addUser(User* u)
{
    u_set.insert(u);
    for (User* usr : u_set)
    {
        u_map.insert(pair<string, User*>((*usr).getName(), usr));
    }
}


/**
 * @brief if type == 0 then it is AND situation, elif type == 1 then it is OR situaiton.
 * here we should implement SetUnion and SetIntersection.
 * 
 * @param terms 
 * @param type 
 * @return std::vector<Product*> 
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    //create a set of product that will store the products that have these terms
    set<Product*>search_result;
    set<Product*> empty_set;
    //set<string> terms_buf;
    vector<Product*> prod_v;
    
    if(p_map.find(terms[0]) != p_map.end()) // if there is any product for the first term
    {
        if(terms[0].size() <= 1)
        {
            return prod_v;
        }
        search_result = p_map.find(terms[0])->second;//a set of products match with the first term
    } 
     
    for(std::vector<std::string>::iterator it = terms.begin()+1; it != terms.end(); ++it)
    {
        if((*it).size()<= 1)
        {
            return prod_v;
        }
        if(p_map.find(*it) == p_map.end()) //if there is no search result
        {  
            if(type == 0) //AND case
            {
                cout << "here1"<<endl;
                search_result = setIntersection(search_result, empty_set);
            }
            else if(type == 1) //OR case
            {
                cout << "here2"<<endl;
                search_result = setUnion(search_result, empty_set);
            }
        }
        else if(type == 0) //AND case
        {
            cout << "here4"<<endl;
            search_result = setIntersection(search_result, p_map.find(*it)->second);
        }
        else if(type == 1) //OR case
        {
            cout << "here5"<<endl;
            search_result = setUnion(search_result, p_map.find(*it)->second);
        }
        
    }
    //vector<Product*> prod_v;
    for(Product* p : search_result)
    {
        prod_v.push_back(p);
    }
    return prod_v;
}


void MyDataStore::addCart(string usr_name, Product* p)
{
    if(u_map.find(usr_name) == u_map.end())
    {
        cout << "Invalid username";
        return;
    }

    (cart[usr_name]).push_back(p); 
    cout<<p->getName()<<endl;
    cout<<"Successfully added to your cart, "<< usr_name<<"."<<endl;
}
void MyDataStore::viewCart(string usr_name)
{   
    //debugging
    /* cout<<"inside ViewCart f: "<<endl;;
    for(Product* p : cart[usr_name])
    {
        cout<< p->getName()<<endl;
     }*/


    if(u_map.find(usr_name) == u_map.end())
    {
        cout<< "Invalid username" <<endl;
        return;
    }
    std::vector<Product*> buf = (cart[usr_name]);
    std::vector<Product*>::iterator it;
    int a = 1;
    for(it = buf.begin(); it !=buf.end() ; ++it)
    {
        cout <<a<<". "<< ((*it)->getName()) <<endl;
        ++a;
    }
}
void MyDataStore::buyCart(string usr_name)
{
    //check if the user name is valid
    if(u_map.find(usr_name) == u_map.end())
    {
        cout<< "Invalid username" <<endl;
        return;
    }

    // process through all the items in the cart
    User* u_ptr = u_map[usr_name];
    vector<Product*> items = cart[usr_name]; // or cart.find(usr_name)->second
    //debug
    cout<<"BUYCART: In the cart, there are " << endl;
    for (Product* p : items)
    {
        cout<<p->getName() <<endl;
    }
    vector<Product*>::iterator it = items.begin();
    while(u_ptr->getBalance() > 0 && it != items.end())
    {
        cout << "*it->getname = "<<(*it)->getName()<<endl;
        //if (budget > price of this product) and the product is not sold out  
        if((*it)->getQty() >0 && u_ptr->getBalance() >= (*it)->getPrice() )
        {
            (*it)->subtractQty(1);
            cart[usr_name].erase(cart[usr_name].begin());
            u_ptr->deductAmount((*it)->getPrice());
            //print out 
            cout<< "You Successfully Purcahsed: "<<(*it)->getName()<<endl;
            
        } 
        // else: sold out or  budget is not enough
        else if((*it)->getQty() == 0)
        {
            //print out 
            cout<< "Sold out: "<<(*it)->getName()<<endl;
            //p_set.erase();
            //p_map.
        }
        else 
        {
            //print out 
            cout<< "Balance not enough to purchase: "<<(*it)->getName()<<endl;
            
        }
        ++it;
    }
    //cart[usr_name].clear();
    

    

}


void MyDataStore::dump(std::ostream& ofile)
{
    for(Product* x : p_set) 
    {
        (*x).dump(ofile);
    }

    for(User * x : u_set) 
    {
        (*x).dump(ofile);
    }
}
