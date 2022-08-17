#ifndef RadixTree_h
#define RadixTree_h
#include <stdio.h>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

template <typename ValueType>
class RadixTree
{
public:
    RadixTree();
    ~RadixTree();
    void insert(std::string key, const ValueType& value);
    ValueType* search(std::string key) const;
private:
    struct Edge;
    struct Node
    {
        bool isWord = false;
        shared_ptr<ValueType> value = nullptr;
        shared_ptr<Edge> m_edges[128];
    };
    struct Edge
    {
        string stringPartial;
        shared_ptr<Node> next;
    };
    shared_ptr<Node> root;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree()
{
    shared_ptr<Node> newNode(new Node);
    root = newNode;
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree()
{
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType &value)
{
    shared_ptr<Node> p = root;
    shared_ptr<Edge> e;
    int index = 0;
    shared_ptr<ValueType> valuecopy(new ValueType(value));
    while(p != nullptr)
    {
        if(index < key.size())
        {
            //if key is not finished but there is no node for the next letter, create one
            if(p->m_edges[key[index]] == nullptr)
            {
                shared_ptr<Edge> newEdge(new Edge);
                p->m_edges[key[index]] = newEdge;
                newEdge->stringPartial = key.substr(index);
                shared_ptr<Node> newNode(new Node); 
                newEdge->next = newNode;
                newNode->isWord = true;
                newNode->value = valuecopy;
                return;
            }
            else
            {
                //find the amount of that matches with the node's partial string
                int substringSize = 0;
                e = p->m_edges[key[index]];
                string StringPartial = e->stringPartial;
                for(int i = 0; i < StringPartial.size() && index < key.size(); i++)
                {
                    if(key[index] == StringPartial[i])
                    {
                        index++;
                        substringSize++;
                    }
                    else
                        break;
                }
                //if all of node partial is hit, then go to the next node
                if(substringSize == StringPartial.size())
                    p = e->next;
                else
                {
                    //if not, create new node and branch out a new node
                    shared_ptr<Edge> newEdge(new Edge);
                    string StringPartial = e->stringPartial;
                    p->m_edges[StringPartial[0]] = newEdge;
                    newEdge->stringPartial = StringPartial.substr(0, substringSize);
                    shared_ptr<Node> newNode(new Node);
                    newEdge->next = newNode;
                    newNode->m_edges[StringPartial[substringSize]] = e;
                    e->stringPartial = StringPartial.substr(substringSize);
                    p = newNode;
                }
            }
        }
        //if key is fullfilled then set the node to endword and overwrite the value.
        else
        {
            p->isWord = true;
            p->value = valuecopy;
            return;
        }
    }
}

template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const
{
    shared_ptr<Node> p = root;
    shared_ptr<Edge> e;
    int index = 0;
    while(p != nullptr)
    {
        if(index < key.size())
        {
            if(p->m_edges[key[index]] == nullptr)
                return nullptr;
            else
            {
                int substringSize = 0;
                e = p->m_edges[key[index]];
                string StringPartial = e->stringPartial;
                for(int i = 0; i < StringPartial.size() && index < key.size(); i++)
                {
                    if(key[index] == StringPartial[i])
                    {
                        index++;
                        substringSize++;
                    }
                    else
                        break;
                }
                if(substringSize == StringPartial.size())
                    p = e->next;
                else
                    return nullptr;
            }
        }
        else
        {
            if(p->isWord)
                //only this path will return something, everything else is nullptrmiliTy3@charter.net
                return p->value.get();
            return nullptr;
        }
    }
    return nullptr;
}
/*
 template <typename ValueType>
 class RadixTree
 {
 public:
 RadixTree();
 ~RadixTree();
 void insert(std::string key, const ValueType& value);
 ValueType* search(std::string key) const;
 private:
 map<string, ValueType*> pairs;
 };
 
 template <typename ValueType>
 RadixTree<ValueType>::RadixTree()
 {
 }
 
 template <typename ValueType>
 RadixTree<ValueType>::~RadixTree()
 {
 }
 
 template <typename ValueType>
 void RadixTree<ValueType>::insert(std::string key, const ValueType &value)
 {
 ValueType* valuecopy = new ValueType(value);
 //    pairs.insert_or_assign(key, *valuecopy);
 pairs.insert(pair<std::string, ValueType*>(key, valuecopy));
 }
 
 template <typename ValueType>
 ValueType* RadixTree<ValueType>::search(std::string key) const
 {
 if(pairs.find(key) != pairs.end())
 return pairs.find(key)->second;
 return nullptr;
 }
 */
#endif /* RadixTree_hpp */
