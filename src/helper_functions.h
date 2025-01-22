/*
************************************************************
* Name:  Samman Bhetwal                                    *
* Project:  1 yahtzee                                      *
* Class:  CMPS-366                                         *
* Date:  10/26/2024                                        *
*****************************************************************
*/
#pragma once

#include <vector>
#include <algorithm>
#include <map>
#include <random>
#include <sstream>

using namespace std;

/************************************************************
Function Name: all_same
Purpose: To check if all elements in a vector are identical.
Parameters:
            v, a vector of integers passed by reference. It holds values to check for uniformity.
Return Value: A boolean indicating if all elements in the vector are the same.
Algorithm:
            1) Loop through elements in the vector.
            2) Compare each element with the first one; return false if any element differs.
            3) If all elements match, return true.
Reference: none
************************************************************/
inline bool all_same(const vector<int> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i] != v[0])
        {
            return false;
        }
    }
    return true;
}


/************************************************************
Function Name: all_sequence
Purpose: To check if the elements in a vector form a consecutive sequence.
Parameters:
            v, a vector of integers passed by reference. It holds values to check for a sequence.
Return Value: A boolean indicating if the vector elements form a sequence.
Algorithm:
            1) Sort the vector to organize elements in ascending order.
            2) Loop through the sorted vector, comparing each element with the previous one.
            3) If all elements increase consecutively by 1, return true; otherwise, return false.
Reference: none
************************************************************/
inline bool all_sequence(const vector<int> &v)
{
    vector<int> sorted_v = v;
    sort(sorted_v.begin(), sorted_v.end());
    for (int i = 1; i < sorted_v.size(); i++)
    {
        if (sorted_v[i] != sorted_v[i - 1] + 1)
        {
            return false;
        }
    }
    return true;
}


/************************************************************
Function Name: contains_sequence
Purpose: To check if a vector contains a sequence of a specified length.
Parameters:
            v, a vector of integers passed by reference. It holds values to be checked for sequences.
            sequence_length, an integer. Specifies the length of the desired sequence.
Return Value: A boolean indicating whether a sequence of the given length exists.
Algorithm:
            1) Loop through vector to extract sub-vectors of the specified length.
            2) For each sub-vector, check if it forms a consecutive sequence.
            3) Return true if a sequence of the specified length is found; otherwise, return false.
Reference: none
************************************************************/
inline bool contains_sequence(const vector<int> &v, int sequence_length)
{
    int length = sequence_length;
    if (v.size() < length)
    {
        return false;
    }
    for (int i = 0; i < v.size() - length + 1; i++)
    {
        vector<int> sub_v(v.begin() + i, v.begin() + i + length);
        if (all_sequence(sub_v))
        {
            return true;
        }
    }
    return false;
}


/************************************************************
Function Name: five_sequence
Purpose: To check if the vector contains a sequence of exactly 5 consecutive numbers.
Parameters:
            v, a vector of integers passed by reference. It holds values to be checked.
Return Value: A boolean indicating whether a 5-number sequence exists in the vector.
Algorithm:
            1) Use contains_sequence to search for a 5-number sequence in the vector.
            2) Return the result.
Reference: none
************************************************************/
inline bool five_sequence(const vector<int> &v)
{
    return contains_sequence(v, 5);
}


/************************************************************
Function Name: four_sequence
Purpose: To check if the vector contains a sequence of exactly 4 consecutive numbers.
Parameters:
            v, a vector of integers passed by reference. It holds values to be checked.
Return Value: A boolean indicating whether a 4-number sequence exists in the vector.
Algorithm:
            1) Use contains_sequence to search for a 4-number sequence in the vector.
            2) Return the result.
Reference: none
************************************************************/
inline bool four_sequence(const vector<int> &v)
{
    return contains_sequence(v, 4);
}


/************************************************************
Function Name: atleast_n_same
Purpose: To check if the vector contains at least 'n' occurrences of any single number.
Parameters:
            v, a vector of integers passed by reference. It holds values to check for occurrences.
            n, an integer. Specifies the minimum number of occurrences needed.
Return Value: A boolean indicating if any number appears at least 'n' times.
Algorithm:
            1) Create a map to count occurrences of each number.
            2) Loop through the vector, updating counts in the map.
            3) Check if any number has a count of 'n' or greater; return true if found.
            4) Otherwise, return false.
Reference: none
************************************************************/
inline bool atleast_n_same(const vector<int> &v, int n)
{
    map<int, int> counts;
    for (int i : v)
    {
        counts[i]++;
    }
    for (auto const &entry : counts)
    {
        if (entry.second >= n)
        {
            return true;
        }
    }
    return false;
}


