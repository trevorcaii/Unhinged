#include "MatchMaker.h"

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_mdb = mdb;
    m_at = at;
}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    const PersonProfile* member = m_mdb.GetMemberByEmail(email);
    vector<AttValPair> sourcePairs;
    //get the source pairs for the entered email
    for(int i = 0; i < member->GetNumAttValPairs(); i++)
    {
        AttValPair sourcePair;
        member->GetAttVal(i, sourcePair);
        sourcePairs.push_back(sourcePair);
    }
    vector<AttValPair> compabtiblePairs;
    //find all compaitble pairs for those source pairs
    for(int i = 0; i < member->GetNumAttValPairs(); i++)
    {
        vector<AttValPair> sourcePair = m_at.FindCompatibleAttValPairs(sourcePairs[i]);
        for(vector<AttValPair>::iterator it = sourcePair.begin(); it != sourcePair.end(); it++)
        {
            //make sure there aren't repeats
            bool contains = false;
            for(int j = 0; j < compabtiblePairs.size(); j++)
                if(compabtiblePairs[j] == *it)
                    contains = true;
            if(!contains)
                compabtiblePairs.push_back(*it);
        }
    }
    //loop through all the compaitble pairs and get all the emails that have that pair, if they are already inside my emails list, then increment their count, if not, then add them with a count of 1
    unordered_map<string, EmailCount> emails;
    for(int i = 0; i < compabtiblePairs.size(); i++)
    {
        vector<string> matchingMembers = m_mdb.FindMatchingMembers(compabtiblePairs[i]);
        for(int j = 0; j < matchingMembers.size(); j++)
        {
            auto search = emails.find(matchingMembers[j]);
            if(search != emails.end())
                search->second.count += 1;
            else
            {
                EmailCount newEmail(matchingMembers[j], 1);
                emails.insert(pair<string, EmailCount>(matchingMembers[j], newEmail));
            }
        }
    }
    vector<EmailCount> matches;
    for(unordered_map<string, EmailCount>::iterator it = emails.begin(); it != emails.end(); it++)
        if(it->second.count >= threshold)
            matches.push_back(it->second);
    sort(matches.begin(), matches.end(), comparisonFunction);
    for(auto element : matches)
        cout << element.email << ", " << element.count << endl;
    return matches;
}
