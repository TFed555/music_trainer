#include "statswidget.h"
#include <QtCharts>

StatsWidget::StatsWidget(StatisticsRepository* statsRepo, QWidget *parent)
    : QWidget(parent)
    , statsRepo(statsRepo)
{
    layout = new QVBoxLayout(this);
}

StatsWidget::~StatsWidget()
{
}

void StatsWidget::showEvent(QShowEvent*) {
    auto data = statsRepo->loadStatistics();
    buildBarChart(solver.byCategory(data));
}

void StatsWidget::buildBarChart(const QVector<CategoryStats>& stats) {
    QBarSet *correct = new QBarSet(tr("Правильно"));
    QBarSet *total = new QBarSet(tr("Всего"));
    for (auto n : stats) {
        *correct << n.correct;
        *total << n.total;
    }

    QBarSeries *series = new QBarSeries();
    series->append(correct);
    series->append(total);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle(tr("Статистика выполнения"));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (auto n : stats) {
        categories << n.name;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    if (chartView) {
        layout->removeWidget(chartView);
        delete chartView;
    }
    chartView = new QChartView(chart, this);
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
}