/* *********************************************************************
Function Name: atleast_four_same
Purpose: To check if there are at least 4 occurrences of the same number in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: True if there are 4 or more of the same number, false otherwise
Algorithm:
            1) Calls the atleast_n_same function with 4 as the desired count
Reference: none
********************************************************************* */
inline bool atleast_four_same(const vector<int> &v)
{
    return atleast_n_same(v, 4);
}


/* *********************************************************************
Function Name: atleast_three_same
Purpose: To check if there are at least 3 occurrences of the same number in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: True if there are 3 or more of the same number, false otherwise
Algorithm:
            1) Calls the atleast_n_same function with 3 as the desired count
Reference: none
********************************************************************* */
inline bool atleast_three_same(const vector<int> &v)
{
    return atleast_n_same(v, 3);
}


/* *********************************************************************
Function Name: contains_n
Purpose: To check if a given number exists in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
            n, an integer. It represents the number to check for in the vector
Return Value: True if the vector contains the number n, false otherwise
Algorithm:
            1) Loop through the vector
            2) Return true if n is found in the vector, false if not
Reference: none
********************************************************************* */
inline bool contains_n(const vector<int> &v, int n)
{
    for (int i : v)
    {
        if (i == n)
        {
            return true;
        }
    }
    return false;
}


/* *********************************************************************
Function Name: get_sequence
Purpose: To find the first sequence of a specified length in a vector of integers
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
            sequence_length, an integer. It represents the desired sequence length
Return Value: A vector containing the found sequence, or an empty vector if not found
Algorithm:
            1) Sort the vector
            2) Loop through elements, creating sub-vectors of length sequence_length
            3) Check if each sub-vector is a sequence
Reference: none
********************************************************************* */
inline vector<int> get_sequence(vector<int> &v, int sequence_length)
{
    vector<int> sorted_v = v;
    sort(sorted_v.begin(), sorted_v.end());
    for (int i = 0; i < sorted_v.size() - sequence_length + 1; i++)
    {
        vector<int> sub_v(sorted_v.begin() + i, sorted_v.begin() + i + sequence_length);
        if (all_sequence(sub_v))
        {
            return sub_v;
        }
    }
    return {};
}


/* *********************************************************************
Function Name: sum
Purpose: To calculate the sum of all elements in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: The total sum of elements in the vector, an integer
Algorithm:
            1) Initialize total to 0
            2) Add each element in the vector to total
Reference: none
********************************************************************* */
inline int sum(const vector<int> &v)
{
    int total = 0;
    for (int i : v)
    {
        total += i;
    }
    return total;
}


/* *********************************************************************
Function Name: count_n
Purpose: To count how many times a specified number appears in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
            n, an integer. It represents the number to count in the vector
Return Value: The count of occurrences of n in the vector, an integer
Algorithm:
            1) Loop through the vector
            2) Increment the total for each match with n
Reference: none
********************************************************************* */
inline int count_n(const vector<int> &v, int n)
{
    int total = 0;
    for (int i : v)
    {
        if (i == n)
        {
            total++;
        }
    }
    return total;
}


/* *********************************************************************
Function Name: get_unique
Purpose: To create a vector containing unique elements from the input vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: A vector of unique integers from v
Algorithm:
            1) Loop through each element
            2) Add element to unique vector if it is not already present
Reference: none
********************************************************************* */
inline vector<int> get_unique(const vector<int> &v)
{
    vector<int> unique_v;
    for (int i : v)
    {
        if (find(unique_v.begin(), unique_v.end(), i) == unique_v.end())
        {
            unique_v.push_back(i);
        }
    }
    return unique_v;
}


/* *********************************************************************
Function Name: count_unique
Purpose: To count the number of unique elements in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: The number of unique elements, an integer
Algorithm:
            1) Call get_unique function
            2) Return size of resulting unique vector
Reference: none
********************************************************************* */
inline int count_unique(const vector<int> &v)
{
    return get_unique(v).size();
}


/* *********************************************************************
Function Name: max_count
Purpose: To find the highest frequency of any number in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: The maximum frequency of any number in the vector, an integer
Algorithm:
            1) Count occurrences of each element using a map
            2) Find the highest frequency in the map
Reference: none
********************************************************************* */
inline int max_count(const vector<int> &v)
{
    map<int, int> counts;
    for (int i : v)
    {
        counts[i]++;
    }
    int max = 0;
    for (auto const &entry : counts)
    {
        if (entry.second > max)
        {
            max = entry.second;
        }
    }
    return max;
}


