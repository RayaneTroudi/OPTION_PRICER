#include "Core/Path.hpp"

Path::Path(const std::vector<double>& prices_in) : prices(prices_in) {} 


// get the price at final time
double Path::getFinalPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return prices.back();
}




// get the average price over the path
double Path::getAveragePrice() const {
    if (prices.empty()){
        return 0.0;
    }
    double sum = std::accumulate(prices.begin(), prices.end(), 0.0);
    return sum / prices.size();
}




// get the maximum price over the path
double Path::getMaxPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::max_element(prices.begin(), prices.end());
}




// get the minimum price over the path
double Path::getMinPrice() const {
    if (prices.empty()){
        return 0.0;
    }
    return *std::min_element(prices.begin(), prices.end());
}



// get the length of the path
size_t Path::getLength() const {
    return prices.size();
}



// get the price at a specific index
double Path::at(size_t index) const {
    return prices.at(index);
};




