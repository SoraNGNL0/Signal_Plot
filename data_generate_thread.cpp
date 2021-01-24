#include "data_generate_thread.h"

int fft_len = 256;

data_generate_thread::data_generate_thread()
{
    fps = 1; //每秒帧数
    ADRun = false;
}

void data_generate_thread::run()
{
    fps=10;//control the location plot speed
    double *in = new double[fft_len];
    int k = 0;
    for(int i=0;i<50;i++)
    {
        for(int j=0;j<fft_len;j++)
        {
            ++k;
            in[j] = rand()%50;
        }
        emit data_complete(in,fft_len);
        Sleep(1000/fps);
    }
    delete[]in;
}