/* *********************************************************************
Function Name: num_repeats
Purpose: To calculate the total number of repeated elements in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: The count of repeated elements, an integer
Algorithm:
            1) Count occurrences using a map
            2) Sum up counts for elements that appear more than once
Reference: none
********************************************************************* */
inline int num_repeats(const vector<int> &v)
{
    map<int, int> counts;
    for (int i : v)
    {
        counts[i]++;
    }
    int total = 0;
    for (auto const &entry : counts)
    {
        if (entry.second > 1)
        {
            total += entry.second - 1;
        }
    }
    return total;
}


/* *********************************************************************
Function Name: longest_sequence_length
Purpose: To find the length of the longest sequence of consecutive numbers in the vector
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: The length of the longest consecutive sequence, an integer
Algorithm:
            1) Sort unique elements
            2) Count the length of consecutive sequences and keep track of longest
Reference: none
********************************************************************* */
inline int longest_sequence_length(const vector<int> &v)
{
    if (v.empty())
    {
        return 0;
    }

    int longest = 0;
    int current = 1; // Initialize current to 1 for the first element
    vector<int> sorted_v = get_unique(v);
    sort(sorted_v.begin(), sorted_v.end());

    for (int i = 1; i < sorted_v.size(); i++)
    {
        if (sorted_v[i] == sorted_v[i - 1] + 1)
        {
            current++;
        }
        else
        {
            longest = std::max(longest, current);
            current = 1;
        }
    }

    longest = std::max(longest, current); // Compare current with longest after the loop
    return longest;
}


/* *********************************************************************
Function Name: full_house
Purpose: To check if the vector represents a full house (3 of one number, 2 of another)
Parameters:
            v, a vector of integers passed by reference. It holds the dice values
Return Value: True if full house is found, false otherwise
Algorithm:
            1) Count occurrences of each element using a map
            2) Check if any counts match full house pattern (3 and 2)
Reference: none
********************************************************************* */
inline bool full_house(const vector<int> &v)
{
    map<int, int> counts;
    for (int i : v)
    {
        counts[i]++;
    }
    bool has_two = false;
    bool has_three = false;
    for (auto const &entry : counts)
    {
        if (entry.second == 2)
        {
            has_two = true;
        }
        else if (entry.second == 3)
        {
            has_three = true;
        }
    }
    return has_two && has_three;
}


/* *********************************************************************
Function Name: split
Purpose: To split a string into tokens based on a delimiter
Parameters:
            s, a string passed by reference. It is the string to split
            delimiter, a character. It is the delimiter to use for splitting
Return Value: A vector of strings containing split tokens
Algorithm:
            1) Use stringstream and getline to split string into tokens
Reference: none
********************************************************************* */
inline vector<string> split(const string &s, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}


/* *********************************************************************
Function Name: join
Purpose: To join a vector of strings into a single string with a delimiter
Parameters:
            v, a vector of strings passed by reference. It contains strings to join
            delimiter, a character passed by reference. It is used between strings
Return Value: A single string with all vector elements joined by the delimiter
Algorithm:
            1) Append each string in vector to result with delimiter in between
Reference: none
********************************************************************* */
inline string join(const vector<string> &v, const char &delimiter)
{
    string result;
    for (int i = 0; i < v.size(); i++)
    {
        result += v[i];
        if (i != v.size() - 1)
        {
            result += delimiter;
        }
    }
    return result;
}


/* *********************************************************************
Function Name: trim
Purpose: To trim whitespace from both ends of a string
Parameters:
            s, a string passed by reference. It is the string to trim
Return Value: The trimmed string
Algorithm:
            1) Use find_if and erase to remove whitespace from start and end
Reference: none
********************************************************************* */
inline string trim(const string &s)
{
    string result = s;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](int ch)
                                         { return !isspace(ch); }));
    result.erase(find_if(result.rbegin(), result.rend(), [](int ch)
                         { return !isspace(ch); })
                     .base(),
                 result.end());
    return result;
}


/* *********************************************************************
Function Name: get_dice_permutation
Purpose: To generate all possible combinations of dice values for a given number of dice
Parameters:
            num_dice, an integer. It represents the number of dice
Return Value: A vector of vectors containing all possible dice value combinations
Algorithm:
            1) Generate all combinations of numbers from 1 to 6, repeated num_dice times
Reference: none
********************************************************************* */
inline vector<vector<int>> get_dice_permutation(int num_dice)
{
    vector<vector<int>> combinations;
    vector<int> combination;
    for (int i = 1; i <= 6; i++)
    {
        combination.push_back(i);
        combinations.push_back(combination);
        combination.pop_back();
    }

    for (int i = 1; i < num_dice; i++)
    {
        vector<vector<int>> new_combinations;
        for (const vector<int> &c : combinations)
        {
            for (int j = 1; j <= 6; j++)
            {
                vector<int> new_combination = c;
                new_combination.push_back(j);
                new_combinations.push_back(new_combination);
            }
        }
        combinations = new_combinations;
    }

    return combinations;
}


