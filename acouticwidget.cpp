#include "acouticwidget.h"

acouticWidget::acouticWidget(QWidget *parent,bool type,size_t ac_max_X,size_t ac_max_Y,size_t lc_max_X,size_t lc_max_Y)
{

    if(type)
    {

        location_maxY = lc_max_Y;
        location_maxX = lc_max_X;
        location_line  = new QLineSeries;
        chart = new QChart();
        chart->addSeries(location_line);
        chart->legend()->hide();
        chart->createDefaultAxes();

        chart->axisX()->setRange(0,location_maxX);
        chart->axisY()->setRange(0, location_maxY);
        chart->axisX()->setTitleText("Distance/m");
        chart->axisY()->setTitleText("Energy/a.u.");
        chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
        chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

        chartView = new ChartView(chart);
        chartView->loc_dclk=true;//针对定位图和时域波形图定义的属性初始化

        location_error=false;//initialize
    }
    else
    {
        acoustic_maxX = ac_max_X;//acoustic横轴最大值
        acoustic_maxY = ac_max_Y;//acoustic纵轴最大值
        acoustic_line = new QLineSeries;
        acoustic_line->setPen(QPen(Qt::blue,1));
        acoustic_chart= new QChart();
        acoustic_chart->addSeries(acoustic_line);//添加线到chart对象

        acoustic_chart->createDefaultAxes();
        acoustic_chart->axisY()->setRange(-1*acoustic_maxY, acoustic_maxY);
        acoustic_chart->axisX()->setRange(0, acoustic_maxX);//设置范围

        acoustic_chart->axisX()->setTitleText("Time/ms");//横轴说明
        acoustic_chart->axisY()->setTitleText("Energy/a.u.");//纵轴说明

        acoustic_chart->axisX()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));
        acoustic_chart->axisY()->setTitleFont(QFont("Microsoft YaHei", 10, QFont::Normal, true));

        acoustic_chart->axisX()->setGridLineVisible(false);
        acoustic_chart->axisY()->setGridLineVisible(false);

        /* hide legend */
        acoustic_chart->legend()->hide();
        acoustic_chartView = new ChartView(acoustic_chart,this);
        acoustic_chartView->loc_dclk=false;//针对定位图和时域波形图定义的属性初始化

        acoustic_error = false;//initialize
    }
}

void acouticWidget::acousticUpdate(double *data_in,int len)//用于更新时域波形图的槽函数
{
    int i;
    QVector<QPointF> oldData = acoustic_line->pointsVector();
    QVector<QPointF> data;

    if (oldData.size() < acoustic_maxX)
    {
        data = acoustic_line->pointsVector();//*******
    }
    else
    {
        /* 添加之前老的数据到新的vector中，不复制最前的数据，即每次替换前面的数据
         * 由于这里每次只添加len个数据，所以为len，使用时根据实际情况修改
         */
        for (i = len; i < oldData.size(); ++i)
        {
            data.append(QPointF(i - len, oldData.at(i).y()));
        }
    }
    qint64 size = data.size();
    /* 这里表示插入新的数据，因为每次只插入len个，这里为i < len,
     * 但为了后面方便插入多个数据，先这样写
     */
    double mean_val = 0;
    for (int i = 0; i<len; ++i)
        mean_val += data_in[i];
    mean_val /= len; //去直流
    if(isnan(mean_val)||isinf(mean_val))
        acoustic_error=true;//judge the input exist the Inf or Nan
    i = 0;
    while(/*flags.bADRun &&*/ i < len)//标志位控制运行，一定要兼顾运行的标志位
    {
       data.append(QPointF(i+size, data_in[i] - mean_val));//
       ++i;
    }
    acoustic_line->replace(data);//更新波形数据
}

void acouticWidget::locateUpdate(double *data_in,int len)
{
    double temp=0;//store the sum of data_in,devoted to judge the Inf or Nan
    if(ADRun)//标志位注意
    {
        location_line->clear();
        points.clear();
    }
    int i=0;
    while(ADRun && i<len)//标志位注意
    {
        temp=temp+data_in[i];
        points.append(QPointF(i,data_in[i]));
        i++;
    }
    location_line->replace(points);
}
