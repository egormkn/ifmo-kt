#ifndef FORMAT_H
#define FORMAT_H

using std::string; using std::to_string;

int printed = 0;
string unknown_spec = "";

string format(const string &fmt);

template<typename First, typename... Rest> string format(const string &fmt, First value, Rest... args){
    string result = "";
    unsigned pos = 0;
    bool spec_found = false, spec_parsed = false;
    while(!spec_found){
        for(; pos < fmt.length() && fmt[pos] != '%'; result.push_back(fmt[pos++]));
        if(pos == fmt.length()){
            printf("Too many arguments for format [-Wformat-extra-args]\n");
            return result;
        }
        if(pos == fmt.length() - 1){
            printf("Spurious trailing '%%' in format [-Wformat=]\n");
            return result;
        }
        if(fmt[pos + 1] == '%'){
            result.push_back('%');
            pos += 2;
        } else {
            pos++;
            spec_found = true;
        }
    }

    bool force_sign = false;
    bool left_justify = false;
    bool space_or_sign = false;
    bool force_num_format = false;
    bool left_pad = false;
    int width = 0;
    int precision = -1;
    int numcount = 0;
    string length = "";
    string temp = "";

    while(!spec_parsed){
        if(pos == fmt.length()){
            printf("Сonversion lacks type at end of format [-Wformat=]\n");
            return result;
        }

        unknown_spec.push_back(fmt[pos]);
        switch(fmt[pos]){
            case 'h': /// Length
            case 'l':
            case 'j':
            case 'z':
            case 't':
            case 'L':
                length.push_back(fmt[pos]);
                break;
            case '.': /// Precision
                pos++;
                unknown_spec.push_back(fmt[pos]);
                if(isdigit(fmt[pos])){
                    temp.push_back(fmt[pos]);
                    while(isdigit(fmt[pos+1])) {
                        temp.push_back(fmt[++pos]);
                        unknown_spec.push_back(fmt[pos]);
                    }
                    precision = stoi(temp);  // TODO Проверить, вмещается ли в int
                    temp = "";
                } else if (fmt[pos] == '*'){
                    temp.push_back('%');
                    if(force_sign){temp.push_back('+');}
                    if(left_justify){temp.push_back('-');}
                    if(space_or_sign){temp.push_back(' ');}
                    if(force_num_format){temp.push_back('#');}
                    if(left_pad){temp.push_back('0');}
                    if(width != 0){temp.append(to_string(width));}
                    temp.push_back('.');
                    temp.append(to_string((int) value));
                    spec_parsed = true;
                }
                break;
            case '*': /// Width
                temp.push_back('%');
                if(force_sign){temp.push_back('+');}
                if(left_justify){temp.push_back('-');}
                if(space_or_sign){temp.push_back(' ');}
                if(force_num_format){temp.push_back('#');}
                if(left_pad){temp.push_back('0');}
                temp.append(to_string((int) value)); // TODO Проверить на число
                spec_parsed = true;
                break;
            case '-': /// Flags
                left_justify = true;
                if(left_pad){
                    printf("'0' flag ignored with '-' flag in ms_printf format [-Wformat=]");
                    left_pad = false;
                }
                break;
            case '+':
                force_sign = true;
                if(space_or_sign){
                    printf("' ' flag ignored with '+' flag in ms_printf format [-Wformat=]");
                    space_or_sign = false;
                }
                break;
            case ' ':
                if(force_sign){
                    printf("' ' flag ignored with '+' flag in ms_printf format [-Wformat=]");
                } else {
                    space_or_sign = true;
                }
                break;
            case '#':
                force_num_format = true;
                break;
            case '0':
                if(left_justify){
                    printf("'0' flag ignored with '-' flag in ms_printf format [-Wformat=]");
                } else {
                    left_pad = true;
                }
                break;
            default:
                if(isdigit(fmt[pos])){
                    temp.push_back(fmt[pos]);
                    while(isdigit(fmt[pos+1])) {
                        temp.push_back(fmt[++pos]);
                    }
                    width = stoi(temp); // TODO Проверить, вмещается ли в int
                    temp = "";
                } else {


/**
    bool force_sign;
    bool left_justify;
    bool space_or_sign;
    bool force_num_format;
    bool left_pad;
    int width;
    int precision = -1;
    string length = "";
    int numcount;
**/
                    int v;
                    switch(fmt[pos]){
                        case 'd':
                        case 'i':
                            v = (int) value;
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
                            result.append(to_string((unsigned) value));
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
                            value = (First) numcount;
                            break;
                        default:
                            printf("Unknown format\n");
                            result = unknown_spec;
                            break;
                    }
                    if(precision == -100 && numcount < 0){temp = " ";} //FIXME
                    temp = "";
                    spec_parsed = true;
                }
                break;
        }
        pos++;
    }

    printed += result.length();
    if(!spec_parsed){
        printf("Wrong format\n");
	}
    
    return result + format(temp + fmt.substr(pos, fmt.length()), args...);
}

#endif