/* *********************************************************************
Function Name: generate_combinations
Purpose: To recursively generate combinations of dice values
Parameters:
            n, an integer. It is the number of remaining dice to add
            start, an integer. It represents the starting dice value
            current, a vector of integers passed by reference. Holds the current combination
            result, a vector of vector<int> passed by reference. Holds all combinations
Return Value: none
Algorithm:
            1) Base case: Add current combination to result
            2) Recursive case: Generate dice values for remaining dice
Reference: none
********************************************************************* */
inline void generate_combinations(int n, int start, vector<int> &current, vector<vector<int>> &result)
{
    if (n == 0)
    {
        // If n dice have been "rolled", add the current combination to the result
        result.push_back(current);
        return;
    }

    // Loop through possible values for the dice (1 to 6)
    for (int i = start; i <= 6; ++i)
    {
        current.push_back(i);
        // Recursively generate combinations for the remaining n-1 dice
        generate_combinations(n - 1, i, current, result);
        // Backtrack and remove the last dice to explore other possibilities
        current.pop_back();
    }
}


/* *********************************************************************
Function Name: dice_combinations
Purpose: To generate all possible combinations of dice rolls for a given
         number of dice
Parameters:
            n, an integer passed by value. It represents the number of
            dice to consider for combinations
Return Value: A vector of vectors, where each inner vector represents a
              unique dice roll combination
Algorithm:
            1) Create an empty vector to hold current combinations and
               another for the final result
            2) Use the helper function generate_combinations to recursively
               add each combination to the result
Reference: none
********************************************************************* */
inline vector<vector<int>> dice_combinations(int n)
{
    vector<vector<int>> result;
    vector<int> current;
    generate_combinations(n, 1, current, result);
    return result;
}


/* *********************************************************************
Function Name: random_bool
Purpose: To generate a random boolean value
Parameters: none
Return Value: A boolean value that is either true or false
Algorithm:
            1) Use random_device and uniform distribution to return 0 or 1
Reference: none
********************************************************************* */
inline bool random_bool()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    return dis(gen);
}


/* *********************************************************************
Function Name: reversed
Purpose: To create a reversed version of a vector
Parameters:
            v, a vector passed by reference. It is the vector to reverse
Return Value: A vector with the elements in reverse order
Algorithm:
            1) Loop through vector from end to beginning, appending elements
Reference: none
********************************************************************* */
template <typename T>
inline vector<T> reversed(const vector<T> &v)
{
    vector<T> reversed_v;
    for (int i = v.size() - 1; i >= 0; i--)
    {
        reversed_v.push_back(v[i]);
    }
    return reversed_v;
}


/* *********************************************************************
Function Name: intersection
Purpose: To find the common elements between two vectors
Parameters:
            v1, a vector of type T passed by reference. It represents
                the first collection of elements
            v2, a vector of type T passed by reference. It represents
                the second collection of elements
Return Value: A vector of type T containing elements that are common
              between v1 and v2
Algorithm:
            1) Use a map to count occurrences of each element in v1
            2) Traverse v2 and check if the element exists in the map.
               If it does, add it to the result and decrease its count
               in the map
Reference: none
********************************************************************* */
template <typename T>
inline std::vector<T> intersection(const std::vector<T> &v1, const std::vector<T> &v2)
{
    std::map<T, int> count_map;
    std::vector<T> result;

    // Count occurrences of each element in v1
    for (const T &element : v1)
    {
        count_map[element]++;
    }

    // Find common elements and their minimum count
    for (const T &element : v2)
    {
        if (count_map[element] > 0)
        {
            result.push_back(element);
            count_map[element]--;
        }
    }

    return result;
}


