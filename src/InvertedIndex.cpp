//
// Created by Meresse on 7/3/2022.
//

#include <algorithm>
#include <thread>
#include <sstream>
#include <string>
#include <mutex>
#include "InvertedIndex.h"

//std::mutex MUTEX;

void InvertedIndex::UpdateDocumentBase(const std::vector<std::string>& input_docs)
{
    copy(input_docs.begin(), input_docs.end(), std::back_inserter(docs));

    std::vector<std::thread> threads;

    for (size_t doc_id = 0; doc_id < docs.size(); doc_id++)
    {
        threads.emplace_back([this, doc_id]()
        {
            //MUTEX.lock();

            std::string request = docs[doc_id];

            std::istringstream iss(request);

            while (iss)
            {
                std::string subs;

                iss >> subs;

                if (!subs.empty())
                {
                    size_t count = 0;
                    size_t nPos = request.find(subs, 0);

                    while(nPos != std::string::npos)
                    {
                        if (request[nPos + subs.length()] >= 32 || request[nPos + subs.length()] <= 64) // 32 это пробель !!!
                        {
                            count += 1;
                        }

                        nPos = request.find(subs, nPos + 1);
                    }

                    Entry entry({doc_id, count});

                    std::vector<Entry>::iterator it = find(freq_dictionary[subs].begin(),freq_dictionary[subs].end(), entry);

                    if (it == freq_dictionary[subs].end())
                    {
                        freq_dictionary[subs].push_back({doc_id, count});
                    }
                }
            }
            //MUTEX.unlock();
        });
    }

    std::for_each(threads.begin(), threads.end(), [](std::thread &t)
    {
        t.join();
    });
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word)
{
    return freq_dictionary[word];
}

