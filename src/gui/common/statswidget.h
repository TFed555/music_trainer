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
    Q_OBJECT
public:
    explicit StatsWidget(StatisticsRepository* statsRepo, QWidget *parent = nullptr);
    ~StatsWidget();
    void showEvent(QShowEvent*) override;
private:
    void buildBarChart(const QVector<CategoryStats>& stats);
    void changeEvent(QEvent* event) override;
    StatisticsRepository* statsRepo;
    StatisticsSolver solver;
    QVBoxLayout* layout;
    QChartView* chartView = nullptr;
};

#endif // STATSWIDGET_H
