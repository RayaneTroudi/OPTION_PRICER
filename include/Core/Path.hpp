#ifndef PATH_HPP
#define PATH_HPP

#include <vector> 
#include <numeric>
#include <algorithm>
#include <stdexcept>

/**
 * @brief Represents a single simulated trajectory of asset prices over time.
 * * This class stores a sequence of discrete price points S_t from t=0 to T.
 * It provides utility methods required by path-dependent options (Asian, Lookback).
 */
class Path{

public:

    /**
     * @brief Default constructor.
     */
    Path() = default;

    /**
     * @brief Parameterized constructor.
     * @param prices_in The vector containing the sequence of discrete prices.
     */
    Path(const std::vector<double>& prices_in);

    // --- Accessor Methods ---

    /**
     * @brief Retrieves the price at the end of the path (S_T).
     * This is typically used by European (vanilla) options.
     * @return The final price S_T.
     * @throw std::out_of_range If the path is empty.
     */
    double getFinalPrice() const;

    /**
     * @brief Calculates the average price over all time steps in the path.
     * This is required for Asian options (Average Rate Options).
     * @return The arithmetic mean of all prices in the path.
     * @throw std::out_of_range If the path is empty.
     */
    double getAveragePrice() const;

    /**
     * @brief Finds the maximum price reached during the path.
     * This is required for Lookback options.
     * @return The maximum price S_max.
     * @throw std::out_of_range If the path is empty.
     */
    double getMaxPrice() const;

    /**
     * @brief Finds the minimum price reached during the path.
     * This is required for Lookback options.
     * @return The minimum price S_min.
     * @throw std::out_of_range If the path is empty.
     */
    double getMinPrice() const;

    /**
     * @brief Gets the total number of price points stored (steps + 1).
     * @return The size of the internal price vector.
     */
    size_t getLength() const;

    /**
     * @brief Accesses the price at a specific time step index.
     * @param index The step index (0 for S0, Length-1 for S_T).
     * @return The price S_t at the given index.
     */
    double at(size_t index) const;

    /**
     * @brief Provides a non-const reference to the internal data vector.
     * @warning Use with caution. Primarily for advanced internal manipulation.
     * @return A mutable reference to the underlying std::vector<double>.
     */
    std::vector<double>& data(){return prices;}

private:
    /**
     * @brief Internal storage for the asset price sequence.
     * The size is typically steps + 1 (including S0).
     */
    std::vector<double> prices;
    
};

#endif // PATH_HPP