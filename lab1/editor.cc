#include "editor.h"

#include <string>

using std::string;

using size_type = Editor::size_type;

size_type Editor::get_size() const
{
    return text.size();
}

size_type Editor::find_left_par(size_type pos) const {
	char c = text[pos];
	char match = '\0';
	int skip = 0;
	if(c == ')') match = '(';
	else if(c == ']') match = '[';
	else if(c == '}') match = '{';
    for(int i = pos-1; i != -1; --i){
    	if(text[i] == c) skip++;
    	else if(text[i] == match && skip > 0) skip--;
    	else if(text[i] == match && skip == 0) return i;
    }
    return string::npos;
}
