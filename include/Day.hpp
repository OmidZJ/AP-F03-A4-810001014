#ifndef DAY_HPP
#define DAY_HPP

#include <vector>
#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>
using namespace std;
class Card;
class Day;
class Box;
class Day
{
public:
    void next_day();
    void reviewStatus(bool TF);
    bool isIn(const Card &element);
    int streakUpdate();
    int Total();
    int get_day();
    int get_streak();

    vector<Card> isDone;
    vector<vector<int>> history;
    bool reviewIsDone = false;
    int correctAnswers = 0;
    int wrongAnswers = 0;

private:
    int day = 1;
    int streak = 0;
};

#endif