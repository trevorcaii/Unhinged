#include "PersonProfile.h"

PersonProfile::PersonProfile(std::string name, std::string email)
{
    m_name = name;
    m_email = email;
}

string PersonProfile::GetName() const
{
    return m_name;
}

string PersonProfile::GetEmail() const
{
    return m_email;
}

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
    unordered_set<string>* setBefore = m_pairs.search(attval.attribute);
    if(setBefore != nullptr)
    {
        if(setBefore->find(attval.value) == setBefore->end())
        {
            v_pairs.push_back(attval);
            setBefore->insert(attval.value);
        }
    }
    else
    {
        m_pairs.insert(attval.attribute, unordered_set<string>{attval.value});
        v_pairs.push_back(attval);
    }
}

int PersonProfile::GetNumAttValPairs() const
{
    return v_pairs.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if(attribute_num < 0 || attribute_num > GetNumAttValPairs())
        return false;
    attval = v_pairs[attribute_num];
    return true;
}
