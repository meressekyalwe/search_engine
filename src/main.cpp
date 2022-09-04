
#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"
#include <algorithm>



int main()
{
    bool running = true;

    while (running)
    {
        try
        {
            ConverterJSON converterJson;

            std::vector<std::string> docs = converterJson.GetTextDocuments();

            std::vector<std::string> requests = converterJson.GetRequests();

            InvertedIndex invertedIndex;

            invertedIndex.UpdateDocumentBase(docs);

            SearchServer searchServer(invertedIndex);

            auto results = searchServer.search(requests);

            std::vector<std::vector<std::pair<int, float>>> answers;

            for (size_t i = 0; i < results.size(); i++)
            {
                std::vector<std::pair<int, float>> answer;

                for (size_t j = 0; j < results[i].size(); j++)
                {
                    answer.push_back({(int)results[i][j].doc_id, results[i][j].rank});
                }

                answers.push_back(answer);
            }

            converterJson.putAnswers(answers);

            running = false;
        }
        catch (const std::runtime_error& error)
        {
            std::cerr << error.what() << std::endl;

            running = false;
        }
        catch (std::vector<std::string> paths)
        {
            for (const auto& i : paths)
            {
                std::cerr << "could not open file : " << i << std::endl;
            }
            running = false;
        }
    }

    return 0;
}
