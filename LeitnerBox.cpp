#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <map>
using namespace std;

map<int, int> translate = {{1, 0}, {3, 1}, {7, 2}, {30, 3}, {-1, -1}};
map<int, int> translateReversed = {{0, 1}, {1, 3}, {2, 7}, {3, 30}, {4, -1}};
class card;
class Day
{
public:
    int day = 1;
    int streak = 0;
    void next_day();
    void reviewStatus(bool TF);
    int correctAnswers = 0;
    int wrongAnswers = 0;
    bool isReview = false;
    vector<vector<int>> history;
    vector<card> isDone;
    bool isIn(const card &element);
    int streakUpdate();
    int Total();

private:
};
class card
{
public:
    card(string q, string a);
    void print();
    string question;
    string answer;
    int box;
    int fault = 0;
    bool operator==(const card &other) const
    {
        return (question == other.question && answer == other.answer);
    }

private:
};
void Day::next_day()
{
    if (isReview)
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
        isReview = true;
    else
        isReview = false;
}
bool Day::isIn(const card &element)
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

Day day;

int Day::Total()
{
    int total = 0;
    for (auto i : history)
    {
        if (i != vector<int>{0, 0})
            total++;
    }
    if (isReview)
        return total + 1;
    return total;
}
int Day::streakUpdate()
{
    if (isReview)
    {
        return streak + 1;
    }
    return streak;
}
card::card(string q, string a)
{
    question = q;
    answer = a;
    box = 0;
}

void card::print()
{
    cout << question << '/' << '/' << answer << endl;
}

class box
{
public:
    box(int p);
    void add(card c);
    vector<card> set;
    int period;

private:
};

box::box(int p)
{
    period = p;
}

void box::add(card c)
{
    set.push_back(c);
}

vector<box> everyBox = {box(0), box(1), box(2), box(3), box(-1)};

void print()
{
    for (auto i : everyBox)
    {
        cout << i.period << endl;
        for (auto j : i.set)
        {
            j.print();
        }
    }
}

int find(int temp, card element)
{
    for (int i = 0; i < everyBox[temp].set.size(); i++)
    {
        if (element == everyBox[temp].set[i])
        {

            return i;
        }
    }
    return -1;
}
void add_flashcard()
{
    int n;
    cin >> n;
    string q, a;

    for (int i = 0; i < n; i++)
    {
        cin >> q;
        cin >> a;
        everyBox[0].add(card(q, a));
    }
    cout << "flashcards added to the daily box" << endl;
}
vector<card> todaysCards(int n)
{
    vector<card> tempCard;
    int size = 0;
    for (int i = everyBox.size() - 1; i > -1; i--)
    {

        if (everyBox[i].period == -1 ? 1 : day.day % translateReversed[everyBox[i].period] != 0)
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
void review_today()
{
    int n;
    cin >> n;
    day.isReview = true;

    string temp;
    vector<card> tempCard = todaysCards(n);
    for (auto i : tempCard)
    {
        cout << i.question << endl;
        cout << "Your answer: ";
        cin >> temp;
        if (temp == i.answer)
        {
            card j = i;
            card jj = i;
            j.fault = 0;
            jj.box++;
            everyBox[jj.box].set.push_back(jj);
            everyBox[j.box].set.erase(everyBox[j.box].set.begin() + find(j.box, j));

            cout << "Your answer was correct! Well done, keep it up!" << endl;
            day.correctAnswers++;
        }
        else
        {
            if (i.box > 0 && i.fault == 1)
            {
                card j = i;
                card jj = i;
                jj.fault = 0;
                jj.box--;
                everyBox[jj.box].set.push_back(jj);
                everyBox[j.box].set.erase(everyBox[j.box].set.begin() + find(j.box, j));
            }
            else
                everyBox[i.box].set[find(i.box, i)].fault++;

            cout << "Your answer was incorrect. Don't worry! The correct answer is: " << i.answer << ". Keep practicing!" << endl;
            day.wrongAnswers++;
        }
    }

    cout << "You’ve completed today’s review! Keep the momentum going and continue building your knowledge, one flashcard at a time!" << endl;
}
void get_report()
{
    string inputLine;

    getline(cin, inputLine);

    int value1, value2 = day.day;

    stringstream ss(inputLine);
    ss >> value1;
    ss >> value2;

    cout << "Day: " << value1 << " to " << value2 << endl;

    int corrects = 0;
    int mistakes = 0;

    for (auto i : day.history)
    {
        cout << i[0] << " " << i[1] << endl;
    }
    for (int i = value1 - 1; i < value2 - 1; i++)
    {
        corrects += day.history[i][0];
        mistakes += day.history[i][1];
    }
    if (value2 == day.day)
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
    cout << "Day of the Challenge: " << day.day << endl;
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
    cout << "Good morning! Today is day " << day.day << " of our journey." << endl;
    cout << "Your current streak is: " << day.streak << endl;
    cout << "Start reviewing to keep your streak!" << endl;
}
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
    {
        if (commands.find(command) != commands.end())
        {
            commands[command]();
        }
        else
        {
        }
        print();
    }

    return 0;
}