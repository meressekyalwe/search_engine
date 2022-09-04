# search_engine


Описание проекта

Представьте, что вы пришли в отдел разработки программного обеспечения недавно
созданного информационно-новостного портала, на котором каждый день выходят
новости о событиях в мире и статьи разных авторов. Руководитель поручил вам
реализацию собственного поискового движка, который поможет осуществлять поиск
среди набора документов.
Существующие поисковые движки ваши коллеги уже попробовали. Лучшим из них был
ресурс от Яндекса, который можно было установить на своём сервере и использовать
для поиска по своему набору документов. Но он перестал существовать как отдельный
сервис. Ваше руководство решило реализовать собственный поиск, алгоритм и
принципы работы которого при необходимости можно менять и развивать.
Поисковый движок должен представлять из себя консольное приложение
(исполняемый файл, запускаемый на любом сервере или компьютере),
осуществляющее поиск и имеющее возможность настройки через файлы формата
JSON. Применённые в нём решения можно впоследствии встроить в поисковый
движок работающий на веб.
________________________________________________________________________________

Принципы работы поискового движка 

1. В конфигурационном файле config.json перед запуском приложения задаются названия
файлов, по которым движок будет осуществлять поиск.
2. Поисковый движок самостоятельно обходить все файлы и
индексировать их так, чтобы потом по любому поисковому запросу находить наиболее
релевантные документы.
3. Пользователь задаёт запрос через JSON-файл requests.json. Запрос — это
набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
максимальное количество возможных документов в ответе задаётся в
конфигурационном файле.
7. В конце программа формирует файл answers.json, в который записывает
результаты поиска.
___________________________________________________________________________________

Используемые технологии

    C++
    JSON
    Google Test
    многопоточность
____________________________________________________________________________________

Сборка и запуск

CMAKE 3.14

MinGW (раскоментировать set(gtest_disable_pthreads on) в tests\CMakeLists.txt), MSVC

Windows
____________________________________________________________________________________

Тесты

Подключена библиотека Google Test для проведения автоматических модульных тестов 
(в папке tests).

Чтобы убедиться, что класс InvertedIndex правильно заполняет коллекцию
freq_dicitonary, предлагается использовать тестов в файле InvertedIndex_test.cpp.

Чтобы убедиться, что приложение правильно рассчитывает абсолютную и
относительную релевантность, предлагается использовать тестов написаны в файле 
SearchServer_test.cpp.




