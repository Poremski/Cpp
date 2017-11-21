#include "TagRemover.h"
#include <string>
#include <istream>
#include <fstream>
#include <iostream>

using std::string;

void tag_remove(std::ifstream* in, string* out)
{
	if(out->back() == ' ')
		out->pop_back();
	char c;
	while((c = in->get()) != EOF)
	{
		if(c == '\n'){
			*out += '\n';
		} else if(c == '>')
		{
			// Remove following space
			//c = in->get();
			//if(c != ' ') {*out += c;}
			if(out->back() == '\n'){
				if((c=in->get()) != ' ') *out += c;
			}
			return;
		}
	}
}

void sp_remove(std::ifstream* in, string* out)
{
	string sp_char;
	char c;
	while((c = in->get()) != ';')
	{
		sp_char += c;
	}
	if(sp_char == "lt")
	{
		*out += '<';
	} else if(sp_char == "gt")
	{
		*out += '>';
	} else if(sp_char == "nbsp")
	{
		*out += ' ';
	} else if(sp_char == "amp")
	{
		*out += '&';
	} else
	{
		*out += "&" + sp_char + ";";
	}
}

string format(std::ifstream* in)
{
	string out;
	char c;
	while((c = in->get()) != EOF)
	{
		if(c == '<')
		{
			tag_remove(in, &out);
		} else if (c == '&'){
			sp_remove(in, &out);
		}
		else
		{
			out += c;
		}
	}
	return out;
}

TagRemover::TagRemover(string fname) 
{
	std::ifstream in{fname};
	output = format(&in);
}

void TagRemover::print(string fname) 
{
	std::ofstream of{fname};
	of << output;
}