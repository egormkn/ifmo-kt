#include <string>
#include <stdexcept>
#include <cctype>
#include <climits>
#include "format.h"

std::string find_spec(const std::string &fmt, unsigned &pos, bool has_arguments){
    std::string result = "";
    while(pos < fmt.length()){
        for(; pos < fmt.length() && fmt[pos] != '%'; result.push_back(fmt[pos++]));
        if(pos == fmt.length()){
            chars_printed = 0;
            if(has_arguments){
                throw std::invalid_argument("Too many arguments for format");
			} else {
                return result;
			}
        }
        if(pos == fmt.length() - 1){
            chars_printed = 0;
            throw std::invalid_argument("Spurious trailing '%%' in format");
        }
        if(fmt[pos + 1] == '%'){
            result.push_back('%');
            pos += 2;
        } else {
            pos++;
            if(!has_arguments){
                throw std::out_of_range("Need more arguments or unknown format");
	        }
	        break;
        }
    }
    return result;
}

std::string format(const std::string &fmt){
    unsigned pos = 0;
    std::string result = find_spec(fmt, pos, false);
    chars_printed = 0;
    return result;
}




#ifndef TEST
int main(){
	using namespace std;
	try {
        printf("%s\n", format("test", 10).c_str());
    } catch (exception &e){
        printf("%s\n", e.what());
    }

    long g = INT_MAX;
    printf("%s\n", format("Format:   %-5.20lx %.10d", g, 10).c_str());
    printf("Original: %-5.20lx %.10d\n", g, 10);


    int val = 0;
    printf("%s\n", format("blah %n blah", &val).c_str());
    printf("%s\n", format("val = %d\n", val).c_str());

    /*printf("%s\n", format("%-*.*wd test", 10).c_str());



    printf("Need: %");
    printf("\n");
    printf("Got:  %s\n", format("%").c_str());
    
    printf("NEED: %%");
    printf("\n");
    printf("GOT:  %s\n", format("%%").c_str());
    
    printf("Need: %%%");
    printf("\n");
    printf("Got:  %s\n", format("%%%").c_str());
    
    printf("NEED: %%%%");
    printf("\n");
    printf("GOT:  %s\n", format("%%%%").c_str());
    
    printf("NEED: test");
    printf("\n");
    printf("GOT:  %s\n", format("test").c_str());

    printf("Need: %test");
    printf("\n");
    printf("Got:  %s\n", format("%test").c_str());
    
    printf("Need: %d");
    printf("\n");
    printf("Got:  %s\n", format("%d").c_str());
*/
    char zz[] = "foo%% test %% %%%% %i";
    printf("Need: ");
    printf(zz, 100);
    printf("\n");
    printf("Got:  %s\n", format(zz, 100).c_str());


    printf("%s\n", format("Characters: %c %c \n", 'a', 65).c_str());
    printf("%s\n", format("Decimals: %d %ld\n", 1977, 650000L).c_str());
    printf("%s\n", format("Preceding with blanks: %10d \n", 1977).c_str());
    printf("%s\n", format("Preceding with zeros: %010d \n", 1977).c_str());
    printf("%s\n", format("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100).c_str());
    printf("%s\n", format("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416).c_str());
    printf("%s\n", format("Width trick: %*.*d \n", 5, 5, 10).c_str());
    printf("%s\n", format("%s \n", "A string").c_str());

    
    return 0;
}
#endif
