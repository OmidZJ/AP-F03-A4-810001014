#include "Day.hpp"
#include <iostream>
using namespace std;

void Day::next_day()
{
    if (reviewIsDone)
        streak++;
    else
        streak = 0;
    history.push_back({correctAnswers, wrongAnswers});
    correctAnswers = 0;
    wrongAnswers = 0;
    isDone = {};

    day++;
    reviewStatus(false);
}
void Day::reviewStatus(bool TF)
{
    if (TF)
        reviewIsDone = true;
    else
        reviewIsDone = false;
}
bool Day::isIn(const Card &element)
{
    for (int i = 0; i < isDone.size(); i++)
    {
        if (element == isDone[i])
        {

            return true;
        }
    }
    return false;
}
int Day::Total()
{
    int total = 0;
    for (auto i : history)
    {
        if (i != vector<int>{0, 0})
            total++;
    }
    if (reviewIsDone)
        return total + 1;
    return total;
}
int Day::streakUpdate()
{
    if (reviewIsDone)
    {
        return streak + 1;
    }
    return streak;
}
int Day::get_day()
{
    return day;
}
int Day::get_streak()
{
    return streak;
}