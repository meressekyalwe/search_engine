//
// Created by Meresse on 7/3/2022.
//
#include "InvertedIndex.h"
#include <algorithm>
#include <thread>
#include <sstream>
#include <string>
#include <set>


void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs)
{
    copy(input_docs.begin(), input_docs.end(), std::back_inserter(docs));

    std::vector<std::thread> threads;

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++)
    {
        threads.emplace_back([doc_id, this]()
        {
            std::string request = docs[doc_id];

            std::istringstream ss(request);

            std::string word;

            std::vector<std::string> words;

            std::set<std::string> unique_words;

            while (ss >> word)
            {
                if (!word.empty())
                {
                    words.push_back(word);

                    unique_words.emplace(word);
                }
            }

            for (const auto& subs : unique_words)
            {
                size_t count = 0;

                for (size_t j = 0; j < words.size(); j++)
                {
                    if (words[j] == subs) count += 1;
                }

                freq_dictionary[subs].emplace_back(Entry{doc_id, count});
            }
        });
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread& t)
    {
        t.join();
    });

    for (auto& i : freq_dictionary)
    {
        std::sort(i.second.begin(), i.second.end());
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
    auto it = freq_dictionary.find(word);

    if (it != freq_dictionary.end())
    {
        return freq_dictionary[word];
    }

    return{};
}

