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
#include <cmath>
using namespace std;
//?????? ???? ????????? ???????

// string hex_to_dec(unsigned int x);
// string binary_inst_R_op(string s);
// string binary_inst(vector<string> s, vector<string> la);
// string binary_inst_R_funct(string s);
// string binary_inst_I_op(string s);
// string binary_inst_J_op(string s);
// void data_detect(vector<vector<string>> &s, int x, int y, vector<string> &w_ad, vector<string> &w_d, vector<string> &lb, vector<string> &lba);
// void text_detect(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);
// void text_detect_exe(vector<vector<string>> &s, int x,vector<string> &i_adds, vector<string> &i_b, vector<string> &lb, vector<string> &lba);

// void inst_lb_change(vector<string> &s, vector<string> lb, vector<string> lb_ad);
// unsigned int binary_to_ten(string s);
vector<string> Register{"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "R8", "R9", "R10", "R11",
                        "R12", "R13", "R14", "R15", "R16", "R17", "R18", "R19", "R20", "R21",
                        "R22", "R23", "R24", "R25", "R26", "R27", "R28", "R29", "R30", "R31"};
vector<string> Register_value{"0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0",
                              "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0",
                              "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0", "0x0"};
//1. ??��??? ?????? ???
vector<string> File_in_vector;
vector<string> datas;
vector<int> datas_address_int;
vector<string> instructions;
vector<string> instructions_binary;
vector<int> instructions_address_int;

vector<string> input_option;


string hex_to_dec(unsigned int x);
string detect_instruction(string s);
void operate_instruction(string s, string b, int &pc);
unsigned int sixth_to_int(string s);
unsigned int binary_to_ten(string s);
int find(vector<int> a, unsigned int b);

string inst_num = "0x400000";
int inst_num_int = sixth_to_int(inst_num);

string data_num = "0x10000000";
int data_num_int = sixth_to_int(data_num);

int main(int argc, const char *argv[])
{
    string str;
    //1.������ �ɼ��� �д´�
    for (int i=0; i<argc; i++)
    {
        cout << argv[i] <<endl;
        input_option.push_back(argv[i]);
    }
    //detect file
    int op_m, op_d, op_n, operation_number = 0;
    string m_range1, m_range2;
    cout<<"pass"<<endl;
    for (int i=0; i<argc; i++)
    {
        if(argv[i][1]=='m')
        {
            op_m = 1;
            int a;
            for (int t=0; t<strlen(argv[i+1]); t++)
            {
                if(argv[i+1][t]==':')
                {
                    cout<<t<<endl;
                    a=t;
                }
            }
            string ar =argv[i+1];
            string arr = argv[i+1];
            // cout<<ar<<endl;
            m_range1 = ar.erase(a);
            m_range2 = arr.erase(0, a+1);
            // cout<<m_range1<< " "<<m_range2<<endl;
            // cout<<typeid(m_range1).name()<<typeid(m_range2).name()<<endl;
        }
        else if (argv[i][1]=='d')
        {
            op_d = 1;
            // cout<<"d"<<op_d<<endl;
        }
        else if (argv[i][1]=='n')
        {

            op_n = 1;
            string n_num =argv[i+1];
            operation_number = stoi(n_num);
            cout<<operation_number<<endl;
            // cout<<"n"<<op_n<<endl;
        }
    }//output은 op_n/ op_d/ op_m/ operation_number/ m_range1/ m_range2
    
    // char filePath[100]; //??��? ??????????
    // strcpy(filePath, argv[argc-1]);

    // //2.������ �ؼ��Ѵ�.
    // //2-1. ������ ���庰�� �о�´�.
    // ifstream InputFile(filePath);
    // if (InputFile.is_open())
    // {
    //     while (!InputFile.eof())
    //     {
    //         getline(InputFile, str);
    //         if (str.length() != 0)
    //         {
    //             File_in_vector.push_back(str);
    //         }
    //     }
    //     // for (int i = 0; i < File_in_vector.size(); i++)
    //     // {
    //         // cout << File_in_vector[i] << endl;
    //     // }
    //     InputFile.close();
    // }
    // //������ �о� �� �Ŀ� ù��°�� �ι�° ������ �ν��Ѵ�
    // int inst_size = sixth_to_int(File_in_vector[0])/4;
    // int data_size = sixth_to_int(File_in_vector[1])/4;
    // cout<<inst_size<<data_size<<endl;
    // //�����Ϳ� �ν�Ʈ������ ��� ����� �����.
    // for (int i=2; i<File_in_vector.size(); i++)
    // {
    //     if (i<2+inst_size)
    //     {
    //         cout<<"ins : "<<File_in_vector[i]<<endl;
    //         instructions.push_back(File_in_vector[i]);
    //         string s =bitset<32>(sixth_to_int(File_in_vector[i])).to_string();
    //         instructions_address_int.push_back(inst_num_int);
    //         cout<<inst_num_int<<endl;
    //         inst_num_int = inst_num_int + 4;
    //         // cout<<s<<endl;
    //         instructions_binary.push_back(s);
    //     }
    //     else
    //     {
    //         cout<<"data : "<<File_in_vector[i]<<endl;
    //         datas.push_back(File_in_vector[i]);
    //         datas_address_int.push_back(data_num_int);
    //         cout<<data_num_int<<endl;
    //         data_num_int = data_num_int + 4;
            

    //     }
    // }
    // //�Էµ� �ν�Ʈ���ǵ��� � �ν�Ʈ�������� �ν��ϰ�, �����ϴ� �ܰ�, �ϴ� ���θ� �����ϰ� ���߿� ������ �޾� ���ళ���� ���Ѵ�.

    // int a1 = 4194304;
    // int n = 19;
    // int _pc = a1;
    // for (int j=0; j<n; j++)//���ళ���� �޾ƿ�
    // {
    //     for(int i=0; i<instructions_address_int.size(); i++)
    //     {
    //         cout<<instructions_address_int[i]<<endl;
    //     }
    //     cout<< _pc << endl;
    //     cout<<find(instructions_address_int, _pc)<<endl;
    //     cout<<"here"<<endl;
    //     int i = find(instructions_address_int, _pc);
    //     cout<<detect_instruction(instructions_binary[i])<<endl;
    //     operate_instruction(detect_instruction(instructions_binary[i]), instructions_binary[i], _pc); 
    // }

    

    return 0;
}

