#ifndef STATISTICSMODEL_H
#define STATISTICSMODEL_H
#include <QString>

struct CategoryStats {
    QString name;
    int correct;
    int total;
    double accuracy() const { return total > 0 ? (double)correct / total : 0; }
};

#endif // STATISTICSMODEL_H
