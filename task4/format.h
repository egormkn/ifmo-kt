#ifndef FORMAT_H
#define FORMAT_H

static unsigned chars_printed = 0;

std::string find_spec(const std::string &fmt, unsigned &pos, bool has_arguments);

std::string format(const std::string &fmt);

template<typename To, typename From> typename std::enable_if<std::is_convertible<From, To>::value, To>::type convert(From value){
    return (To) value;
}

template<typename To, typename From> typename std::enable_if<!std::is_convertible<From, To>::value, To>::type convert(From value){
    throw std::invalid_argument("Invalid argument type");
}

template<typename Need, typename Got> typename std::enable_if<std::is_same<Need, Got>::value, Need>::type safetype(Got value){
    return (Need) value;
}

template<typename Need, typename Got> typename std::enable_if<!std::is_same<Need, Got>::value, Need>::type safetype(Got value){
    throw std::invalid_argument("Invalid argument type");
}

template<typename First, typename... Rest> std::string format(const std::string &fmt, First value, Rest... args){
    unsigned pos = 0;
    std::string result = find_spec(fmt, pos, true);
    bool force_sign = false;
    bool left_justify = false;
    bool space_or_sign = false;
    bool force_num_format = false;
    bool left_pad = false;
    bool uppercase = false;
    if(uppercase){uppercase=true;}
    int width = 0;
    int precision = -1; /// Ignored if negative
    enum {len_hh, len_h, len_default, len_l, len_ll, len_j, len_z, len_t, len_L, len_error} length = len_default;
    std::string temp = "";

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
        temp = "%";
        if(force_sign){temp.push_back('+');}
        if(left_justify){temp.push_back('-');}
        if(space_or_sign){temp.push_back(' ');}
        if(force_num_format){temp.push_back('#');}
        if(left_pad){temp.push_back('0');}
        temp.append(std::to_string(width));
        pos++;
        chars_printed += result.length();
        return result + format(temp + fmt.substr(pos, std::string::npos), args...);
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
            temp = "%";
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            temp.push_back('.');
            temp.append(std::to_string(precision));
            pos++;
            chars_printed += result.length();
            return result + format(temp + fmt.substr(pos, std::string::npos), args...);
	    } else {
            while(pos < fmt.length() && isdigit(fmt[pos])){
	    		temp.push_back(fmt[pos++]);
		    }
            if(!temp.empty()){
			    precision = stoi(temp);
		        temp = "";
		    } else {
                precision = 0;
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
        throw std::invalid_argument("Unknown length");
	}

	if(pos == fmt.length()){
        throw std::invalid_argument("Сonversion lacks type at end of format");
    }


    /*
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     *
     */

    intmax_t d;
    uintmax_t u;
    void* p;
    long double f;
    wint_t c;
    
    std::string s;
    

    char buffer[1024];

    switch(fmt[pos++]){
        case 'd':
        case 'i':
            switch (length){
                case len_hh:
                    d = convert<signed char>(value);
                    break;
                case len_h:
                    d = convert<short int>(value);
                    break;
                case len_l:
                    d = convert<long int>(value);
                    break;
                case len_ll:
                    d = convert<long long int>(value);
                    break;
                case len_j:
                    d = convert<intmax_t>(value);
                    break;
                case len_z:
                    d = convert<size_t>(value);
                    break;
                case len_t:
                    d = convert<ptrdiff_t>(value);
                    break;
                case len_default:
                    d = convert<int>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME d
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("jd");
			snprintf(buffer, 1024, temp.c_str(), d);
			result.append(buffer);
            break;
        case 'u':
            switch (length){
                case len_hh:
                    u = convert<unsigned char>(value);
                    break;
                case len_h:
                    u = convert<unsigned short int>(value);
                    break;
                case len_l:
                    u = convert<unsigned long int>(value);
                    break;
                case len_ll:
                    u = convert<unsigned long long int>(value);
                    break;
                case len_j:
                    u = convert<uintmax_t>(value);
                    break;
                case len_z:
                    u = convert<size_t>(value);
                    break;
                case len_t:
                    u = convert<ptrdiff_t>(value);
                    break;
                case len_default:
                    u = convert<unsigned int>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("ju");
			snprintf(buffer, 1024, temp.c_str(), u);
			result.append(buffer);
			break;
        case 'o': // TODO o
            switch (length){
                case len_hh:
                    u = convert<unsigned char>(value);
                    break;
                case len_h:
                    u = convert<unsigned short int>(value);
                    break;
                case len_l:
                    u = convert<unsigned long int>(value);
                    break;
                case len_ll:
                    u = convert<unsigned long long int>(value);
                    break;
                case len_j:
                    u = convert<uintmax_t>(value);
                    break;
                case len_z:
                    u = convert<size_t>(value);
                    break;
                case len_t:
                    u = convert<ptrdiff_t>(value);
                    break;
                case len_default:
                    u = convert<unsigned int>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("jo");
			snprintf(buffer, 1024, temp.c_str(), u);
			result.append(buffer);
			break;
        case 'X':
            uppercase = true;
        case 'x': // TODO x
            switch (length){
                case len_hh:
                    u = convert<unsigned char>(value);
                    break;
                case len_h:
                    u = convert<unsigned short int>(value);
                    break;
                case len_l:
                    u = convert<unsigned long int>(value);
                    break;
                case len_ll:
                    u = convert<unsigned long long int>(value);
                    break;
                case len_j:
                    u = convert<uintmax_t>(value);
                    break;
                case len_z:
                    u = convert<size_t>(value);
                    break;
                case len_t:
                    u = convert<ptrdiff_t>(value);
                    break;
                case len_default:
                    u = convert<unsigned int>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			if(uppercase){
				temp.append("jX");
			} else {
				temp.append("jx");
			}
			snprintf(buffer, 1024, temp.c_str(), u);
			result.append(buffer);
			break;
        case 'F':
            uppercase = true;
        case 'f': // TODO f
            switch (length){
                case len_l:
                case len_default:
                    f = convert<double>(value);
                    break;
                case len_L:
                    f = convert<long double>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			if(uppercase){
				temp.append("LF");
			} else {
				temp.append("Lf");
			}
			snprintf(buffer, 1024, temp.c_str(), f);
			result.append(buffer);
			break;
        case 'E':
            uppercase = true;
        case 'e': // TODO e
            switch (length){
                case len_l:
                case len_default:
                    f = convert<double>(value);
                    break;
                case len_L:
                    f = convert<long double>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			if(uppercase){
				temp.append("LE");
			} else {
				temp.append("Le");
			}
			snprintf(buffer, 1024, temp.c_str(), f);
			result.append(buffer);
			break;
        case 'G':
            uppercase = true;
        case 'g': // TODO g
            switch (length){
                case len_l:
                case len_default:
                    f = convert<double>(value);
                    break;
                case len_L:
                    f = convert<long double>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			if(uppercase){
				temp.append("LG");
			} else {
				temp.append("Lg");
			}
			snprintf(buffer, 1024, temp.c_str(), f);
			result.append(buffer);
			break;
        case 'A':
            uppercase = true;
        case 'a': // TODO a
            switch (length){
                case len_l:
                case len_default:
                    f = convert<double>(value);
                    break;
                case len_L:
                    f = convert<long double>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			if(uppercase){
				temp.append("LA");
			} else {
				temp.append("La");
			}
			snprintf(buffer, 1024, temp.c_str(), f);
			result.append(buffer);
			break;
        case 'c': // TODO c
            switch (length){
                case len_l:
                    c = convert<wint_t>(value);
                    break;
                case len_default:
                    c = convert<int>(value);
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("c");
			snprintf(buffer, 1024, temp.c_str(), c);
			result.append(buffer);
			break;
        case 's': // TODO s
            /*switch (length){
                case len_l:
                    //s = convert<wchar_t*>(value);
                    s = convert<char*>(value);
                    break;
                case len_default:
                    s = (char*)value;
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
			printf(s.c_str());
			result.append(s);
            /*temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("s");
			snprintf(buffer, 1024, temp.c_str(), s.c_str());
			result.append(buffer);
			break;*/
            s = convert<std::string>(value); 
            result.append(s); 
            break;
        case 'p': // TODO p
            p = convert<void*>(value);
            if(length != len_default){
                throw std::invalid_argument("Unsupported length specifier");
			}
            temp = "%"; /// FIXME
            if(force_sign){temp.push_back('+');}
            if(left_justify){temp.push_back('-');}
            if(space_or_sign){temp.push_back(' ');}
            if(force_num_format){temp.push_back('#');}
            if(left_pad){temp.push_back('0');}
            if(width != 0){temp.append(std::to_string(width));}
            if(precision >= 0){
				temp.push_back('.');
                temp.append(std::to_string(precision));
			}
			temp.append("p");
			snprintf(buffer, 1024, temp.c_str(), p);
			result.append(buffer);
			break;
        case 'n':
            switch (length){
                case len_hh:
                    *(safetype<signed char*>(value)) = chars_printed + result.length();
                    break;
                case len_h:
                    *(safetype<short int*>(value)) = chars_printed + result.length();
                    break;
                case len_l:
                    *(safetype<long int*>(value)) = chars_printed + result.length();
                    break;
                case len_ll:
                    *(safetype<long long int*>(value)) = chars_printed + result.length();
                    break;
                case len_j:
                    *(safetype<intmax_t*>(value)) = chars_printed + result.length();
                    break;
                case len_z:
                    *(safetype<size_t*>(value)) = chars_printed + result.length();
                    break;
                case len_t:
                    *(safetype<ptrdiff_t*>(value)) = chars_printed + result.length();
                    break;
                case len_default:
                    *(safetype<int*>(value)) = chars_printed + result.length();
                    break;
                default:
                    throw std::invalid_argument("Unsupported length specifier");
			}
            break;
        default:
            throw std::invalid_argument("Unknown format");
            break;
    }
    chars_printed += result.length();
    return result + format(fmt.substr(pos, std::string::npos), args...);
}

#endif
