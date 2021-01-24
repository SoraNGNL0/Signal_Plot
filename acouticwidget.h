#ifndef ACOUTICWIDGET_H
#define ACOUTICWIDGET_H

#include <QObject>
#include <QWidget>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QLineSeries>
#include <QDebug>
#include "data_generate_thread.h"
#include "chartview.h"

using namespace QtCharts;
extern bool ADRun;//不鲁棒点

class acouticWidget : public QWidget
{
    Q_OBJECT
public:
    explicit acouticWidget(QWidget *parent = nullptr,bool type=false,size_t ac_max_X=0,size_t ac_max_Y=0,size_t lc_max_X=0,size_t lc_max_Y=0);
    int acoustic_maxX;
    int acoustic_maxY;
    int location_maxY;
    int location_maxX;
    QVector<QPointF> points;
    QChart *acoustic_chart;
    QChart *chart;
    ChartView *chartView;
    ChartView *acoustic_chartView;
    QLineSeries *location_line;//draw location line
    QLineSeries *acoustic_line;//draw acoustic line
    bool acoustic_error;//judge acoustic input is nan or Inf,exist->return error
    bool location_error;//judge location input is nan or Inf,exist->return error

signals:

public slots:
    void acousticUpdate(double *data_in,int len);//data_in is acoustic input,len is data_in's length
    void locateUpdate(double *data_in,int len);//data_in is location input,len is location's len
};

#endif // ACOUTICWIDGET_H
