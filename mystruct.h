#ifndef MYSTRUCT_H
#define MYSTRUCT_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

class blifWire;
class blifElaborate;


using namespace std;


class blifWire
{
public:
    blifWire();
    void setOutput(const string& outPutName);
    string getOutput(); //获取输出端口名

    void addHead(const string& headName);
    const vector<string>& getHead();//获取表头

    void addLogic(const string& logicRow);
    const vector<string>& getLogic();//获取逻辑式

    void addLogical(vector<char>& logicals);
    string getHeadoutput(); //获取表头的输出端口名
private:
    string Output;
    vector<string> head;  // 表头，例如 {"d", "e", "f", "j"}
    vector<string> logic;  // 逻辑表达式
    vector<vector<char>> logical;
};

class blifElaborate
{
public:
    blifElaborate();
    void setFileName(const string& filename);
    string getFileName();
    void setInput(const string& inputName);
    void setOutput(const string& outputName);
    void setWire(const string& wireName);
    void blifElaborateRead();  // 解析
    void blif2Verilog();   //输出

private:
    string fileName; //该blif文件名称
    vector<blifWire> myblifWires;//存储所有的连接关系的数据结构
    vector<string> output; //blif中的输出端口
    vector<string> input; //blif中的输入端口
    vector<string> wire; //blif中的端口
    ifstream file;
};

#endif // !MYSTRUCT_H
