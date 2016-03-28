#include <string>
#include <stdexcept>

using namespace std;

string format(const string &fmt){
	return fmt;
}

template<typename First, typename... Rest> string format(const string &fmt, First value, Rest... args){
    string temp = "";
    unsigned pos = 0;
    bool spec_found = false, spec_parsed = false;
    while(!spec_found){
        for(; pos < fmt.length() && fmt[pos] != '%'; temp.push_back(fmt[pos++]));
        if(pos == fmt.length()){
	    	printf("Too many arguments for format [-Wformat-extra-args]\n");
            return temp;
	    }
    	if(pos == fmt.length() - 1){
	    	printf("Spurious trailing '%%' in format [-Wformat=]\n");
            return temp;
	    }
	    if(fmt[pos + 1] == '%'){
            temp.push_back('%');
            pos += 2;
		} else {
			pos++;
            spec_found = true;
		}
	}
    /// fmt[pos] == '%' и после что-то есть
    
    /* char flags = 0;
    int width = 0;
    int precision = -1;
	char length[5] = "00000";
	char sign = '\0';
	char type = ' '; */
    while(!spec_parsed){
        if(pos == fmt.length()){
            printf("Сonversion lacks type at end of format [-Wformat=]\n");
            return temp;
    	}
    
        switch(fmt[pos]){
            case 'd':
            case 'i':
                temp.append("(int)");
                spec_parsed = true;
			    break;
			case 'u':
			    temp.append("(unsigned int)");
                spec_parsed = true;
			    break;
            case 'o':
                temp.append("(unsigned octal)");
                spec_parsed = true;
			    break;
            case 'x':
                temp.append("(unsigned hex)");
                spec_parsed = true;
			    break;
            case 'X':
                temp.append("(UNSIGNED HEX)");
                spec_parsed = true;
			    break;
            case 'f':
                temp.append("(decimal float)");
                spec_parsed = true;
			    break;
            case 'F':
                temp.append("(DECIMAL FLOAT)");
                spec_parsed = true;
			    break;
            case 'e':
                temp.append("(scientific)");
                spec_parsed = true;
			    break;
            case 'E':
                temp.append("(SCIENTIFIC)");
                spec_parsed = true;
			    break;
            case 'g':
                temp.append("(%e or %f)");
                spec_parsed = true;
			    break;
            case 'G':
                temp.append("(%E or %F)");
                spec_parsed = true;
			    break;
            case 'a':
                temp.append("(hex float)");
                spec_parsed = true;
			    break;
            case 'A':
                temp.append("(HEX FLOAT)");
                spec_parsed = true;
			    break;
            case 'c':
                temp.append("(char)");
                spec_parsed = true;
			    break;
            case 's':
                temp.append("(string)");
                spec_parsed = true;
			    break;
            case 'p':
                temp.append("(pointer)");
                spec_parsed = true;
			    break;
            case 'n':
                spec_parsed = true;
			    break;
            /// Length
            case 'h':
            case 'l':
            case 'j':
            case 'z':
            case 't':
            case 'L':
            /// Precision
            case '.':
            /// Width
            case '*':
            /// Flags
            case '-':
                // Left-justify within the given field width; Right justification is the default (see width sub-specifier).
                break;
            case '+':

            case ' ':

            case '#':
                break;
            case '0':
                break;
     	}
     	pos++;
	}
    
    return temp + format(fmt.substr(pos, fmt.length()), args...);
}


int main(){
	char zz[] = "foo%% test %% %%%% %d %f";
    printf("%s\n", zz);

	
    printf(format(zz, 10, 0.5).c_str());
	return 0;
}
 
