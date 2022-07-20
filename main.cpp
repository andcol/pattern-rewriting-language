#include <iostream>

#include "Rule.hpp"

#include "program3.cpp" //"Program to load (cpp file with rule and field objects)"

uint64_t timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

int main(int, char**) {
    srand(time(NULL)); //Initialize RNG
    Pattern field = start; //Initialize field
    int ruleIndex = 0; //Start with the first rule

    field.prettyPrint(); //show initial state

    uint64_t before = timeSinceEpochMillisec();

    while(ruleIndex < numberOfRules) {
        if (field.apply(ruleSet[ruleIndex])) {
            //If a rule applies successfully, return to the top of the ruleset and continue
            //field.prettyPrint(); //show new state
            ruleIndex = 0;
            continue;
        } else {
            //Otherwise we check the next rule
            ruleIndex++;
        }
    }

    uint64_t delay = timeSinceEpochMillisec() - before;
    std::cout << "Done in " << std::to_string(delay) << "ms" << std::endl;

    field.prettyPrint();
}