//
// Created by Meresse on 5/21/2022.
//
#include "ConverterJSON.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <exception>

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
    std::ifstream ifstr("C:\\Users\\Meresse\\Downloads\\search_engine-master\\search_engine-master\\JsonFiles\\config.json");

    if (ifstr.is_open())
    {
        nlohmann::json json;
        ifstr >> json;

        if (!json.contains("config"))
        {
            throw std::runtime_error("config file is empty!");
        }
        else if (version != json["config"]["version"])
        {
            throw std::runtime_error("config.json has incorrect file version");
        }
        if (!json.contains("files"))
        {
            throw std::runtime_error("file paths does not exist!");
        }

        std::string str;
        std::vector<std::string> textDocuments;
        std::vector<std::string> paths;

        size_t number_of_files =  json["files"].size();

        for (size_t i = 0; i < number_of_files; i++)
        {
            std::string doc;

            std::string filename = json["files"][i];

            std::ifstream file(filename);

            if (file.is_open())
            {
                while(!file.eof())
                {
                    file >> str;

                    doc += (str + " ");
                }
            }
            else
            {
                paths.push_back(json["files"][i]);
            }

            file.close();

            textDocuments.push_back(doc);
        }
        if (!paths.empty())
        {
            throw paths;
        }

        return textDocuments;
    }
    else
    {
        throw std::runtime_error("config file don not opened!");
    }
    return {};
}

int ConverterJSON::GetResponsesLimit()
{
    std::ifstream ifstr("C:\\Users\\Meresse\\Downloads\\search_engine-master\\search_engine-master\\JsonFiles\\config.json");

    if (ifstr.is_open())
    {
        nlohmann::json config;
        ifstr >> config;
        return config["config"]["max_responses"];
    }
    return{};
}

std::vector<std::string> ConverterJSON::GetRequests()
{
    std::ifstream ifstr("C:\\Users\\Meresse\\Downloads\\search_engine-master\\search_engine-master\\JsonFiles\\requests.json");

    if (ifstr.is_open())
    {
        std::vector<std::string> requests;
        nlohmann::json json;
        ifstr >> json;


        for (auto & i : json["requests"])
        {
            std::string request = i;

            requests.push_back(request);
        }

        return requests;
    }
    else
    {
        throw std::runtime_error("requests do not opened!");
    }
    return {};
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
    std::ofstream ofstr("C:\\Users\\Meresse\\Downloads\\search_engine-master\\search_engine-master\\JsonFiles\\answers.json");

    if (ofstr.is_open())
    {
        auto requests = GetRequests();
        nlohmann::json json;

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

        ofstr << json.dump(answers.size());

    }
}
