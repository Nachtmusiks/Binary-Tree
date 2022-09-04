#include "btree.h"
#include "ArgumentManager.h"

using namespace std;

bool checkDup(vector<int> num, int data)
{
    for (int i = 0; i < num.size(); i++)
    {
        if (num[i] == data)
        {
            return true;
        }
    }
    return false;
}
int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);
    string in = am.get("input");
    string out = am.get("output");
    string cmd = am.get("command");
    vector<int> num;
    ifstream input(in);
    ofstream output(out);
    ifstream command(cmd);
    string degree;
    string temp; //temp string to read getline
    getline(command, degree);
    degree = degree.substr(degree.find("=") + 1);

    BTree t(stoi(degree));

    if (input.is_open())
    {
        while (getline(input, temp))
        {
            stringstream temp2(temp);
            string data;
            while (!temp2.eof())
            {
                temp2 >> data;
                if (!checkDup(num, stoi(data)))
                {
                    num.push_back(stoi(data));
                }

            }          
        }
    }   
    for (int i = 0; i < num.size(); i++)
    {
        t.insert(num[i]);
    }    
    output << "Height=" << t.getHeight() << endl;
    while (getline(command, temp))
    {
        temp = temp.substr(temp.find(' ') + 1); //Level #
        if (stoi(temp) > t.getHeight())
        {
            output << "EMPTY\n";
        }
        else
        {
            t.traverse(stoi(temp) - 1,output);
            output << endl;
        }

    }
    input.close();
    output.close();
    command.close();

    return 0;
}