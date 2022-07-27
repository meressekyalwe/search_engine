//
// Created by Meresse on 5/21/2022.
//

#include <fstream>
#include <nlohmann/json.hpp>
#include "ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream ifstr("../JsonFiles/config.json");
    nlohmann::json json;
    ifstr >> json;
    std::string str;
    std::vector<std::string> textDocuments;

    size_t number_of_files =  json["files"].size();

    for (size_t i = 0; i < number_of_files; i++)
    {
        std::string doc;

        std::ifstream file(json["files"][i]);

        if (file.is_open())
        {
            while(!file.eof())
            {
                file >> str;

                doc += (str + " ");
            }
        }

        textDocuments.push_back(doc);
    }

    return textDocuments;
}

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream ifstr("../JsonFiles/config.json");
    nlohmann::json config;
    ifstr >> config;

    return config["config"]["max_responses"];
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::vector<std::string> requests;
    std::ifstream ifstr("../JsonFiles/requests.json");
    nlohmann::json json;
    ifstr >> json;


    for (auto & i : json["requests"])
    {
        std::string request = i;

        requests.push_back(request);
    }

    return requests;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    auto requests = GetRequests();
    nlohmann::json json;
    std::ofstream ofstr("../JsonFiles/answers.json");

    for (size_t i = 0; i < answers.size(); i++)
    {
        if (!answers[i].empty())
        {
            json["answers"]["request" + std::to_string(i + 1)]["result"] = true;

            for (size_t j = 0; j < answers[i].size(); j++)
            {
                json["answers"]["request" + std::to_string(i + 1)]["relevance"].push_back({{"doc_id", answers[i][j].first}, {"rank" , answers[i][j].second}});
            }

        } else
        {
            json["answers"]["request" + std::to_string(i + 1)]["result"] = false;
        }
    }

    ofstr << json;
}
