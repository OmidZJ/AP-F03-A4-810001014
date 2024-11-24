#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>

#include <iostream>
#include <string>
using namespace std;

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
