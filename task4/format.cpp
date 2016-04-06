#include <string>
#include <stdexcept>
#include <cctype>
#include <climits>
#include <cstddef>
#include <algorithm>
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


#ifndef RELEASE
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

    printf("%s\n", format("floats: %4.2a %+.0A %A \n", 3.1416, 3.1416, 3.1416).c_str());
    printf("floats: %4.2a %+.0A %A \n", 3.1416, 3.1416, 3.1416);


    printf("Strings:\n");
    printf("%s\n", format("Strings:\n").c_str());
 
    const char* s = "Hello";
    printf("\t.%10s.\n\t.%-10s.\n\t.%*s.\n", s, s, 10, s);
    printf("%s\n", format("\t.%10s.\n\t.%-10s.\n\t.%*s.\n", s, s, 10, s).c_str());
 
    printf("Characters:\t%c %%\n", 65);
    printf("%s\n", format("Characters:\t%c %%\n", 65).c_str());
 
    printf("Integers\n");
    printf("%s\n", format("Integers\n").c_str());
    printf("Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1);
    printf("%s\n", format("Decimal:\t%i %d %.6i %i %.0i %+i %u\n", 1, 2, 3, 0, 0, 4, -1).c_str());
    printf("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6);
    printf("%s\n", format("Hexadecimal:\t%x %x %X %#x\n", 5, 10, 10, 6).c_str());
    printf("Octal:\t%o %#o %#o\n", 10, 10, 4);
    printf("%s\n", format("Octal:\t%o %#o %#o\n", 10, 10, 4).c_str());
 
    printf("Floating point\n");
    printf("%s\n", format("Floating point\n").c_str());
    printf("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3);
    printf("%s\n", format("Rounding:\t%f %.0f %.32f\n", 1.5, 1.5, 1.3).c_str());
    printf("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5);
    printf("%s\n", format("Padding:\t%05.2f %.2f %5.2f\n", 1.5, 1.5, 1.5).c_str());
    printf("Scientific:\t%E %e\n", 1.5, 1.5);
    printf("%s\n", format("Scientific:\t%E %e\n", 1.5, 1.5).c_str());
    printf("Hexadecimal:\t%a %A\n", 1.5, 1.5);
    printf("%s\n", format("Hexadecimal:\t%a %A\n", 1.5, 1.5).c_str());
    printf("Special values:\t0/0=%g 1/0=%g\n", 0./0, 1./0);
    printf("%s\n", format("Special values:\t0/0=%g 1/0=%g\n", 0./0, 1./0).c_str());
 
    printf("Variable width control:\n");
    printf("%s\n", format("Variable width control:\n").c_str());
    printf("right-justified variable width: '%*c'\n", 5, 'x');
    printf("%s\n", format("right-justified variable width: '%*c'\n", 5, 'x').c_str());
    int r1, r2;
    printf("left-justified variable width : '%*c'%n\n", -5, 'x', &r1);
    printf("%s\n", format("left-justified variable width : '%*c'%n\n", -5, 'x', &r2).c_str());
    printf("(the last printf printed %d characters)\n", r1);
    printf("%s\n", format("(the last printf printed %d characters)\n", r2).c_str());

    
    
    return 0;
}
#endif
