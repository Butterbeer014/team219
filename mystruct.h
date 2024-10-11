#ifndef MYSTRUCT_H
#define MYSTRUCT_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class BilfWire;
class BilfElaborate;


using namespace std;


class BilfWire
{
public:
    BilfWire();
    void setOutput(const string& outPutName);
    string getOutput(); //��ȡ����˿���

    void addHead(const string& headName);
    const vector<string>& getHead();//��ȡ��ͷ

    void addLogic(const string& logicRow);
    const vector<string>& getLogic();//��ȡ�߼�ʽ

    void addLogical(vector<char>& logicals);
    string getHeadoutput(); //��ȡ��ͷ������˿���
private:
    string Output;
    vector<string> head;  // ��ͷ������ {"d", "e", "f", "j"}
    vector<string> logic;  // �߼����ʽ
    vector<vector<char>> logical;
};

class BilfElaborate
{
public:
    BilfElaborate();
    void setFileName(const string& filename);
    string getFileName();
    void setInput(const string& inputName);
    void setOutput(const string& outputName);
    void setWire(const string& wireName);
    void BilfElaborateRead();  // ����
    void Bilf2Verilog();   //���

private:
    string fileName; //��bilf�ļ�����
    vector<BilfWire> myBilfWires;//�洢���е����ӹ�ϵ�����ݽṹ
    vector<string> output; //bilf�е�����˿�
    vector<string> input; //bilf�е�����˿�
    vector<string> wire; //bilf�еĶ˿�
    ifstream file;
};

#endif // !MYSTRUCT_H
