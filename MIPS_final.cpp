#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <typeinfo>
#include <bitset>
#include <cctype>
using namespace std;
//?????? ???? ????????? ???????

string hex_to_dec(unsigned int x);
string binary_inst_R_op(string s);
string binary_inst(vector<string> s, vector<string> la);
string binary_inst_R_funct(string s);
string binary_inst_I_op(string s);
string binary_inst_J_op(string s);
void data_detect(vector<vector<string>> &s, int x, int y, vector<string> &w_ad, vector<string> &w_d, vector<string> &lb, vector<string> &lba);
void text_detect(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);
void text_detect_exe(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);

void inst_lb_change(vector<string> &s, vector<string> lb, vector<string> lb_ad);
unsigned int binary_to_ten(string s);
int main(int argc, const char * argv[])
{   
    int locate_data;
    int locate_text;
    string File_name;
    string str;
    ifstream readFile;
    vector<string> File_in_vector;
    vector<vector<string>> split_vector_wordbyword_1;
    vector<string> split_vector_wordbyword_2;
    vector<char> split_vector_wordbyword_3;
    vector<string> label;
    vector<string> label_address;
    vector<string> word_directives;
    vector<string> word_address;
    vector<string> instruction_address;
    vector<string> instruction_binary;
    // cout << "\"sample.s\" ?? ???????????" <<endl;
    // cin >> File_name;
    vector<char> save_binary;
    char filePath[100];
    strcpy(filePath, argv[1]);
    cout<<"HERE"<<filePath<<endl;
    cout<<"part 0. finish"<<endl;
    // string filePath="sample2.s";
    // readFile.open(File_name);
    ifstream InputFile(filePath);
    if (InputFile.is_open())
    {
        while (!InputFile.eof())
        {
            getline(InputFile, str);
            if(str.length()!=0)
            {
                File_in_vector.push_back(str);
            }
        }//????? ?��???? File_in_vector?? ????? ??????
        
        for (int i=0; i<File_in_vector.size();i++)
        {
            cout << File_in_vector[i] << endl;
        }
        InputFile.close();

    }
    cout<<"part 1. finish"<<endl;
    for (int i=0; i<=(File_in_vector.size()-1); i++)
    {
        for (int j=0; j<(File_in_vector[i].length()); j++)
        {
            if (File_in_vector[i][j]!=' ')
            {
                split_vector_wordbyword_3.push_back(File_in_vector[i][j]);
                if (j==(File_in_vector[i].length()-1))
                {
                    string s(split_vector_wordbyword_3.begin(), split_vector_wordbyword_3.end());
                    split_vector_wordbyword_2.push_back(s);
                    split_vector_wordbyword_3.clear();
                }
            }   
            else
            {
                if (split_vector_wordbyword_3.size() != 0 )
                {
                    string s(split_vector_wordbyword_3.begin(), split_vector_wordbyword_3.end());
                    split_vector_wordbyword_2.push_back(s);
                    split_vector_wordbyword_3.clear();
                }
            }  
        }
        split_vector_wordbyword_1.push_back(split_vector_wordbyword_2);
        split_vector_wordbyword_2.clear();

    }
    // cout<<"part 2. finish"<<endl;
    // for (int r=0; r<split_vector_wordbyword_1.size(); r++)
    // {
    //     for (int t=0; t<split_vector_wordbyword_1[r].size(); t++)
    //     {
    //         cout << "split_vector_wordbyword1 [" << r << "]" << "[" << t << "]" << split_vector_wordbyword_1[r][t] << endl;
    //     }   
    // }
    for (int i=0; i<split_vector_wordbyword_1.size(); i++)
    {
        for (int t=0; t<split_vector_wordbyword_1[i].size(); t++)
        {
            if(split_vector_wordbyword_1[i][t]==".data")
            {
                locate_data=i;//.data�� ��Ÿ������ ������ �ڵ�
            }
            else if(split_vector_wordbyword_1[i][t]==".text")
            {
                locate_text=i;//.text�� ��Ÿ������ ������ �ڵ�
            }
        }
    }
    
    // cout<<split_vector_wordbyword_1[9].size()<<endl;
    data_detect(split_vector_wordbyword_1, locate_data, locate_text, word_address, word_directives, label, label_address);
    cout<<"passpoint_here"<<endl;
    text_detect(split_vector_wordbyword_1, locate_text, instruction_address, instruction_binary, label, label_address);
    cout<<"part 2. finish"<<endl;
    text_detect_exe(split_vector_wordbyword_1, locate_text, instruction_address, instruction_binary, label, label_address);
    cout<<"part 3. finish"<<endl;
    // for (int r=0; r<split_vector_wordbyword_1.size(); r++)
    // {
    //     for (int t=0; t<split_vector_wordbyword_1[r].size(); t++)
    //     {
    //         cout << "split_vector_wordbyword1 [" << r << "]" << "[" << t << "]" << split_vector_wordbyword_1[r][t] << endl;
    //     }   
    // }
    cout<<"������Ʈ"<<endl;
    for(int i=0; i<word_directives.size(); i++)
    {
        cout<<word_directives[i]<<endl;
        cout<<word_address[i]<<endl;   
    }
    cout<<"����Ʈ"<<endl;
    for(int i=0; i<label.size(); i++)
    {
        cout<<label[i]<<endl;
        cout<<label_address[i]<<endl;   
    }
    cout<<"���̳ʸ���Ʈ"<<endl;
    for(int i=0; i<instruction_binary.size(); i++)
    {
        cout<<instruction_binary[i]<<endl;
        cout<<instruction_address[i]<<endl;   
    }

    string Name_output=argv[1];
    Name_output=strtok(filePath, ".s");
    Name_output.append(".o");
    const char * name_of_output = Name_output.c_str();

	// write File
	ofstream writeFile(name_of_output);
	if( writeFile.is_open() )
    {
		int text_section_size=4*instruction_address.size();
        string text_section_size_hex=hex_to_dec(text_section_size);
        //----------<text section size>
        writeFile << text_section_size_hex<<endl;

        int data_section_size=4*word_address.size();
        string data_section_size_hex=hex_to_dec(data_section_size);
        //----------<data section size>
        writeFile << data_section_size_hex<<endl;
        
        //-----------<instruction binary>
        for (int i=0; i<instruction_binary.size(); i++)
        {
            cout<<instruction_binary[i]<<endl;
            unsigned int n=binary_to_ten(instruction_binary[i]);
            cout<<n<<endl;
            string a=hex_to_dec(n);
            cout<<a<<endl;
            writeFile << a<<endl;
        }
        //-----------<word_value>
        for (int i=0; i<word_directives.size(); i++)
        {
            if(word_directives[i][1]=='x')
            {
                writeFile << word_directives[i]<<endl;
            }
            else
            {
                int num = atoi(word_directives[i].c_str());//string�� int��
                string a=hex_to_dec(num);
                writeFile << a<<endl;
            }
            
        }
		writeFile.close();
	}


    // text_detect(split_vector_wordbyword_1, locate_text, label, label_address, instruction_address, instruction_binary);
    // cout<<instruction_binary[0]<<label[3]<<endl;
    
    // cout<<split_vector_wordbyword_2[4]<<endl;
    // cout<<split_vector_wordbyword_2[5]<<endl;
    // cout<<split_vector_wordbyword_2[6]<<endl;

    return 0;

}

