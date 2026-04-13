#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include "../../core/common/models/StatisticsModel.h"
#include "../../core/data/statistics/statisticsrepository.h"
#include "../../core/data/statistics/statisticssolver.h"
#include <QVBoxLayout>
#include <QChartView>

class StatsWidget : public QWidget
{
public:
    explicit StatsWidget(StatisticsRepository* statsRepo, QWidget *parent = nullptr);
    ~StatsWidget();
    void showEvent(QShowEvent*);
private:
    void buildBarChart(const QVector<CategoryStats>& stats);
    StatisticsRepository* statsRepo;
    StatisticsSolver solver;
    QVBoxLayout* layout;
    QChartView* chartView = nullptr;
};

#endif // STATSWIDGET_H
