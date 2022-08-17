#include "AttributeTranslator.h"

AttributeTranslator::AttributeTranslator()
{
}

bool AttributeTranslator::Load(std::string filename)
{
    std::string source;
    std::string compatible;
    std::fstream file;
    file.open(filename, ios::in);
    std::string str;
    std::string sourceAtt;
    std::string sourceVal;
    std::string compatibleAtt;
    std::string compatibleVal;
    while(!file.eof())
    {
        std::getline(file, str, ',');
        if(!str.empty())
        {
            sourceAtt = str;
            std::getline(file, str, ',');
            sourceVal = str;
            std::getline(file, str, ',');
            compatibleAtt = str;
            std::getline(file, str);
            compatibleVal = str;
            AttValPair newPair(compatibleAtt, compatibleVal);
            vector<AttValPair>* attValPairVector = m_compatible.search(sourceAtt+sourceVal);
            if(attValPairVector != nullptr)
            {
                bool contains = false;
                for(int i = 0; i < attValPairVector->size(); i++)
                    if(attValPairVector->at(i) == newPair)
                        contains = true;
                if(!contains)
                    attValPairVector->push_back(newPair);
            }
            else
                m_compatible.insert(sourceAtt+sourceVal, vector<AttValPair> {newPair});

        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs( const AttValPair& source) const
{
    std::vector<AttValPair> pairs;
    std::string sourceAtt = source.attribute;
    std::string sourceVal = source.value;
    vector<AttValPair>* searchResult = m_compatible.search(sourceAtt+sourceVal);
    if(searchResult != nullptr)
       pairs = *(searchResult);
    return pairs;
}
