#ifndef FORMAT_H
#define FORMAT_H

using namespace std;

unsigned printed = 0;

string find_spec(const string &fmt, unsigned &pos, bool has_arguments);

string format(const string &fmt);

template<typename To, typename From> typename enable_if<is_convertible<From, To>::value, To>::type convert(From value){
    return (To) value;
}

template<typename To, typename From> typename enable_if<!is_convertible<From, To>::value, To>::type convert(From value){
    throw std::invalid_argument("Illegal argument type");
}

template<typename First, typename... Rest> string format(const string &fmt, First value, Rest... args){
    unsigned pos = 0;
    string result = find_spec(fmt, pos, true);

    bool force_sign = false;       /// +
    bool left_justify = false;     /// -
    bool space_or_sign = false;    /// space
    bool force_num_format = false; /// #
    bool left_pad = false;         /// 0
    int width = 0;
    int precision = -1;            /// Ignored if negative
    enum {len_hh, len_h, len_default, len_l, len_ll, len_j, len_z, len_t, len_L, len_error} length = len_default;
    string temp = "";

    while(pos < fmt.length() && (fmt[pos] == '-' || fmt[pos] == '+' || fmt[pos] == ' ' || fmt[pos] == '#' || fmt[pos] == '0')){
		switch(fmt[pos++]){
            case '-':
                left_justify = true;
                left_pad = false;
                break;
            case '+':
                force_sign = true;
                space_or_sign = false;
                break;
            case ' ':
                space_or_sign = !force_sign;
                break;
            case '#':
                force_num_format = true;
                break;
            case '0':
                left_pad = !left_justify;
                break;
        }
	}

	if(pos < fmt.length() && fmt[pos] == '*'){
        width = convert<int>(value);
        printf("Width = %d\n", width);
        temp = "%";
        if(force_sign){temp.push_back('+');}
        if(left_justify){temp.push_back('-');}
        if(space_or_sign){temp.push_back(' ');}
        if(force_num_format){temp.push_back('#');}
        if(left_pad){temp.push_back('0');}
        temp.append(to_string(width));
        pos++;
        printed += result.length();
        return result + format(temp + fmt.substr(pos, string::npos), args...);
	} else {
        while(pos < fmt.length() && isdigit(fmt[pos])){
			temp.push_back(fmt[pos++]);
		}
        if(!temp.empty()){
			width = stoi(temp);
		    temp = "";
		}
	}

    if(pos < fmt.length() - 1 && fmt[pos] == '.'){
		pos++;
        if(fmt[pos] == '*'){
			precision = convert<int>(value);
            printf("Precision = %d\n", precision);
            temp = "%";
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(to_string(width));}
            temp.push_back('.');
            temp.append(to_string(precision));
            pos++;
            printed += result.length();
            return result + format(temp + fmt.substr(pos, string::npos), args...);
	    } else {
            while(pos < fmt.length() && isdigit(fmt[pos])){
	    		temp.push_back(fmt[pos++]);
		    }
            if(!temp.empty()){
			    precision = stoi(temp);
		        temp = "";
		    }
	    }
    }

	while(pos < fmt.length() && (fmt[pos] == 'h' || fmt[pos] == 'l' || fmt[pos] == 'j' || fmt[pos] == 'z' || fmt[pos] == 't' || fmt[pos] == 'L')){
		switch(fmt[pos++]){
            case 'h':
                length = (length == len_h) ? len_hh : ((length == len_default) ? len_h : len_error);
                break;
            case 'l':
                length = (length == len_l) ? len_ll : ((length == len_default) ? len_l : len_error);
                break;
            case 'j':
                length = (length == len_default) ? len_j : len_error;
                break;
            case 'z':
                length = (length == len_default) ? len_z : len_error;
                break;
            case 't':
                length = (length == len_default) ? len_t : len_error;
                break;
            case 'L':
                length = (length == len_default) ? len_L : len_error;
                break;
        }
	}

	if(length == len_error){
        throw invalid_argument("Unknown length");
	}

	if(pos == fmt.length()){
        throw invalid_argument("Сonversion lacks type at end of format");
    }

    int v;
    switch(fmt[pos++]){
        case 'd':
        case 'i':
            v = convert<int>(value);
            if(force_sign || space_or_sign){
                result.push_back(v < 0 ? '-' : (space_or_sign ? ' ' : '+'));
            }
            v = abs(v);
            if(left_justify){
                //b
            }
            result.append(to_string(v));
            break;
        case 'u':
            result.append(to_string(convert<unsigned>(value)));
            break;
        case 'o':
            result.append("(unsigned octal)");
            break;
        case 'x':
            result.append("(unsigned hex)");
            break;
        case 'X':
            result.append("(UNSIGNED HEX)");
            break;
        case 'f':
            result.append("(decimal float)");
            break;
        case 'F':
            result.append("(DECIMAL FLOAT)");
            break;
        case 'e':
            result.append("(scientific)");
            break;
        case 'E':
            result.append("(SCIENTIFIC)");
            break;
        case 'g':
            result.append("(%e or %f)");
            break;
        case 'G':
            result.append("(%E or %F)");
            break;
        case 'a':
            result.append("(hex float)");
            break;
        case 'A':
            result.append("(HEX FLOAT)");
            break;
        case 'c':
            result.append("(char)");
            break;
        case 's':
            result.append("(string)");
            break;
        case 'p':
            result.append("(pointer)");
            break;
        case 'n':
            break;
        default:
            throw invalid_argument("Unknown format");
            break;
    }
    printed += result.length();
    return result + format(fmt.substr(pos, string::npos), args...);
}

#endif
