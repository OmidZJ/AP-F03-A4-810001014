#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
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

class Box
{
public:
    Box(int p);
    void add(Card c);
    int find(Card element);
    int get_period();

    vector<Card> set;

private:
    int period;
};

Day day;
map<int, int> indexToPeriod = {{0, 1}, {1, 3}, {2, 7}, {3, 30}, {4, -1}};
vector<Box> everyBox = {Box(0), Box(1), Box(2), Box(3), Box(-1)};

vector<Card> todaysCards(int n);
void add_flashcard();
void review_today();
void get_report();
void get_progress_report();
void streak();
void next_day();

int main()
{

    map<string, void (*)()> commands = {
        {"add_flashcard", add_flashcard},
        {"review_today", review_today},
        {"get_report", get_report},
        {"get_progress_report", get_progress_report},
        {"streak", streak},
        {"next_day", next_day}};

    string command;

    while (cin >> command)
        if (commands.find(command) != commands.end())
            commands[command]();

    return 0;
}

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

Card::Card(string q, string a)
{
    question = q;
    answer = a;
    box = 0;
}
void Card::print()
{
    cout << question << '/' << '/' << answer << endl;
}
string Card::get_question()
{
    return question;
}
string Card::get_answer()
{
    return answer;
}

Box::Box(int p)
{
    period = p;
}
void Box::add(Card c)
{
    set.push_back(c);
}
int Box::find(Card element)
{
    for (int i = 0; i < set.size(); i++)
    {
        if (element == set[i])
        {

            return i;
        }
    }
    return -1;
}
int Box::get_period()
{
    return period;
}

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
