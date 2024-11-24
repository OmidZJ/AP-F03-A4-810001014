#ifndef CARD_HPP
#define CARD_HPP

#include <string>
#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>
using namespace std;

class Card;
class Day;
class Box;

class Card
{
public:
    Card(string q, string a);
    void print();
    bool operator==(const Card &other) const
    {
        return (question == other.question && answer == other.answer);
    }
    string get_question();
    string get_answer();

    int box;
    int fault = 0;

private:
    string question;
    string answer;
};

#endif