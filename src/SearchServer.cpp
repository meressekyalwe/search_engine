//
// Created by Meresse on 7/4/2022.
//

#include <sstream>
#include <algorithm>
#include "SearchServer.h"
#include "ConverterJSON.h"


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> Indexes;

    ConverterJSON converterJson;

    int responseLimit = converterJson.GetResponsesLimit();

    for (const auto& request : queries_input)
    {
        std::vector<RelativeIndex> Index;

        std::map<size_t, size_t> map; // doc_id & sum count (Rabs)

        std::vector<std::string> words; // words of one request

        std::istringstream iss(request);

        while (iss)
        {
            std::string subs;

            iss >> subs;

            if (!subs.empty())
            {
                words.push_back(subs);
            }
        }

        for (const auto& word : words)
        {
            std::vector<Entry> entries = _index.GetWordCount(word);

            if (!entries.empty())
            {
                size_t rabs = 0;

                for (auto entry : entries)
                {
                    rabs += entry.count;
                    map[entry.doc_id] = rabs;
                }
            }
        }

        for (auto it = map.begin(); it != map.end(); it++)
        {
            float rank = 0.f;

            auto iterator = std::max_element(map.begin(),map.end(),[] (const std::pair<char,int>& a, const std::pair<char,int>& b)->bool{ return a.second < b.second; });

            size_t rabsMax = iterator->second;

            rank = (float)it->second / (float)rabsMax;

            Index.push_back({it->first, rank});
        }

        sort(Index.begin(), Index.end(), std::greater<RelativeIndex>()); // сравнения rank The std::greater is a functional object which is used for performing comparisons.

        if (Index.size() > responseLimit)
        {
            Index.resize(responseLimit);
        }

        Indexes.push_back(Index);
    }

    return Indexes;
}
