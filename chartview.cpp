#include "chartview.h"

ChartView::ChartView(QChart *chart, QWidget *parent):
    QChartView(chart, parent),
    isClicking(true),
    xOld(0),yOld(0)
{
    setRenderHint(QPainter::Antialiasing); //抗锯齿
    setRubberBand(QChartView::RectangleRubberBand);//确定是界面画四边形放大
}

void ChartView::mousePressEvent(QMouseEvent *event)//鼠标按键操作
{
    if(event->button()==Qt::MidButton)
    {
        chart()->zoomReset();
    }
    QChartView::mousePressEvent(event);//这句话非常关键
}

void ChartView::wheelEvent(QWheelEvent *event)//鼠标滚轮操作
{
    if(event->delta()>0)
    {
        chart()->zoom(1.1);
    }
    else
    {
        chart()->zoom(10.0/11);
    }
    QChartView::wheelEvent(event);//
}

void ChartView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(loc_dclk)
    {
        QPointF point=chart()->mapToValue(event->pos());//return mouse click position
        loc_temp.setX(qMin((int)point.x(),fiber_len));
        loc_temp.setX(qMax((int)point.x(),0));
        loc_temp.setY((int)point.y());
        qDebug()<<"loc_temp="<<loc_temp;
        QChartView::mouseDoubleClickEvent(event);
    }
    else
    {
        QChartView::mouseDoubleClickEvent(event);
        return;
    }
}