unsigned int sixth_to_int(string s)
{
    s.erase(0, 2);
    unsigned int nDec = stoul(s, nullptr, 16);
    return nDec;
}

// string int_to_binary(int a, int num);
// {
//     return bitset<num>(a).to_string();
// }

unsigned int binary_to_ten(string s)
{
    unsigned int result = 0;
    int a = 1;
    for (int i = s.length() - 1; i >= 0; i--)
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

string detect_instruction(string s)
{
    string opbi_6 = s.substr(0, 6);
    string fnbi_6 ;
    //= s.substr(26, 6)
    unsigned int op_num = binary_to_ten(opbi_6);
    unsigned int funct_num;
    //= binary_to_ten(fnbi_6)
    //R format first
    if (op_num == 0 )
    {
        fnbi_6 = s.substr(26, 6);
        funct_num = binary_to_ten(fnbi_6);
        if (funct_num == 33)
        {
            return "Raddu";
        }
        else if (funct_num == 36)
        {
            return "Rand";
        }
        else if (funct_num == 8)
        {
            return "Rjr";
        }
        else if (funct_num == 39)
        {
            return "Rnor";
        }
        else if (funct_num == 37)
        {
            return "Ror";
        }
        else if (funct_num == 43)
        {
            return "Rsltu";
        }
        else if (funct_num == 0)
        {
            return "Rsll";
        }
        else if (funct_num == 2)
        {
            return "Rsrl";
        }
        else if (funct_num == 35)
        {
            return "Rsubu";
        }
        else
        {
            cout<< "no operation, check detect_instruction"<<endl;
            return "ERROR!";
        }
        
    }
    //I format
    else if (op_num == 9)
    {
        return "Iaddiu";
    }
    else if (op_num == 12)
    {
        return "Iandi";
    }
    else if (op_num == 4)
    {
        return "Ibeq";
    }
    else if (op_num == 5)
    {
        return "Ibne";
    }
    else if (op_num == 15)
    {
        return "Ilui";
    }
    else if (op_num == 35)
    {
        return "Ilw";
    }
    else if (op_num == 32)
    {
        return "Ilb";
    }
    else if (op_num == 13)
    {
        return "Iori";
    }
    else if (op_num == 11)
    {
        return "Isltiu";
    }
    else if (op_num == 43)
    {
        return "Isw";
    }
    else if (op_num == 40)
    {
        return "Isb";
    }
    //J-format
    else if (op_num == 2)
    {
        return "Jj";
    }
    else if (op_num == 3)
    {
        return "Jjal";
    }
    else
    {
        cout<<"no operation, check detect_instruction"<<endl;
        return "something_problem";
    }
}

void operate_instruction(string s, string b, int &pc)
{
    if (s[0] == 'R')
    {
        string rs, rt, rd, shamt;
        int rs_num, rt_num, rd_num;
        rs = b.substr(6, 5);
        rt = b.substr(11, 5);
        rd = b.substr(16, 5);
        rs_num = binary_to_ten(rs);
        rt_num = binary_to_ten(rt);
        rd_num = binary_to_ten(rd);
        shamt = b.substr(21, 5);
        int save_value_int;
        string save_value;
        if (s == "Raddu")
        {
            save_value_int = sixth_to_int(Register_value[rs_num]) + sixth_to_int(Register_value[rt_num]);
            save_value = hex_to_dec(save_value_int);
            Register_value[rd_num] = save_value;
            pc = pc + 4;
        }
        else if (s == "Rand")
        {
            string binary_rs, binary_rd, binary_rt;
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            binary_rd = bitset<32>(sixth_to_int(Register_value[rd_num])).to_string();
            binary_rt = bitset<32>(sixth_to_int(Register_value[rt_num])).to_string();
            for (int i; i<rs.size(); i++)
            {
                if (binary_rs[i]=='1' && binary_rt[i]=='1')
                {
                    binary_rd[i]=='1';
                }
                else
                {
                    binary_rd[i]=='0';
                }
                //and operation

            }
            // cout<< binary_rs << " " << binary_rt <<endl;
            Register_value[rd_num] = hex_to_dec(binary_to_ten(binary_rd));
            // cout<<Register_value[rd_num]<<hex_to_dec(binary_to_ten(binary_rd))<<endl;
            pc =pc+4;
        }
        else if (s == "Rjr")
        {
            pc = sixth_to_int(Register_value[rs_num]);
        }
        else if (s == "Rnor")
        {
            string binary_rs, binary_rd, binary_rt;
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            binary_rd = bitset<32>(sixth_to_int(Register_value[rd_num])).to_string();
            binary_rt = bitset<32>(sixth_to_int(Register_value[rt_num])).to_string();
            for (int i; i<rs.size(); i++)
            {
                if (binary_rs[i]=='0' && binary_rt[i]=='0')
                {
                    binary_rd[i]='1';
                }
                else
                {
                    binary_rd[i]='0';
                }
                //end operation
            }
            // cout<< binary_rs << " " << binary_rt <<endl;
            Register_value[rd_num] = hex_to_dec(binary_to_ten(binary_rd));
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
            // cout<<Register_value[rd_num]<<hex_to_dec(binary_to_ten(binary_rd))<<endl;
        }
        else if (s == "Ror")
        {
            string binary_rs, binary_rd, binary_rt;
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            binary_rd = bitset<32>(sixth_to_int(Register_value[rd_num])).to_string();
            binary_rt = bitset<32>(sixth_to_int(Register_value[rt_num])).to_string();
            for (int i; i<rs.size(); i++)
            {
                if (binary_rs[i]=='0' && binary_rt[i]=='0')
                {
                    binary_rd[i]='0';
                }
                else
                {
                    binary_rd[i]='1';
                }
                //end operation
            }
            // cout<< binary_rs << " " << binary_rt <<endl;
            Register_value[rd_num] = hex_to_dec(binary_to_ten(binary_rd));
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
            // cout<<Register_value[rd_num]<<hex_to_dec(binary_to_ten(binary_rd))<<endl;
        }
        else if (s == "Rsltu")
        {
            string binary_rs, binary_rd, binary_rt;
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            binary_rd = bitset<32>(sixth_to_int(Register_value[rd_num])).to_string();
            binary_rt = bitset<32>(sixth_to_int(Register_value[rt_num])).to_string();
            if (sixth_to_int(Register_value[rs_num])<sixth_to_int(Register_value[rt_num]))
            {
                Register_value[rd_num] = hex_to_dec(1);
            }
            else
            {
                Register_value[rd_num] = hex_to_dec(0);
            }
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Rsll")
        {
            int a, rd_val;
            a = pow(2,binary_to_ten(shamt));
            rd_val = sixth_to_int(Register_value[rt_num]) * a;
            Register_value[rd_num] == hex_to_dec(rd_val);
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Rsrl")
        {
            int a, rd_val;
            a = pow(2,binary_to_ten(shamt));
            rd_val = sixth_to_int(Register_value[rt_num]) / a;
            Register_value[rd_num] == hex_to_dec(rd_val);
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Rsubu")
        {
            save_value_int = sixth_to_int(Register_value[rs_num]) - sixth_to_int(Register_value[rt_num]);
            save_value = hex_to_dec(save_value_int);
            Register_value[rd_num] = save_value;
            cout<<Register_value[rd_num]<<endl;
            pc =pc+4;
        }
        
    }
    else if (s[0] == 'I')
    {
        string rs, rt, imm;
        int rs_num, rt_num;
        rs = b.substr(6, 5);
        rt = b.substr(11, 5);
        imm = b.substr(16, 16);
        rs_num = binary_to_ten(rs);
        rt_num = binary_to_ten(rt);

        if (s == "Iaddiu")
        {
            //sign - extended
            string c;
            int t=0;
            while (imm[t]!='1')
            {
                imm[t]='1';
                t++;
            }
            cout<<imm<<endl;
            for (int i=0; i<32-imm.size(); i++)
            {
                c.append("1");
            }
            c.append(imm);
            imm = c;
            cout<<imm<<endl;
            int a = sixth_to_int(Register_value[rs_num]) + binary_to_ten(imm);
            Register_value[rt_num] = hex_to_dec(a);
            cout<<Register_value[rt_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Iandi")
        {
            string binary_imm, binary_rs; 
            string a = "00000000000000000000000000000000";
            binary_imm = bitset<32>(binary_to_ten(imm)).to_string();
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            for (int i; i<binary_imm.size(); i++)
            {
                if (binary_rs[i]=='1' && binary_imm[i]=='1')
                {
                    a[i]='1';
                }
                else
                {
                    a[i]='0';
                }

            }
            Register_value[rt_num] = hex_to_dec(binary_to_ten(a));
            cout<<Register_value[rt_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Ibeq")
        {
            if (Register_value[rs_num]==Register_value[rt_num])
            {
                pc = pc + binary_to_ten(imm)*4+4;
            }
            else
            {
                pc = pc+4;
            }
            
        }
        else if (s == "Ibne")
        {
            if (Register_value[rs_num]!=Register_value[rt_num])
            {
                cout<<"if pass"<<endl;
                pc = pc + binary_to_ten(imm)*4+4;
            }
            else
            {
                cout<<"else pass"<<endl;
                pc = pc+4;
            }
        }
        else if (s == "Ilui")
        {
            string s;
            s.append(imm);
            s.append("000000000000000");
            Register[rt_num] = hex_to_dec(binary_to_ten(s));
            cout<<Register_value[rt_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Ilw")
        {
            // int a= sixth_to_int(Register_value[rs_num])  + binary_to_ten(imm);
            // if (find(datas_address_int, a)==999 && find(instructions_address_int, a)==999)
            // {
            //     Register_value[rt_num] = "0x0";
            // }
            // else if (find(datas_address_int, a)==999)
            // {
            //     Register_value[rt_num]=instructions[find(instructions_address_int, a)];
            // }
            // else 
            // {
            //     Register_value[rt_num]=datas[find(datas_address_int, a)];
            // }
            pc = pc + 4;
        }
        else if (s == "Ilb")
        {
            // cout<<"pass"<<endl;
            // unsigned int a= sixth_to_int(Register_value[rs_num])  + binary_to_ten(imm);
            // cout<<"pass1"<<endl;
            // if (find(datas_address_int, a)==999)
            // {
            //     cout<<"pass2"<<endl;
            //     int size = instructions_binary[find(instructions_address_int, a)].size();
            //     string s ="";
            //     for (int i=0; i<32-size; i++)
            //     {
            //         s.append("1");
            //     }
            //     s.append(instructions_binary[find(instructions_address_int, a)]);
            //     Register_value[rt_num] = hex_to_dec(binary_to_ten(s));
            // }
            // else 
            // {
            //     cout<<"pass2"<<endl;
            //     int size = instructions_binary[find(datas_address_int, a)].size();
            //     string s ="";
            //     for (int i=0; i<32-size; i++)
            //     {
            //         s.append("1");
            //     }
            //     s.append(instructions_binary[find(instructions_address_int, a)]);
            //     Register_value[rt_num] = hex_to_dec(binary_to_ten(s));
            // }
            pc = pc + 4;
        }
        else if (s == "Iori")
        {
            string binary_imm, binary_rs; 
            string a = "00000000000000000000000000000000";
            binary_imm = bitset<32>(binary_to_ten(imm)).to_string();
            binary_rs = bitset<32>(sixth_to_int(Register_value[rs_num])).to_string();
            for (int i; i<binary_imm.size(); i++)
            {
                if (binary_rs[i]=='0' && binary_imm[i]=='0')
                {
                    a[i]='0';
                }
                else
                {
                    a[i]='1';
                }

            }
            Register_value[rt_num] = hex_to_dec(binary_to_ten(a));
            cout<<Register_value[rt_num]<<endl;
            pc =pc+4;
        }
        else if (s == "Isltiu")
        {
            int t=0;
            while (imm[t]!='1')
            {
                imm[t]='1';
                t++;
            }
            string c;
            for (int i=0; i<32-imm.size(); i++)
            {
                c.append("1");
            }
            c.append(imm);
            imm = c;
            int a = sixth_to_int(Register_value[rs_num]);
            int b = binary_to_ten(imm);
            if( a < b )
            {
                Register_value[rt_num]="0x1";
            }
            else
            {
                Register_value[rt_num]="0x0";
            }
            cout<<Register_value[rt_num]<<endl;
            pc = pc + 4;
        }
        else if (s == "Isw")
        {
            // int a= sixth_to_int(Register_value[rs_num])  + binary_to_ten(imm);
            // if (find(datas_address_int, a)==999 && find(instructions_address_int, a)==999)
            // {
            //     if (a>= 4194304 && a< 268435456)
            //     {
            //         instructions_address_int.push_back(a);
            //         instructions.push_back(Register_value[rt_num]);
            //     }
            //     else
            //     {
            //         datas_address_int.push_back(a);
            //         datas.push_back(Register_value[rt_num]);
            //     }
                
            // }
            // else if (find(datas_address_int, a)==999)
            // {
            //     instructions[find(instructions_address_int, a)] = Register_value[rt_num];
            // }
            // else 
            // {
            //     datas[find(datas_address_int, a)]=Register_value[rt_num];
            // }

            // pc = pc + 4;

        }
        else if (s == "Isb")
        {
            // cout <<"pass"<<endl;
            // cout << Register_value[rs_num]<<endl;
            // cout << sixth_to_int(Register_value[rs_num])<< binary_to_ten(imm)<<endl;
            // unsigned int a= sixth_to_int(Register_value[rs_num])  + binary_to_ten(imm);
            // cout <<"pass-1"<<endl;
            // cout << a << endl;
            // if (find(datas_address_int, a)==999 & find(instructions_address_int, a)==999)
            // {
            //      cout <<"pass1"<<endl;
            //     if (a>= 4194304 && a< 268435456)
            //     {
            //         cout <<"pass2"<<endl;
            //         instructions_address_int.push_back(a);
            //         instructions.push_back(Register_value[rt_num]);
            //     }
            //     else
            //     {
            //         cout <<"pass3"<<endl;
            //         datas_address_int.push_back(a);
            //         datas.push_back(Register_value[rt_num]);
            //     }
                
            // }
            // else if (find(datas_address_int, a)==999)
            // {
            //     cout <<"pass2-1"<<endl;
            //     instructions[find(instructions_address_int, a)] = Register_value[rt_num];
            // }
            // else 
            // {
            //     cout <<"pass2-2"<<endl;
            //     cout << a<<Register_value[rt_num]<<endl;
            //     datas[find(datas_address_int, a)]=Register_value[rt_num];
            // }

            pc = pc + 4;
        }
        else
        {
            cout<<"something problem"<<endl;
        }
        
    }
    else if (s[0] == 'J')
    {
        string target;
        int target_num;
        target = b.substr(6, 26);
        target_num = binary_to_ten(target);
        if (s == "Jj")
        {
            pc = target_num*4;
        }
        else if (s == "Jjal")
        {
            string a = hex_to_dec(pc+4);
            Register_value[31]= a;
            pc = target_num*4;
        }
        else 
        {
            cout<<"something problem"<<endl;
        }
    }
    else
    {
        cout<<"something wrong >operate_instruction"<<endl;
    }
    
}

string hex_to_dec(unsigned int x)//10?????? 16?????? ??????? ???????.
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
    if (new_hex == "0x")
    {
        new_hex.push_back('0');
    }
	return new_hex;
}
//find(instructions_address_int, _pc)
int find(vector<int> a, unsigned int b)
{
    int i=0;
    while (a[i]!=b)
    {
        i++;
    }
    if (i==a.size())
    {
        return 999;
    }
    else
    {
    return i;
    }
}