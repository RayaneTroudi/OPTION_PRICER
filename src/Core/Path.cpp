#include "Core/Path.hpp"
#include <numeric>     // Required for std::accumulate
#include <algorithm>   // Required for std::max_element and std::min_element
#include <stdexcept>   // Required for exception handling in general (though not explicitly used here)

// --- Constructor ---

/**
 * @brief Parameterized constructor for the Path class.
 * * Initializes the internal price vector with the provided sequence.
 * @param prices_in The vector containing the sequence of discrete prices.
 */
Path::Path(const std::vector<double>& prices_in) : prices(prices_in) {} 


// --- Accessor Methods ---

/**
 * @brief Retrieves the price at the end of the path (S_T).
 * * Uses std::vector::back() for O(1) complexity.
 * @return The final price S_T, or 0.0 if the path is empty.
 */
double Path::getFinalPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return prices.back();
}


/**
 * @brief Calculates the arithmetic average price over all time steps in the path.
 * * Uses std::accumulate for efficient summation.
 * @return The arithmetic mean of all prices, or 0.0 if the path is empty.
 */
double Path::getAveragePrice() const {
    if (prices.empty()){
        return 0.0;
    }
    double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
    return sum / prices.size();
}


/**
 * @brief Finds the maximum price reached during the path.
 * * Uses std::max_element to find the largest price.
 * @return The maximum price S_max, or 0.0 if the path is empty.
 */
double Path::getMaxPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::max_element(prices.begin(), prices.end());
}


/**
 * @brief Finds the minimum price reached during the path.
 * * Uses std::min_element to find the smallest price.
 * @return The minimum price S_min, or 0.0 if the path is empty.
 */
double Path::getMinPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::min_element(prices.begin(), prices.end());
}


/**
 * @brief Gets the total number of price points stored (number of time steps + 1).
 * @return The size of the internal price vector.
 */
size_t Path::getLength() const {
    return prices.size();
}


/**
 * @brief Accesses the price at a specific time step index.
 * * Uses std::vector::at() which performs bounds checking (throws std::out_of_range if index is invalid).
 * @param index The step index (0 for S0, Length-1 for S_T).
 * @return The price S_t at the given index.
 */
double Path::at(size_t index) const {
    return prices.at(index);
};