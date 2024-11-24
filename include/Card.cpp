#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>
#include <iostream>
#include <string>
using namespace std;

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
