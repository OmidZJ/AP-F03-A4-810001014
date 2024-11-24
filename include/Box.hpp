#ifndef BOX_HPP
#define BOX_HPP

#include <vector>
#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>
using namespace std;
class Card;
class Day;
class Box;

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

#endif
