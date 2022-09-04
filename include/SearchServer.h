//
// Created by Meresse on 7/4/2022.
//

#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include "InvertedIndex.h"

struct RelativeIndex
{
    size_t doc_id;
    float rank;

    bool operator == (const RelativeIndex& other) const
    {
        return (doc_id == other.doc_id && rank == other.rank);
    }

    bool operator < (const RelativeIndex& other) const // operateur pour ranger par ordre de rank // для сравнения RelativeIndex rank
    {
        return (rank < other.rank);
    }
};


class SearchServer
{
public:
    /**
    * @param idx в конструктор класса передаётся ссылка на класс InvertedIndex,
    * чтобы SearchServer мог узнать частоту слов встречаемых в запросе
    */
    SearchServer(InvertedIndex& idx) : _index(idx){ };
    /**
    * Метод обработки поисковых запросов
    * @param queries_input поисковые запросы взятые из файла requests.json
    * @return возвращает отсортированный список релевантных ответов для заданных запросов
    */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:

    InvertedIndex _index;
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
