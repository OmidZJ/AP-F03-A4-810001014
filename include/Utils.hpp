#ifndef UTILS_HPP
#define UTILS_HPP
#include <map>
#include <string>
#include <vector>
#include <Box.hpp>
#include <Card.hpp>
#include <Day.hpp>
using namespace std;

extern Day day;
extern map<int, int> indexToPeriod;
extern vector<Box> everyBox;

vector<Card> todaysCards(int n);
void add_flashcard();
void review_today();
void get_report();
void get_progress_report();
void streak();
void next_day();

#endif