#include <string>
#include <stdexcept>
#include <cctype>
#include <climits>
#include "format.h"

using namespace std;

string format(const string &fmt){
	printed = 0;
    unknown_spec = "";

    string result = "";
    unsigned pos = 0;
    while(pos < fmt.length()){
        for(; pos < fmt.length() && fmt[pos] != '%'; result.push_back(fmt[pos++]));
        if(pos == fmt.length()){
            return result;
        } else if(pos == fmt.length() - 1){
            printf("Spurious trailing '%%' in format [-Wformat=]\n");
            return result;
        } else if(fmt[pos + 1] == '%'){
            result.push_back('%');
            pos += 2;
        } else {
            pos++;
            printf("Need more arguments or unknown format\n");
        }
    }
    return result;
}

int main(){
    /*
    long g = INT_MAX;
    printf("%s\n", format("Format:   %-5.20lx %.10d", g, 10).c_str());
    printf("Original: %-5.20lx %.10d\n", g, 10);


    int val = 0;
    printf("%s\n", format("blah %n blah", &val).c_str());
    printf("%s\n", format("val = %d\n", val).c_str());

    printf("%s\n", format("%-*.*wd test", 10).c_str());



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

    char zz[] = "foo%% test %% %%%% %i";
    printf("Need: ");
    printf(zz);
    printf("\n");
    printf("Got:  %s\n", format(zz).c_str());
*/

    printf("%s\n", format("Characters: %c %c \n", 'a', 65).c_str());
    printf("%s\n", format("Decimals: %d %ld\n", 1977, 650000L).c_str());
    printf("%s\n", format("Preceding with blanks: %10d \n", 1977).c_str());
    printf("%s\n", format("Preceding with zeros: %010d \n", 1977).c_str());
    printf("%s\n", format("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100).c_str());
    printf("%s\n", format("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416).c_str());
    printf("%s\n", format("Width trick: %*d \n", 5, 10).c_str());
    printf("%s\n", format("%s \n", "A string").c_str());

    
    return 0;
}
