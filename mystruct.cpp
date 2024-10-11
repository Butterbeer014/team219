#include"mystruct.h"

BilfElaborate::BilfElaborate()
{
}

void BilfElaborate::BilfElaborateRead()
{
    ifstream file("C:/Users/Y1nz/Desktop/test1.blif"); // �滻Ϊ����ļ�·��
    if (!file.is_open()) {
        cerr << "�޷����ļ�" << endl;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string token;

        // ��ȡ��һ�����ʣ�ͨ����ָ��
        iss >> token;
        if (token == ".model") {
            // ��ȡģ�����ƣ������ո�
            std::string model_name;
            if (iss >> model_name) { // ȷ�����Զ�ȡģ������
                setFileName(model_name); // ʹ�����ú��������ļ���
            }
        }

        else if (token == ".inputs") {
            // ��ȡ����˿�
            while (iss >> token) {
                setInput(token); // ʹ�����ú����������˿�
                setWire(token);// ʹ�����ú���������ж˿�
            }
        }
        else if (token == ".outputs") {
            // ��ȡ����˿�
            while (iss >> token) {
                setOutput(token); // ʹ�����ú����������˿�
                setWire(token);// ʹ�����ú���������ж˿�
            }
        }
        else if (token == ".names") {
            BilfWire myBilfWire;//Ϊÿ��names������һ����װ�����ݽṹ

            // �������� .names ���е�����
            while (iss >> token) {
                setWire(token);// ʹ�����ú�����Ӷ˿���û�еĶ˿�
                myBilfWire.addHead(token);//������������ж˿�
            }
            string outputName = myBilfWire.getHeadoutput(); 
            myBilfWire.setOutput(outputName);//��������˿ڵķ���
            while (getline(file, line) && (isdigit(line[0]) || line[0] == '-')) {
                const vector<string>& it = myBilfWire.getHead();//��ñ�ͷ
                string expr;
                bool first = true;
                for (size_t i = 0; i < it.size(); ++i) {
                    if (line[i] == '1') {
                        if (!first) expr += " & ";
                        expr += it[i];
                        first = false;
                    }
                    else if (line[i] == '0') {
                        if (!first) expr += " & ";
                        expr += "!" + it[i];
                        first = false;
                    }
                }
                myBilfWire.addLogic(expr);

                vector<char> mylogical;
                for (char c : line) {
                    if (c != ' ') {
                        mylogical.push_back(c);
                    }
                }
                myBilfWire.addLogical(mylogical);

            }
            myBilfWires.push_back(myBilfWire);

            if (!line.empty() && !isdigit(line[0])) {
                file.putback('\n');
                for (auto it = line.rbegin(); it != line.rend(); ++it) {
                    file.putback(*it);
                }
            }
        }
    }
    int a = 1;
    file.close();
}

void BilfElaborate::setFileName(const string& filename)
{
    fileName = filename;
}

string BilfElaborate::getFileName()
{
    return fileName;
}

void BilfElaborate::setInput(const string& inputName)
{
    input.push_back(inputName);
}

void BilfElaborate::setOutput(const string& outputName)
{
    output.push_back(outputName);
}

void BilfElaborate::setWire(const string& wireName)
{
    auto it = find(wire.begin(), wire.end(), wireName);
    if (it == wire.end()) {
        // ���outputName����outputs�У������
        wire.push_back(wireName);
    }
}

void BilfElaborate::Bilf2Verilog()
{
    std::ofstream outFile("C:/Users/Y1nz/Desktop/111/test1.v");

    // д���ļ���
    string fileName = getFileName();
    outFile << "module " << fileName <<"(clk, rst";
    for (const auto& output : output) {
        outFile << "," << output;
    }
    for (const auto& input : input) {
        outFile << "," << input;
    }

    outFile << ");"<< endl;
    outFile << "input clk,rst;" << endl;
    for (const auto& output : output) {
        outFile << "output " << output << ";" << endl;
    }
    for (const auto& input : input) {
        outFile << "input  "<<input << ";" << endl;
    }
    outFile << endl;

    for (const auto& wire : wire) {
        outFile << "wire  " << wire << ";" << endl;
    }
    outFile << endl;

    for (auto blifWire : myBilfWires) {
        outFile << "assign " << blifWire.getOutput() << " = ";
        const auto& it = blifWire.getLogic();
        for (size_t i = 0; i < it.size(); ++i) {
            outFile << " " << it[i] << " ";
            if (i < it.size() - 1) {
                outFile << "|";
            }
        }
        outFile << ";\n";
    }

    outFile << endl;

    outFile << "endmodule"<< endl;

    outFile.close();

    std::cout << "������д�뵽�ļ��С�" << std::endl;

}

BilfWire::BilfWire()
{
}

void BilfWire::setOutput(const string& outPutName)
{
    Output = outPutName;
}

void BilfWire::addLogic(const string& logicRow)
{
    logic.push_back(logicRow);
}

void BilfWire::addHead(const string& headName)
{
    head.push_back(headName);
}

const vector<string>& BilfWire::getHead()
{
    return head;
}

string BilfWire::getOutput()
{
    return Output;
}

void BilfWire::addLogical(vector<char>& logicals)
{
    logical.push_back(logicals);
}

string BilfWire::getHeadoutput()
{
    return head.back();
}


const vector<string>& BilfWire::getLogic()
{
    return logic;
}




