/*
 * @Author: your name
 * @Date: 2021-07-25 20:54:29
 * @LastEditTime: 2021-09-25 09:25:48
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \C_Single\excercise\hello.cpp
 */

#include<fstream>
#include<iostream>
#include<vector>
#include <string>
using namespace std;

#define DEMENSION 5

double weight[DEMENSION];//权重值
int step = 0;//修改次数
int n = 0;//训练样本数
string filename = "hw1_15_train.dat";//读取文件名

//存储训练样本，input为x，output为y
struct record{
    double input[DEMENSION];
    int output;
};

//把记录存在向量里而不是存在结构体数组内，这样可以根据实际一项项添加
vector<record> trainingSet;

//将数据读入训练样本向量中
void getData(ifstream &datafile)
{
    while(!datafile.eof())
    {
        record curRecord;
        curRecord.input[0] = 1;
        int i;
        for(i = 1; i < DEMENSION; i++){
            datafile>>curRecord.input[i];
        }
        datafile>>curRecord.output;
        trainingSet.push_back(curRecord);
    }
    datafile.close();
    n = trainingSet.size(); 
}

//计算sign值
int sign(double x){
    if(x <= 0)return -1;
    else return 1;
}

//两向量相加(实际为数组相加)，将结果保存在第一个数组内，用于计算w(i+1)=w(i)+y*x
void add(double *v1,double *v2,int demension){
    int i;
    for(i = 0;i < demension; i++)v1[i] += v2[i];
}

//计算两数值相乘值，用于判断w*x是否小于0，若小于0要执行修正算法
double multiply(double *v1,double *v2,int demension){
    double temp = 0.0;
    int i;
    for(i = 0; i < demension; i++)temp += v1[i] * v2[i];
    return temp;
}

//计算实数num与向量乘积放在result中，用于计算y*x
void multiply(double *result,double *v,int demension,int num){
    int i;
    for(i = 0; i < demension; i++)result[i] = num * v[i];
}

void PLA()
{
    int correctNum = 0;//当前连续正确样本数，当等于n则表明轮完一圈，则表示全部正确，算法结束
    int index = 0;//当前正在计算第几个样本
    bool isFinished = 0;//算法是否全部完成的表示，=1表示算法结束
    while(!isFinished){
        if(trainingSet[index].output == sign(multiply(weight,trainingSet[index].input,DEMENSION)))correctNum++;//当前样本无错，连续正确样本数+1
        else{//出错，执行修正算法
            double temp[DEMENSION];
            multiply(temp,trainingSet[index].input,DEMENSION,trainingSet[index].output);//计算y*x
            add(weight,temp,DEMENSION);//计算w(i+1)=w(i)+y*x
            step++;//进行一次修正，修正次数+1
            correctNum = 0;//由于出错了，连续正确样本数归0
            cout<<"step"<<step<<":"<<endl<<"index="<<index<<" is wrong"<<endl;
        }
        if(index == n-1)index = 0;
        else index++;
        if(correctNum == n)isFinished = 1;
    }
    cout<<"total step:"<<step<<endl;
}

int main()
{
    
    ifstream dataFile(filename);

    if(dataFile.is_open()){
        
        getData(dataFile);
    }
    else{
        cout<<"出错，文件打开失败！"<<endl;
        exit(1);
    }
    


    int i;
    for(i = 0; i < DEMENSION; i++)weight[i] = 0.0;
    PLA();

    for(i = 0; i < DEMENSION; i++) cout<<weight[i]<<", ";
    

    return 1;
}
