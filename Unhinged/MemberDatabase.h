#ifndef MemberDatabase_h
#define MemberDatabase_h

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "provided.h"
#include "PersonProfile.h"
using namespace std;

class MemberDatabase
{
public:
    MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<vector<string>> attValPairtoEmail;
    RadixTree<PersonProfile> emailToPersonProfile;
};

#endif /* MemberDatabase_hpp */
