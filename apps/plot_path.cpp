#include "Models/GBM.hpp"
#include "Utils/GnuplotExporter.hpp"

int main() {
    GBM gbm(100.0, 252, 0.05, 0.2);
    GnuplotExporter::savePathPNG(gbm.generatePath(1.0), 1.0, "path.png");
    return 0;
}