/* *********************************************************************
Function Name: difference
Purpose: To compute the difference between two vectors (elements present
         in v1 but not in v2)
Parameters:
            v1, a vector of type T passed by reference. It represents
                the main collection of elements
            v2, a vector of type T passed by reference. It represents
                the elements to exclude from v1
Return Value: A vector of type T containing elements that are in v1
              but not in v2
Algorithm:
            1) Sort both vectors to allow efficient comparison
            2) Use iterators to traverse each vector, adding unique
               elements from v1 to the result
            3) Continue adding any remaining elements from v1 after
               v2 is exhausted
Reference: none
********************************************************************* */
template <typename T>
inline vector<T> difference(const vector<T> &v1, const vector<T> &v2)
{
    // Sort both vectors for efficient comparison
    vector<T> sorted_v1(v1);
    sort(sorted_v1.begin(), sorted_v1.end());
    vector<T> sorted_v2(v2);
    sort(sorted_v2.begin(), sorted_v2.end());

    // Use two iterators to traverse the sorted vectors
    auto it1 = sorted_v1.begin();
    auto it2 = sorted_v2.begin();

    vector<T> result;

    // Iterate through both vectors simultaneously
    while (it1 != sorted_v1.end() && it2 != sorted_v2.end())
    {
        if (*it1 < *it2)
        {
            // Element in v1 is smaller, add it to result
            result.push_back(*it1);
            ++it1;
        }
        else if (*it1 == *it2)
        {
            // Elements are equal, skip both
            ++it1;
            ++it2;
        }
        else
        {
            // Element in v2 is smaller, skip it
            ++it2;
        }
    }

    // Add any remaining elements from v1
    while (it1 != sorted_v1.end())
    {
        result.push_back(*it1);
        ++it1;
    }

    return result;
}


/* *********************************************************************
Function Name: contains
Purpose: To check if a specific element exists within a vector
Parameters:
            v, a vector of type T passed by reference. It represents the
               collection to search within
            element, an object of type T passed by value. It represents
                     the item to look for in v
Return Value: A boolean value indicating whether element is in v
Algorithm:
            1) Use the find algorithm to check if element is present in v
Reference: none
********************************************************************* */
template <typename T>
inline bool contains(const vector<T> &v, const T &element)
{
    return find(v.begin(), v.end(), element) != v.end();
}


/* *********************************************************************
Function Name: concatenate
Purpose: To join two vectors into a single vector, keeping elements in
         the original order
Parameters:
            v1, a vector of type T passed by reference. It represents
                the first set of elements to concatenate
            v2, a vector of type T passed by reference. It represents
                the second set of elements to concatenate
Return Value: A vector of type T containing elements of v1 followed by v2
Algorithm:
            1) Create a result vector
            2) Add all elements of v1 to result, followed by all elements
               of v2
Reference: none
********************************************************************* */
template <typename T>
inline vector<T> concatenate(const vector<T> &v1, const vector<T> &v2)
{
    vector<T> result;
    for (const T &element : v1)
    {
        result.push_back(element);
    }
    for (const T &element : v2)
    {
        result.push_back(element);
    }
    return result;
}


/* *********************************************************************
Function Name: unordered_equal
Purpose: To determine if two vectors contain the same elements, regardless
         of their order
Parameters:
            v1, a vector of type T passed by reference. It represents
                the first collection of elements to compare
            v2, a vector of type T passed by reference. It represents
                the second collection of elements to compare
Return Value: A boolean value indicating if v1 and v2 contain the same
              elements in any order
Algorithm:
            1) Check if the vectors are of equal length. If not, return false
            2) Count occurrences of each element in both vectors using a map
            3) If counts for all elements match, return true; otherwise,
               return false
Reference: none
********************************************************************* */
template <typename T>
inline bool unordered_equal(const vector<T> &v1, const vector<T> &v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }

    map<T, int> counts;
    for (const T &element : v1)
    {
        counts[element]++;
    }
    for (const T &element : v2)
    {
        counts[element]--;
    }

    for (const auto &entry : counts)
    {
        if (entry.second != 0)
        {
            return false;
        }
    }

    return true;
}


/* *********************************************************************
Function Name: subset
Purpose: To check if all elements in v2 are present in v1
Parameters:
            v1, a vector of type T passed by reference. It represents
                the main collection of elements
            v2, a vector of type T passed by reference. It represents
                the collection to check as a subset of v1
Return Value: A boolean value indicating if v2 is a subset of v1
Algorithm:
            1) Use a map to count occurrences of each element in v1
            2) For each element in v2, check if it exists in the map
               with a non-zero count. If any element does not, return false
            3) If all elements in v2 are found in v1, return true
Reference: none
********************************************************************* */
template <typename T>
inline bool subset(const vector<T> &v1, const vector<T> &v2)
{
    map<T, int> counts;
    for (const T &element : v1)
    {
        counts[element]++;
    }
    for (const T &element : v2)
    {
        counts[element]--;
    }

    for (const auto &entry : counts)
    {
        if (entry.second < 0)
        {
            return false;
        }
    }

    return true;
}
