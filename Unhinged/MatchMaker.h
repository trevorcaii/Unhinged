#ifndef MatchMaker_h
#define MatchMaker_h

#include "PersonProfile.h"
#include "MemberDatabase.h"
#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "provided.h"
#include <algorithm> 
#include <unordered_map>
#include <set>

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
//    bool comparisonFunction (EmailCount& lhs, EmailCount& rhs) { return lhs.count > rhs.count; }
    struct compareFunction
    {
        inline bool operator() (EmailCount& lhs, EmailCount& rhs)
        {
            if(lhs.count != rhs.count)
                return lhs.count > rhs.count;
            else
                return lhs.email < rhs.email;
        }
    } comparisonFunction;
    MemberDatabase m_mdb;
    AttributeTranslator m_at;
};

#endif /* MatchMaker_hpp */