string binary_inst_R_op(string s)
{
    if (s=="addu")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="and")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="jr")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="nor")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="or")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="sltu")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="sll")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="srl")
    {
        return bitset<6>(0).to_string();
    }
    if (s=="subu")
    {
        return bitset<6>(0).to_string();
    }//R format
}

string binary_inst_R_funct(string s)
{
    if (s=="addu")
    {  
        string sixth = "0x21";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="and")
    {
        string sixth = "0x24";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="jr")
    {
        string tenth = "8";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="nor")
    {
        string sixth = "0x27";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="or")
    {
        string sixth = "0x25";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sltu")
    {
        string sixth = "0x2b";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sll")
    {
        string tenth = "0";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="srl")
    {
        string tenth = "2";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="subu")
    {
        string sixth = "0x23";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else
    {
        return "No anything";
    }

}


//R ������ �ν�Ʈ���� ���̳ʸ�ȭ �Լ�//��� ��쿡 ���ؼ� 16���� �о������ ��ġ��.
string binary_inst(vector<string> s, vector<string> la) // la�߰�����//jformat ��ġ��
{
       
    string output;
    string b;
    if (s[0]=="addu"||s[0]=="and"||s[0]=="nor"||s[0]=="or"||s[0]=="sltu"||s[0]=="subu")
    {
        //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)//�з��Ҷ� ���ڸ� �̴°� �ƴ϶� 0x�з�, ���ο����� �з� �����ؾߵ�
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            s[i]=bitset<5>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        //���� 32bit binarycode or ���� ���Ѵ��� 16����... �̰Ŵ� �� �����غ���, binary������ �����غ��� �ϴ�
        
        b=binary_inst_R_funct(s[0]);
        s[0]=binary_inst_R_op(s[0]);
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[3]);
        output.append(s[1]);
        output.append("00000");
        output.append(b);

        return output;
    }
    else if (s[0]=="sll")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            s[i]=bitset<5>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        output.append(binary_inst_R_op(s[0]));
        output.append("00000");
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);
        output.append("000000");
        return output;
    }
    else if (s[0]=="srl")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            s[i]=bitset<5>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        output.append(binary_inst_R_op(s[0]));
        output.append("00000");
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);
        output.append("000010");
        return output;
    }
    else if (s[0]=="jr")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            
            for (int j=0; j<s[i].length(); j++)
            {
                
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            s[i]=bitset<5>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        b=binary_inst_R_funct(s[0]);
        output.append(binary_inst_R_op(s[0]));
        output.append(s[1]);
        output.append("000000000000000");
        output.append(b);
        return output;
    }
    else if (s[0]=="addiu"||s[0]=="andi"||s[0]=="ori"||s[0]=="sltiu")
    {
        //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            if (i==(s.size()-1))
            {   

                int num = atoi(s[i].c_str());//string�� int��
                s[i]=bitset<16>(num).to_string();
            }
            else
            {
                int num = atoi(s[i].c_str());//string�� int��
                s[i]=bitset<5>(num).to_string();
            }
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        //���� 32bit binarycode or ���� ���Ѵ��� 16����... �̰Ŵ� �� �����غ���, binary������ �����غ��� �ϴ�
        
        s[0]=binary_inst_I_op(s[0]);

        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);

        return output;
    }
    // else if (s[0]=="la")
    // {
    //     string ox="0x";
    //     string ox1="0x";
    //     vector<string> a;
    //     vector<string> b;
    //     int n;
    //     cout<<"passpoint-1"<<endl;
    //     //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
    //     for (int j=0; j<s[1].length(); j++)
    //     {
    //         if (isdigit(s[1][j])==0)
    //         {
    //             s[1].erase(j,1);
    //             j--;
    //         }
    //     }
        
    //     cout<<"passpoint-2"<<endl;
    //     cout<<s[2]<<endl;
    //     string front=s[2].substr(2,4);
    //     cout<<front<<endl;
    //     string last=s[2].substr(6,4);
    //     cout<<last<<endl;

    //     if(front!="0000")
    //     {
    //         cout<<"passpoint-3"<<endl;
    //         ox.append(front);
    //         s[0]="lui";
    //         s[2]=ox;

    //         a.push_back(s[0]);
    //         a.push_back(s[1]);
    //         a.push_back(s[2]);
    //         cout<<a[0]<<a[1]<<a[2]<<endl;
    //         cout<<"����?"<<endl;
    //         binary_inst(a,la);
    //         cout<<"����?"<<endl;
    //     }
    //     if(last!="0000")
    //     {
    //         cout<<"passpoint-4"<<endl;
    //         ox1.append(last);
    //         s[0]="ori";
    //         s[2]=ox1;
    //         b.push_back(s[0]);
    //         b.push_back(s[1]);
    //         b.push_back(s[1]);
    //         b.push_back(s[2]);
    //         cout<<b[0]<<b[1]<<b[2]<<b[3]<<endl;
    //         binary_inst(b,la);
    //     }
    // }
    else if (s[0]=="beq")
    {
        //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }

            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        //���� 32bit binarycode or ���� ���Ѵ��� 16����... �̰Ŵ� �� �����غ���, binary������ �����غ��� �ϴ�
        int label_adds=atoi(s[3].c_str());
        string sixth = "0x00400000";
        sixth.erase(0,2);
        int _0x004 = stoi(sixth, nullptr, 16);
        string label_addres=la[la.size()-1];
        label_addres.erase(0,2);
        int ins = stoi(label_addres, nullptr, 16);
        int final_offset;
        final_offset=(label_adds-(_0x004+(ins*4+4))/4);
        s[3]=bitset<16>(final_offset).to_string();

        s[0]=binary_inst_I_op(s[0]);
        int num = atoi(s[1].c_str());
        s[1]=bitset<5>(num).to_string();
        int num1 = atoi(s[2].c_str());
        s[2]=bitset<5>(num1).to_string();
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        output.append(s[3]);

        return output;
    }
    else if (s[0]=="bne")
    {
        //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }

            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        //���� 32bit binarycode or ���� ���Ѵ��� 16����... �̰Ŵ� �� �����غ���, binary������ �����غ��� �ϴ�
        int label_adds=atoi(s[3].c_str());
        cout<<"lookathere"<<endl;
        cout<<label_adds<<endl;
        string sixth = "0x00400000";
        sixth.erase(0,2);

        string label_addres=la[la.size()-1];
        label_addres.erase(0,2);
        int ins = stoi(label_addres, nullptr, 16);
        cout<<ins<<endl;
        int final_offset;
        final_offset=(label_adds-(ins+4))/4;
        cout<<final_offset<<endl;
        s[3]=bitset<16>(final_offset).to_string();

        s[0]=binary_inst_I_op(s[0]);
        int num = atoi(s[1].c_str());
        s[1]=bitset<5>(num).to_string();
        int num1 = atoi(s[2].c_str());
        s[2]=bitset<5>(num1).to_string();
        output.append(s[0]);
        output.append(s[1]);
        output.append(s[2]);
        output.append(s[3]);

        return output;
    }
    else if (s[0]=="lui")
    {
        for (int i=1; i<s.size(); i++)
        {
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            if (i==(s.size()-1))
            {
                int num = atoi(s[i].c_str());
                s[i]=bitset<16>(num).to_string();  
            }
            else
            {
                int num = atoi(s[i].c_str());//string�� int��
                s[i]=bitset<5>(num).to_string();
            }
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        output.append(binary_inst_I_op(s[0]));
        output.append("00000");
        output.append(s[1]);
        output.append(s[2]);
        return output;
    }
    else if (s[0]=="lw"||s[0]=="lb"||s[0]=="sw"||s[0]=="sb")
    {
        //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
        string a;
        for (int i=1; i<s.size(); i++)
        {
            if(i==(s.size()-1))//���������� ()�ȿ� �ִ� ���ڸ� ����
            {
                int j=0;
                while(s[i][j]!='(')
                {
                    a+=s[i][j];//��������
                    s[i][j]='*';
                    j++;
                }
            }
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                string str1 = to_string(nDec);
                s[i]=str1;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            s[i]=bitset<5>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        //���� 32bit binarycode or ���� ���Ѵ��� 16����... �̰Ŵ� �� �����غ���, binary������ �����غ��� �ϴ�
        
        s[0]=binary_inst_I_op(s[0]);
        output.append(s[0]);
        output.append(s[2]);
        output.append(s[1]);
        int num = atoi(a.c_str());
        output.append(bitset<16>(num).to_string());

        return output;
    }
    else if(s[0]=="j"||s[0]=="jal")
    {
        for (int i=1; i<s.size(); i++)
        {
            // cout<<"�����?2"<<endl;
            if (s[i][1]=='x')//16������ ���� ã�� �ڵ�
            {
                s[i].erase(0,2);
                int nDec = stoi(s[i], nullptr, 16);
                nDec=nDec/4;
                string str1 = to_string(nDec);
                s[i]=str1;
                // cout<<s[i]<<endl;
            }
            for (int j=0; j<s[i].length(); j++)
            {
                if (isdigit(s[i][j])==0)
                {
                    s[i].erase(j,1);
                    j--;
                }
                //����ϰ� ���ڸ� ����ϵ��� �ϴ� �ڵ� str�� ���������� ����
            }
            int num = atoi(s[i].c_str());//string�� int��
            // cout<<num<<endl;
            s[i]=bitset<26>(num).to_string();
            //���ڸ� 2������ �ٲٴ� �ڵ�
        }
        s[0]=binary_inst_J_op(s[0]);
        output.append(s[0]);
        output.append(s[1]);
        // cout<<output<<endl;
        return output;
    }
    else
    {
        output.append("not yet");
        return output;
    }

}

string binary_inst_I_op(string s)
{
    if (s=="addiu")
    {  
        string tenth = "9";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="andi")
    {
        string sixth = "0xc";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="beq")
    {
        string tenth = "4";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="lui")
    {
        string sixth = "0xf";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="bne")
    {
        string tenth = "5";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
    else if (s=="lw")
    {
        string sixth = "0x23";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="lb")
    {
        string sixth = "0x20";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="ori")
    {
        string sixth = "0xd";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sltiu")
    {
        string sixth = "0xb";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }
    else if (s=="sw")
    {
        string sixth = "0x2b";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else if (s=="sb")
    {
        string sixth = "0x28";
        sixth.erase(0,2);
        int nDec = stoi(sixth, nullptr, 16);
        return bitset<6>(nDec).to_string();
    }//R format
    else
    {
        return "No anything";
    }
}

string binary_inst_J_op(string s)
{
    if (s=="jal")
    {
        string tenth = "3";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();

    }
    if (s=="j")
    {
        string tenth = "2";
        int num = atoi(tenth.c_str());
        return bitset<6>(num).to_string();
    }
}


void data_detect(vector<vector<string>> &s, int x, int y, vector<string> &w_ad, vector<string> &w_d, vector<string> &lb, vector<string> &lba)
{
    string sixth = "0x10000000";
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    for(int i=start; i<y; i++)
    {
        if(s[i].size()==0)
        {
            
        }
        else
        {
            for(int t=0; t<s[i].size(); t++)
            {
                if (s[i][t]==".word")
                {   
                    // cout<<s[i][t+1]<<endl;
                    w_d.push_back(s[i][t+1]);
                    w_ad.push_back(hex_to_dec(nDec));
                    //int�� 16������ ��ȯ�ϴ� ��� �˾Ƴ���
                }
            }

            int j= s[i][0].length()-1;
            if(s[i][0][j]==':')
            {   
                s[i][0].erase(j,1);
                // cout<<s[i][0]<<endl;
                lb.push_back(s[i][0]);
                // cout<<hex_to_dec(nDec)<<endl;
                lba.push_back(hex_to_dec(nDec));//[i]��°�� �ش��ϴ� word�� �ּ� �����ϱ�.                 
            }
            nDec+=4; 
        } 
    }
}

void text_detect(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba)
{
    string sixth = "0x00400000";
    string a;
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    for(int i=start; i<s.size(); i++)
    {

        if(s[i].size()!=0)
        {
            int j=s[i][0].size()-1;
            if(s[i][0][j]==':')
            {
                a=s[i][0];
                a.erase(j,1);
                lb.push_back(a);
                lba.push_back(hex_to_dec(nDec));
                // cout<<nDec<<endl;
            }            
        }
        if (s[i].size()==0)
        {
            nDec-=4;            
        }
        if(s[i].size()!=1)
        {
        nDec+=4;            
        }
    }
    // for (int i=start; i<s.size(); i++)
    // {
    //     int t=s[i][0].size()-1;
    //     if(s[i].size()!=1)
    //     {
    //         if(s[i][0][t]==':')
    //         {
    //             s[i].erase(s[i].begin());
    //             cout<<"passpass"<<s[i][0]<<endl;
    //         }
    //     }
    // }
    // cout<<"passpoint_here1"<<endl;
    // string sixth = "0x00400000";
    // sixth.erase(0,2);
    // int nDec = stoi(sixth, nullptr, 16);
    // int start=x+1;
    // cout<<"passpoint_here2"<<endl;
    // for (int i=start; i<(s.size()); i++)//����ִ� ���� ����
    // {   
    //     if(s[i].size()==0)
    //     {
    //         nDec-=4;
    //     }
    //     else
    //     {
    //         cout<<"passpoint_here3"<<endl;
    //         int j= s[i][0].length()-1;
    //         if(s[i][0][j]==':')//���� �νĵǸ� �� ������ ���Ϳ� �����Ѵ�
    //         {
    //             s[i][0].erase(j,1);
    //             cout<<"passpoint_here4"<<endl;
    //             cout<<s[i][0]<<endl;
    //             cout<<nDec<<endl;
    //             lb.push_back(s[i][0]);
    //             lba.push_back(hex_to_dec(nDec));
    //         //[i]��°�� �ش��ϴ� word�� �ּ� �����ϱ�.                 
    //         }
    //     nDec+=4;
    //     }
    // }
    // nDec = stoi(sixth, nullptr, 16);
    // for (int i=start; i<(s.size()); i++)//����ִ� ���� ����
    // {   
    //     if(s[i].size()==0)
    //     {
    //         nDec-=4;
    //     }
    //     else
    //     {
    //         if(s[i].size()!=1)//�󺧸� ������ �Ÿ���.//�󺧸� ������� �ּҰ��� ������ �ʵ��� ��������
    //         {
    //             cout<<"passpoint_instruction"<<endl;
    //             int j= s[i][0].length()-1;
    //             if(s[i][0][j]==':')
    //             {
    //                 s[i].erase(s[i].begin());
    //             }
    //             inst_lb_change(s[i], lb, lba); //�ٲ��ش�����
    //             i_b.push_back(binary_inst(s[i])); 
    //             i_adds.push_back(hex_to_dec(nDec));
    //         }
    //     nDec+=4;
    //     }
    // }

}

string hex_to_dec(unsigned int x)
{
	unsigned int remainder; 
	unsigned int quotient;
	unsigned int i = 1, j, temp;
	string hex;
	string new_hex;

	quotient = x;
	while (quotient != 0) {
		temp = quotient % 16;
		//To convert integer into character
		if (temp < 10)
		{
			temp = temp + 48;
		}
		else 
		{
			temp = temp + 55;
		}
		hex.push_back(temp);
		quotient = quotient / 16;
	}

	new_hex.push_back('0');
	new_hex.push_back('x');
	for (int i = hex.size()-1; i >= 0; i--)
	{
		hex[i] = tolower(hex[i]);
		new_hex.push_back(hex[i]);
	}
	return new_hex;
} 

void inst_lb_change(vector<string> &s, vector<string> lb, vector<string> lb_ad)//�ν�Ʈ������ label�� ��ü������
{
    // cout<<"s[i][0]"<<s[0]<<endl;
    for (int i=1; i<s.size(); i++)
    {
        for (int j=0; j<lb.size(); j++ )
        {
            if (s[i]==lb[j])
            {
                // cout<<i<<endl;
                // cout<<"here!!!!"<<s[i]<<endl;
                s[i]=lb_ad[j];
                // cout<<"here!!!!"<<s[i]<<endl;
            }
        }
    }
}

void text_detect_exe(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba)
{
    cout<<"����"<<endl;
    string sixth = "0x00400000";
    string a;
    sixth.erase(0,2);
    int nDec = stoi(sixth, nullptr, 16);
    int start=x+1;
    cout<<"����2"<<endl;
    for (int i=start; i<s.size(); i++)
    {
        cout<<s[i][0]<<"����3"<<endl;
        if(s[i].size()!=0)
        {
            cout<<"����4"<<endl;
            int t=s[i][0].size()-1;
            if(s[i].size()!=1)
            {   
                cout<<"����5"<<endl;
                if(s[i][0][t]==':')
                {
                    cout<<"����6"<<endl;
                    cout<<s[i][0]<<endl;
                    s[i].erase(s[i].begin());
                    cout<<s[i][0]<<endl;
                } //�ٲ��ش�����
                inst_lb_change(s[i], lb, lba);
                // cout<<s[i][0]<<s[i][1]<<endl;
                // cout<<hex_to_dec(nDec)<<endl;
                if(s[i][0]=="la")
                {
                    string ox="0x";
                    string ox1="0x";
                    vector<string> a;
                    vector<string> b;
                    int n;
                    //�� �Լ��� ����ϴ� ������ ����� �ڵ忡 ��ƾ���
                    for (int j=0; j<s[i][1].length(); j++)
                    {
                        if (isdigit(s[i][1][j])==0)
                        {
                            s[i][1].erase(j,1);
                            j--;
                        }
                    }
                    cout<<s[i][2]<<endl;
                    string front=s[i][2].substr(2,4);
                    cout<<front<<endl;
                    string last=s[i][2].substr(6,4);
                    cout<<last<<endl;

                    if(front!="0000")
                    {
                        cout<<"passpoint-3"<<endl;
                        ox.append(front);
                        s[i][0]="lui";
                        s[i][2]=ox;

                        a.push_back(s[i][0]);
                        a.push_back(s[i][1]);
                        a.push_back(s[i][2]);
                        cout<<a[0]<<a[1]<<a[2]<<endl;
                        i_adds.push_back(hex_to_dec(nDec));
                        i_b.push_back(binary_inst(a,lba));
                        nDec+=4;

                    }
                    if(last!="0000")
                    {
                        cout<<"passpoint-4"<<endl;
                        ox1.append(last);
                        s[i][0]="ori";
                        s[i][2]=ox1;
                        b.push_back(s[i][0]);
                        b.push_back(s[i][1]);
                        b.push_back(s[i][1]);
                        b.push_back(s[i][2]);
                        cout<<b[0]<<b[1]<<b[2]<<b[3]<<endl;
                        i_adds.push_back(hex_to_dec(nDec));
                        i_b.push_back(binary_inst(b,lba));
                        nDec+=4;
                    }
                }
                else
                {
                    i_adds.push_back(hex_to_dec(nDec));
                    i_b.push_back(binary_inst(s[i],lba)); 
                    nDec+=4;
                }
                // cout<<binary_inst(s[i],i_adds)<<endl;
                // nDec+=4;
            }
            else
            {
                /* code */
            }
              
        }
        else
        {
            /* code */
        }
    cout<<"����7"<<endl;
    }
    cout<<"����8"<<endl;
}

unsigned int binary_to_ten(string s)
{
	unsigned int result = 0;
	int a = 1;
	for (int i = s.length() - 1;i >= 0;i--)
	{
		for (int j = 0; j < s.length() - i - 1; j++)
		{
			a *= 2;
		}
		if (s[i] == '1')
		{
			result += a;
		}
		a = 1;
	}
	return result;
}