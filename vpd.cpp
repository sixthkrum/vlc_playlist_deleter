#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<sstream>
#include<unistd.h>

char url_code_converter(int code)
{
switch(code)
{
case 0x20:
return ' ';
break;

case 0x21:
return '!';
break;

case 0x22:
return '"';
break;

case 0x23:
return '#';
break;

case 0x26:
return '&';
break;

case 0x27:
return '\'';
break;

case 0x28:
return '(';
break;

case 0x29:
return ')';
break;

case 0x2B:
return '+';
break;

case 0x3D:
return '=';
break;

case 0x5B:
return '[';
break;

case 0x5D:
return ']';
break;

default:
break;
}
return ' ';
}




int main(int argc, char* argv[])
{
std::fstream f;
std::cout<<argv[1]<<'\n';
f.open(argv[1], std::ios::in);
if((f.rdstate() & std::fstream::failbit) != 0)
{
std::cout<<"no such file exists\n";
exit(0);
}
char stream_byte;
char dummy,d1,d2,d[2];
std::string stream;
char* file_to_remove;
std::istringstream file_parser,dis;
int url_code;
while(f.read((char*)&stream_byte,sizeof(char)))
{
if(stream_byte=='<')
{

f.read((char*)&stream_byte,sizeof(char));
if(stream_byte=='l')
{
f.seekg(15,std::ios::cur);//15 skips <l->ocation>file://
file_to_remove = new char[256];
getline(f,stream,'<');
file_parser.str(stream);
int i=0;
file_to_remove[i]='r';
i++;
file_to_remove[i]='m';
i++;
file_to_remove[i]=' ';
i++;
file_to_remove[i]='"';
i++;
while(file_parser>>dummy)
{
if(dummy!='%')
{
file_to_remove[i]=dummy;
i++;
}
else if(dummy=='%')
{
file_parser>>d1;
file_parser>>d2;
d[0]=d1;
d[1]=d2;
dis.str(d);
dis>>std::hex>>url_code;
dummy=url_code_converter(url_code);
file_to_remove[i]=dummy;
i++;
}
}
file_to_remove[i]='"';
system(file_to_remove);
file_parser.clear();
stream.clear();
dis.clear();
}
}
}
}
