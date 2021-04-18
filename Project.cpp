#include<bits/stdc++.h>

int pc=25;

int bti(string s)
{
    int l = s.length(),i,v=0;
    for(i=l-1;i>=0;i--)
    v += s[i]*pow(2,l-1-i);
    return v;
}

int inst_w(string inst,int r, int v)
{
    stringstream ss;
    string s,sa;
    ss.str("");
    ss<<"R"<<r;
    ss>>sa;
    fstream f("R_M.txt");
    if(!(f.is_open()))
    {
        cout << "File could not be opened\n";
        return 1;
    }
    if(inst=="ADD"||inst=="ADDI"||inst=="ADDIU"||inst=="SUB"||inst=="SUBU"||inst=="XOR"||inst=="MUL"||inst=="MULU"||inst=="DIV"||inst=="DIVU")
    {
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                f.seekg(-f.length-1,ios::cur);
                break;
            }
            ss.str("");
            ss<<"R"; ss<<r;  ss<<",";  ss<<v;  ss<<"\n"
            ss>>s;
            f<<s;
        }
        f.close();
        return 0;
    }
    else if (inst == "BEQ"|| inst == "BNE")
    pc+=v;
}

int inst_m(string inst, int r, int m)
{
    stringstream ss;
    string s,sa;
    int v;
    fstream f("R_M.txt");
    if(!(f.is_open()))
    {
        cout << "File could not be opened\n";
        return 1;
    }
    if(inst=="LW")
    {
        ss<<"M"<<m;
        ss>>sa;
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                ss<<s.substr(sa.length+1);
                ss>>v;
                break;
            }
        }
        f.seekg(0,ios::beg);
        ss.str("");
        ss<<"R"<<r;
        ss>>sa;
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                f.seekg(-f.length-1,ios::cur);
                ss.str("");
                ss<<"R"<<r<<","<<v;
                ss>>s;
                f<<s;
                break;
            }
        }
        return 0;
    }
    if(inst=="SW")
    {
        ss<<"R"<<r;
        ss>>sa;
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                ss<<s.substr(sa.length+1);
                ss>>v;
                break;
            }
        }
        f.seekg(0,ios::beg);
        ss.str("");
        ss<<"M"<<m;
        ss>>sa;
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                f.seekg(-f.length-1,ios::cur);
                ss.str("");
                ss<<"M"<<m<<","<<v;
                ss>>s;
                f<<s;
                break;
            }
        }
        return 0;
    }
}

int inst_e(string inst, int a, int b, int c)
{
    string s;
    stringstream ss;
    string sa,sb,sc;
    int va,vb,vc
    ss<<"R";    ss<<a;    ss>>sa;
    ss<<"R";    ss<<b;    ss>>sb;
    ss<<"R";    ss<<c;    ss>>sc;
    fstream f("R_M.txt");
    if(!(f.is_open()))
    {
        cout<<"File could not be opened\n"; 
        return 1;
    }
    if(inst=="ADD")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        va = vb + vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="ADDI")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
        }
        va = vb + c;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="ADDIU")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
        }
        if(c<0)
        c*=-1;
        va = vb + c;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="SUB")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        va = vb - vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="SUBU")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        if(vc<0)
        vc*=-1;
        va = vb - vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="XOR")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        va = vb^vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="MUL")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        va = vb*vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="MULU")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        if(vc<0)
        vc*=-1;
        va = vb*vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="DIVU")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        va = vb/vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="DIVU")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        if(vc<0)
        vc*=-1;
        va = vb/vc;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="BEQ")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        if(vb==vc)
        a = c*4;
        else
        a=0;
        va=a;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="BNE")
    {
        while(getline(f,s))
        {
            if(sb==s.substr(0,sb.length))
            {
                ss << s.substr(sb.length + 1);
                ss >> vb;
            }
            else if (sc == s.substr(0,sc.length))
            {
                ss << s.substr(sc.length + 1);
                ss >> vc;
            }
        }
        if(vb!=vc)
        a = c*4;
        else
        a=0;
        va=a;
        f.close();
        if(inst_w(inst,a,va)!=0)
        cout<<"Write back unsuccessful\n";
        return 0;
    }
    else if(inst=="LW")
    {
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                ss << s.substr(sa.length + 1);
                ss >> va;
            }
        }
        vb = c + va;
        f.close();
        if(inst_m(inst,b,vb)!=0)
        cout<<"Memory execution unsuccessful\n";
        return 0;
    }
    else if(inst=="SW")
    {
        while(getline(f,s))
        {
            if(sa==s.substr(0,sa.length))
            {
                ss << s.substr(sa.length + 1);
                ss >> va;
            }
        }
        vb = c + va;
        f.close();
        if(inst_m(inst,b,vb)!=0)
        cout<<"Memory execution unsuccessful\n";
        return 0;
    }
}

void inst_d(string inst)
{
    if(inst.substr(0,6)=="000000" && inst.substr(21,5)=="00000" && inst.substr(26,6)=="100000")
    {
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,5));
        if(inst_e("ADD",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
    else if(inst.substr(0,6) == "001000")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("ADDI",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }

	else if(inst.substr(0,6) == "001001")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("ADDIU",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000000" && inst.substr(21,5) == "00000" && inst.substr(26,6) == "100010")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,5));
        if(inst_e("SUB",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000000" && inst.substr(21,5) == "00000" && inst.substr(26,6) == "100011")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,5));
        if(inst_e("SUBU",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000000" && inst.substr(21,5) == "00000" && inst.substr(26,6) == "100110")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,5));
        if(inst_e("XOR",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000000" && inst.substr(16,10) == "0000000000" && inst.substr(26,6) == "011000")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(6,5));
        if(inst_e("MUL",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }

	else if(inst.substr(0,6) == "000000" && inst.substr(16,10) == "0000000000" && inst.substr(26,6) == "011001")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(6,5));
        if(inst_e("MULU",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000000" && inst.substr(16,10) == "0000000000" && inst.substr(26,6) == "011010")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(6,5));
        if(inst_e("DIV",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }

	else if(inst.substr(0,6) == "000000" && inst.substr(16,10) == "0000000000" && inst.substr(26,6) == "011001")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(6,5));
        if(inst_e("DIVLU",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000101")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("BNE",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "000100")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("BEQ",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "100011")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("LW",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst.substr(0,6) == "101011")
	{
        int a=bti(inst.substr(6,5)),b=bti(inst.substr(11,5)),c=bti(inst.substr(16,16));
        if(inst_e("SW",a,b,c)==0);
        return;
        else
        {
            cout<<"Instruction not executed\n";
            return;
        }
    }
	
	else if(inst == "00000000000000000000000000000000")
	inst_e(inst, "NOP");
}

int inst_f(string s)
{
    cin>>s;
    if(s.length()!=32)
    return 1;
    else
    {
        for(int i:s)
        if(i!=48&&i!=49)
        return 1;
    }
    return 0;
}

int main()
{
    string inst;
    char c='y';
    do{
        cout<<"Enter the instruction: ";
        if(inst_f(inst)==0)
        inst_d(inst)
        else
        cout<<"Instruction not entered properly\n";
        cout<<"Do you want to continue?(y/n): ";
        cin>>c;
    }while(c=='y');
}