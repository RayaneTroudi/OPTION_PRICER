#ifndef PATH_HPP
#define PATH_HPP

#include <vector> 
#include <numeric>
#include <algorithm>
#include <stdexcept>

class Path{

    public:
    
        Path() = default;
        Path(const std::vector<double>& prices_in);

        double getFinalPrice() const;
        double getAveragePrice() const;
        double getMaxPrice() const;
        double getMinPrice() const;
        size_t getLength() const;
        double at(size_t index) const;
        std::vector<double>& data(){return prices;}

    private:
        std::vector<double> prices;


};

#endif