#pragma once

#include "Symbol.hpp"
#include "Match.hpp"
#include "Orientation.hpp"

#include <vector>

class Rule; //forward declaration

/**
 * @brief Implements a n⨉m pattern of symbols and wildcards.
 * 
 * Note: when visiting the internal 2D symbol array, the height of the pattern
 * is the first dimension, the width of the pattern is the second dimension,
 * like when working with matrices.
 * 
 * Note: by sub-pattern we mean a region of the pattern.
 * 
 */
class Pattern {
    public:
        /**
         * @brief Construct a new Pattern object from a 2d array of symbols, its height and width.
         * 
         * @param pattern The 2d array of Symbol
         * @param height The height of the array (first dimension)
         * @param width The width of the array (second dimension)
         */
        Pattern(Symbol** pattern, int height, int width);

        /**
         * @brief Search this pattern for occurrences of pattern p.
         * 
         * @param pattern The pattern to look for.
         * @return a vector of matches representing where and in which orientation pattern occurs as a sub-pattern of this pattern.
         */
        std::vector<Match> search(Pattern pattern);

        /**
         * @brief Replaces the sub-pattern identified by position in this pattern with the provided pattern.
         * 
         * @param pattern the pattern to replace with,
         * @param position the position where to replace the sub-pattern
         * @return true if the replacement was succesful
         * @return false if the provided pattern does not fit in this pattern
         */
        bool replace(Pattern pattern, Match position);

        /**
         * @brief Search this pattern for occurrences of the sub-pattern that rule r can be applied to,
         * choose one such occurrence randomly and apply r to it.
         * 
         * @param rule the rule to apply.
         * @return true if the pattern has been changed as a result of the application of the rule
         * @return false if the rule did non match any sub-pattern of the pattern
         */
        bool apply(Rule rule);

        /**
         * @brief Print this pattern in a compact way.
         * 
         */
        void prettyPrint();

    private:
        int width, height;
        Symbol** internalPattern;

        /**
         * @brief Compare a sub-pattern of this pattern with a second pattern for equality.
         * 
         * @param pattern the pattern to compare to
         * @param vOffset the vertical offset in this pattern where the sub-pattern starts
         * @param hOffset the horizontal offset in this pattern where the sub-pattern starts
         * @param orientation the orientation of the sub-pattern 
         * @return true if this pattern's sub-pattern matches pattern
         * @return false if this pattern's sub-pattern and rhs differ in at least one symbol
         */
        bool compare(Pattern pattern, int vOffset, int hOffset, Orientation orientation);
};