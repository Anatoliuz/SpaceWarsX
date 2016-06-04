#ifndef MYFUNCTION_H
#define MYFUNCTION_H

#include <string>
#include <stdlib.h>
#include <iostream>
#include <iterator>
#include <assert.h>

using std::cout;
using std::string;

int strtoInt (const string& str, int pos = 0, const string& delim = "");
bool checkCommand (const string& commands, const string delim);

//tempalate functions



template <class T>  // работает для контейнеров типа vector<string>, list<string>  и т.п
                    // должны быть функции push_back
void separate (const string& str, string delim, T& commands)
{
   // assert
    if (checkCommand(str, delim)) { // входящая строка не должна быть пустой, т.к это ошибка на стороне сервера
                          // сервер тоже должен проверять не пустоту ли он посылает
//    assert(comands != nullptr); // очередь должна существовать
    assert(!delim.empty());
    string temp;
//    string delim = "||"; // разделитель команд, можно задать в общем виде


    int begin  = str.find(delim) + delim.length();; // начало подстроки-команды
    int len    = str.find(delim, begin) - begin;; // длина подстроки-команды
    // последняя позиция разделителя, подстроки кончатся, если начало новой команды это последний разделитель
    int size = str.length();
    while (begin < size) { // чтобы не делать strlen в цикле
        temp  = str.substr(begin, len);
        commands.push_back(temp);
        begin = str.find(delim, begin) + delim.length(); // смещение на длину разделитея, чтобы begin указывал на 1ый символ подстроки
        len   = str.find(delim, begin) - begin; // смещение на 1 символ назад, чтобы end указывал на последний символ подстроки
    }


    }
}

template <class T> // выводит объекты, которые могут быть выведены cout
void printContainer(T& container)
{
    cout << "\n";
    class T::iterator begin = container.begin();
    while (begin != container.end()) {
        cout << *begin++ << "\n";
    }
}


#endif // MYFUNCTION_H
