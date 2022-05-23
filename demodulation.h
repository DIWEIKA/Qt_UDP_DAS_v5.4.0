#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QThread>
#include <mainwindow.h>

#define READ_LENGTH 4096*1000 //从CHdata里读取的数据长度
#define CHDATA_ALL_LENGTH 1024*1000 //四个通道的十进制数数据长度
#define CHDATA_LENGTH 256*1000 //一个通道的十进制数长度
#define NUMTABLE 201

class UDP_Recv;

class Demodulation : public QThread
{
    Q_OBJECT
public:
    explicit Demodulation(UDP_Recv* udp_Recv);

    UDP_Recv* udp_recv;
    shared_ptr<CirQueue<float>> DEMOdata_flash;
    shared_ptr<CirQueue<float>> DEMOdata_save;
    unsigned char demo_CHdata[READ_LENGTH]= {'\0'};
    float Vi[CHDATA_LENGTH] = {0};
    float Vq[CHDATA_LENGTH]= {0};
    float Ph[CHDATA_LENGTH]= {0};
    float atanTable[NUMTABLE]= {0};
    int sizeoCHdata;
    int demo_CHdata_DEC_all[CHDATA_ALL_LENGTH]= {0};
    int sizeoCHdataDec;
    int demo_CHdata_DEC_1[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_2[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_3[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_4[CHDATA_LENGTH]= {0};
    int sizeoDemoCHdata;
    int peakNum;
    qint64 LenoDemo = READ_LENGTH;
    qint64 LenoDemoSave = 4096*10000;

    float* RealPh;
    float* PriorPh;
    float* K;
    float* PriorK;

    void readConfigFile();
    void readAtanTable(float *roundNum);
    float demoduPh(float vi,float vq);
    float Unwrap(float Ph, int i);

signals:
    void sendToDemoWave_widget(shared_ptr<CirQueue<float>> DEMOdata);

protected:
    void run();

};

#endif // DEMODULATION_H
