#include "Core/Path.hpp"
#include <numeric>
#include <algorithm>
#include <stdexcept>

Path::Path(const std::vector<double>& prices_in) : prices(prices_in) {} 

double Path::getFinalPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return prices.back();
}

double Path::getAveragePrice() const {
    if (prices.empty()){
        return 0.0;
    }
    double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
    return sum / prices.size();
}

double Path::getMaxPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::max_element(prices.begin(), prices.end());
}

double Path::getMinPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::min_element(prices.begin(), prices.end());
}

size_t Path::getLength() const {
    return prices.size();
}

double Path::at(size_t index) const {
    return prices.at(index);
};