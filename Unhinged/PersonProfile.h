#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include "RadixTree.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email);
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair(const AttValPair& attval);
    int GetNumAttValPairs() const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::unordered_set<string>> m_pairs;
    vector<AttValPair> v_pairs;
};
#endif /* PersonalProfile_hpp */
