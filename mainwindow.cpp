#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data_generate=new data_generate_thread;

//************************************动态时域图测试部分************************************//
    acoutic=new acouticWidget(this,false,4000,50,256,60);
    acoutic->acoustic_chartView->fiber_len=6000;
    connect(data_generate,SIGNAL(data_complete(double*,int)),acoutic,SLOT(acousticUpdate(double *,int)));
    QHBoxLayout *acoustic_layout = new QHBoxLayout();
    acoustic_layout->setContentsMargins(0,0,0,0);
    acoustic_layout->addWidget(acoutic->acoustic_chartView);
    ui->graphicsView->setLayout(acoustic_layout);//ui中拉出一个graphicsview对象并命名为Timedomain

//************************************定位图测试部分************************************//
//    acoutic=new acouticWidget(this,true,4000,50,256,60);
//    QHBoxLayout *acoustic_layout = new QHBoxLayout();
//    acoustic_layout->setContentsMargins(0,0,0,0);
//    acoustic_layout->addWidget(acoutic->chartView);
//    ui->graphicsView->setLayout(acoustic_layout);//ui中拉出一个graphicsview对象并命名为Timedomain
//    connect(data_generate,SIGNAL(data_complete(double*,int)),acoutic,SLOT(locateUpdate(double *,int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//按键触发槽函数
{

//    qDebug()<<"index="<<ui->typeselete->currentIndex();
//    switch (ui->typeselete->currentIndex())
//    {
//        case 0:
//        {
//            acoutic=new acouticWidget(this,true,4000,50,256,60);
//            acoutic->chartView->fiber_len=256;
//            QHBoxLayout *acoustic_layout = new QHBoxLayout();
//            acoustic_layout->setContentsMargins(0,0,0,0);
//            acoustic_layout->addWidget(acoutic->chartView);
//            ui->graphicsView->setLayout(acoustic_layout);//ui中拉出一个graphicsview对象并命名为Timedomain
//            connect(data_generate,SIGNAL(data_complete(double*,int)),acoutic,SLOT(locateUpdate(double *,int)));
//            break;
//        }
//        case 1:
//        {
//            acoutic=new acouticWidget(this,false,4000,50,256,60);
//            QHBoxLayout *acoustic_layout = new QHBoxLayout();
//            acoustic_layout->setContentsMargins(0,0,0,0);
//            acoustic_layout->addWidget(acoutic->acoustic_chartView);
//            ui->graphicsView->setLayout(acoustic_layout);//ui中拉出一个graphicsview对象并命名为Timedomain

//            connect(data_generate,SIGNAL(data_complete(double*,int)),acoutic,SLOT(acousticUpdate(double *,int)));
//            break;
//        }
//    }
    ADRun=!ADRun;
    data_generate->start();
}
