#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QRubberBand>
#include <QDebug>
QT_CHARTS_USE_NAMESPACE

class ChartView : public QChartView
{
public:
    ChartView(QChart *chart, QWidget *parent = 0);
    bool loc_dclk;
    QPoint loc_temp;
    int fiber_len;//针对光纤定位图的长度定义

protected:
    void mousePressEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    bool isClicking;

    int xOld;
    int yOld;
};

#endif // CHARTVIEW_H
