#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
//parse file identified by string filename into individual words
//held in tokenlist
namespace nwsjs
{
    namespace options
    {
        int comments = 0x01;
        int spaces = 0x02;
        int tabs = 0x03;
    }
}
bool tokenizeJS(std::string filename,std::vector<std::string>&tokenlist,int&parseOptions)
{
    std::ifstream file(filename.c_str(),std::ios::in);
    char byte;
    std::string str;
    bool add = true;
    if(file.fail())
		return false;
    while(file.get(byte))
    {
        add = true;
        switch(byte)
        {
            case '/':
                if(parseOptions&nwsjs::options::comments)
                {
                    file.get(byte);
                    //single line
                    if(byte == '/')
                    {
                        //consume the line
                        while(byte != '\n')
                        {
                            file.get(byte);
                        }
                        break;
                    }
                    //multi line
                    else if(byte == '*')
                    {
                        for(;;)
                        {
                            file.get(byte);
                            if(byte == '*')
                            {
                                file.get(byte);
                                if(byte == '/')
                                {
                                    file.get(byte);
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    else
                    {
                        str += "/";
                        str += byte;
                        file.get(byte);
                    }
                }
            break;
            case ' ':
                if((parseOptions&nwsjs::options::spaces) == 0)
                    str += " ";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case '(':
                str += "(";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case ')':
                str += ")";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case '{':
                str += "{";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case '}':
                str += "}";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case ',':
                str += ",";
                str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case '\n':
                str += "\n";
                //str.erase(std::remove(str.begin(),str.end(),'\n'),str.end());
                //str.erase(std::remove(str.begin(),str.end(),'\t'),str.end());
                if(str != "")
                    tokenlist.push_back(str);
                str = "";
                add = false;
            break;
            case '\"':
                str += byte;
                for(;;)
                {
                    file.get(byte);
                    str += byte;
                    if(byte == '\"')
                        break;
                }
            break;
            case '\'':
                str += byte;
                for(;;)
                {
                    file.get(byte);
                    str += byte;
                    if(byte == '\'')
                        break;
                }
            break;
        }
        if(add && byte != '\'' && byte != '\"')
            str += byte;
    }
	file.close();
    return true;
}
