#include <Utils.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
using namespace std;

Day day;
map<int, int> indexToPeriod = {{0, 1}, {1, 3}, {2, 7}, {3, 30}, {4, -1}};
vector<Box> everyBox = {Box(0), Box(1), Box(2), Box(3), Box(-1)};


vector<Card> todaysCards(int n)
{
    vector<Card> tempCard;
    int size = 0;
    for (int i = everyBox.size() - 1; i > -1; i--)
    {

        if (everyBox[i].get_period() == -1 ? 1 : day.get_day() % indexToPeriod[everyBox[i].get_period()] != 0)
            continue;
        for (auto j : everyBox[i].set)
        {
            if (size == n)
                break;
            if (!day.isIn(j))
            {
                size++;
                tempCard.push_back(j);
                day.isDone.push_back(j);
            }
        }
    }
    return tempCard;
}
void add_flashcard()
{
    string n;
    getline(cin, n);
    string q, a;

    for (int i = 0; i < stoi(n); i++)
    {
        getline(cin, q);
        getline(cin, a);
        everyBox[0].add(Card(q, a));
    }
    cout << "flashcards added to the daily box" << endl;
}
void review_today()
{
    string n;
    getline(cin, n);
    day.reviewIsDone = true;

    string temp;
    vector<Card> tempCard = todaysCards(stoi(n));
    for (auto i : tempCard)
    {
        cout << "Flashcard: " << i.get_question() << endl;
        cout << "Your answer: ";

        getline(cin, temp);
        cout << endl;
        cout << i.get_answer() << temp << endl;

        if (temp == i.get_answer())
        {
            Card j = i;
            Card jj = i;
            j.fault = 0;
            jj.box++;
            everyBox[jj.box].set.push_back(jj);
            everyBox[j.box].set.erase(everyBox[j.box].set.begin() + everyBox[j.box].find(j));

            cout << "Your answer was correct! Well done, keep it up!" << endl;
            day.correctAnswers++;
        }
        else
        {
            if (i.box > 0 && i.fault == 1)
            {
                Card j = i;
                Card jj = i;
                jj.fault = 0;
                jj.box--;
                everyBox[jj.box].set.push_back(jj);
                everyBox[j.box].set.erase(everyBox[j.box].set.begin() + everyBox[j.box].find(j));
            }
            else
                everyBox[i.box].set[everyBox[i.box].find(i)].fault++;

            cout << "Your answer was incorrect. Don't worry! The correct answer is: " << i.get_answer() << ". Keep practicing!" << endl;
            day.wrongAnswers++;
        }
    }

    cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
}
void get_report()
{
    string inputLine;

    getline(cin, inputLine);

    int value1, value2 = day.get_day();

    stringstream ss(inputLine);
    ss >> value1;
    ss >> value2;

    cout << "Day: " << value1 << " to " << value2 << endl;

    int corrects = 0;
    int mistakes = 0;

    for (int i = value1 - 1; i < value2 - 1; i++)
    {
        corrects += day.history[i][0];
        mistakes += day.history[i][1];
    }
    if (value2 == day.get_day())
    {
        corrects += day.correctAnswers;
        mistakes += day.wrongAnswers;
    }
    else
    {
        corrects += day.history[value2 - 1][0];
        mistakes += day.history[value2 - 1][1];
    }

    cout << "Correct Answers: " << corrects << endl;
    cout << "Incorrect Answers: " << mistakes << endl;
    cout << "Total: " << corrects + mistakes << endl;
}
void get_progress_report()
{
    cout << "Challenge Progress Report:\n"
         << endl;
    cout << "Day of the Challenge: " << day.get_day() << endl;
    cout << "Streak: " << day.streakUpdate() << endl;
    cout << "Total Days Participated: " << day.Total() << endl;
    cout << "Mastered Flashcards: " << everyBox[4].set.size() << "\n"
         << endl;
    cout << "Keep up the great work! You're making steady progress toward mastering your flashcards." << endl;
}
void streak()
{

    cout << "Your current streak is: " << day.streakUpdate() << endl;
    cout << "Keep going!" << endl;
}
void next_day()
{
    day.next_day();
    cout << "Good morning! Today is day " << day.get_day() << " of our journey." << endl;
    cout << "Your current streak is: " << day.get_streak() << endl;
    cout << "Start reviewing to keep your streak!" << endl;
}
