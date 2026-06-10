#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H
#include "BlockCategory.h"

struct CategoryStats {
    BlockCategory category;
    int correct;
    int total;
    double accuracy() const { return total > 0 ? (double)correct / total : 0; }
};

#endif // STATISTICSMODEL_H
