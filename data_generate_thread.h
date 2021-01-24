#ifndef DATA_GENERATE_THREAD_H
#define DATA_GENERATE_THREAD_H

#include <QThread>
#include <QDebug>
#include <Windows.h>
#include <cstring>
#include <QDebug>

extern bool ADRun;

class data_generate_thread : public QThread
{
    Q_OBJECT
public:
     data_generate_thread();
     size_t fps; //每秒帧数
signals:
     void data_complete(double*,int);
protected:
    void run() override;
};



#endif // DATA_GENERATE_THREAD_H
