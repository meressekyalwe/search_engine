//
// Created by Meresse on 7/4/2022.
//

#include "SearchServer.h"
#include "ConverterJSON.h"
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>


std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &queries_input)
{
    std::vector<std::vector<RelativeIndex>> Indexes;

    ConverterJSON converterJson;

    size_t responseLimit = converterJson.GetResponsesLimit();

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
                for (auto entry : entries)
                {
                    auto it = map.find(entry.doc_id);

                    if (it != map.end())
                    {
                        map[entry.doc_id] += entry.count;
                    }
                    else
                    {
                        map[entry.doc_id] = entry.count;
                    }
                }
            }
        }

        std::pair<size_t, size_t> maxValuePair;
        int maxValue = 0;

        for (const auto& entry : map)
        {
            if (maxValue < entry.second)
            {
                maxValue = entry.second;
                maxValuePair = entry;
            }
        }
     

        size_t rabsMax = maxValuePair.second;

        for (auto it = map.begin(); it != map.end(); it++)
        {
            float f = static_cast<float>(it->second) / static_cast<float>(rabsMax);

            std::stringstream stream;

            stream << std::fixed << std::setprecision(3) << f;

            std::string s = stream.str();

            float rank = std::stof(s);

            Index.push_back({it->first, rank});
        }

        for (size_t i = 0; i < Index.size(); i++) // sort in descending order rank
        {
            for (size_t j = 0; j < Index.size() - 1; j++)
            {
                if (Index[j] < Index[j + 1])
                {
                    RelativeIndex temp = Index[j];
                    Index[j] = Index[j + 1];
                    Index[j + 1] = temp;
                }
            }
        }

        if (Index.size() > responseLimit)
        {
            Index.resize(responseLimit);
        }

        Indexes.push_back(Index);
    }

    return Indexes;
}
