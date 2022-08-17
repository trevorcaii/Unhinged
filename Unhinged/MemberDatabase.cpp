#include "MemberDatabase.h"

MemberDatabase::MemberDatabase(){}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::string name;
    std::string email;
    int numOfAttValPairs = 0;
    std::fstream file;
    file.open(filename, ios::in);
    std::string str;
    while(!file.eof())
    {
        std::getline(file, str);
        name = str;
        std::getline(file, str);
        email = str;
        if(emailToPersonProfile.search(email) != nullptr)
            return false;
        PersonProfile newPerson(name, email);
        std::getline(file, str);
        numOfAttValPairs = stoi(str);
        while(numOfAttValPairs > 0)
        {
            std::string stringAtt;
            std::string stringVal;
            std::getline(file, stringAtt, ',');
            std::getline(file, stringVal);
            AttValPair newPair(stringAtt, stringVal);
            newPerson.AddAttValPair(newPair);
            vector<string>* emailVector = attValPairtoEmail.search(stringAtt+stringVal);
            if(emailVector != nullptr)
                emailVector->push_back(email);
            else
                attValPairtoEmail.insert(stringAtt+stringVal, vector<string> {email});
            numOfAttValPairs--;
        }
        emailToPersonProfile.insert(email, newPerson);
        std::getline(file, str);
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::vector<std::string> emails {};
    vector<string>* searchResult = attValPairtoEmail.search(input.attribute + input.value);
    if(searchResult != nullptr)
        emails = *(searchResult);
    return emails;
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    return emailToPersonProfile.search(email);
}
