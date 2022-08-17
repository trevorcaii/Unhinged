#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <fstream>
#include "RadixTree.h"
#include "provided.h"
using namespace std;

class AttributeTranslator
{
public:
    AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs( const AttValPair& source) const;
private:
    RadixTree<vector<AttValPair>> m_compatible;
};

#endif /* AttributeTranslator_hpp */
