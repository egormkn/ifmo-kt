#include <iostream>
#include <climits>

#define is_big_endian (!(union{uint16_t u16; unsigned char c[sizeof(uint16_t)];}){.u16 = 1}.c[0])

using namespace std;

template<typename = double> struct IEEE754 {
    const char s = 1;
	const char e = 11;
    const char m = 52;
};
/*
template<> struct IEEE754<float> {
    const char sign = 1;
	const char exponent = 8;
    const char mantissa = 23;
};*/

template<typename T, typename = void> class binary {
    // Do nothing
};

template<typename T> class binary<T, typename enable_if<is_floating_point<T>::value, void>::type> {
	bool sign = 0;
	unsigned long long mantissa = 0;
	unsigned exponent = 0;
    union {
	    T value = 0;
	    unsigned char bytes[sizeof(T)];
    };
    bool bits[sizeof(T) * CHAR_BIT];
    
    public:
        void set(bool sign, unsigned exponent, unsigned long long mantissa){
            this->sign = sign;
            this->exponent = exponent;
            this->mantissa = mantissa;
            merge();
            fill_bits();
		}

		void set(T value){
            this->value = value;
            split();
            fill_bits();
		}

        void print(){
            printf("%f", this->value);
		}

	    void print_binary(){
			for(unsigned i = 0; i < sizeof(T) * CHAR_BIT; i++){
                cout << (bits[i] ? '1' : '0');
			}
		}

		binary(){
            // Zero-initialized
		}

		binary(bool sign, unsigned exponent, unsigned long long mantissa){
            set(sign, exponent, mantissa);
        }
    
        binary(T value){
			set(value);
        }
        
	private:
        void fill_bits(){
            for(
                unsigned i = is_big_endian ? 0 : sizeof(T);
                (!is_big_endian && i > 0) || (is_big_endian && i < sizeof(T));
                i += is_big_endian ? 1 : -1
            ){
		        unsigned _size = sizeof(char) * CHAR_BIT;
	            for(unsigned _s = 0; _s < _size; ++_s)
		            bits[(8-i)*8+_s] = (this->bytes[i-1] >> (_size - 1 - _s)) & 1;
	        }	
		}
	
        void split(){
            
		}

        void merge(){
            
		}
};


int main(int argc, char **argv){
    binary<double> myfl(1.5);
    myfl.print_binary();
    cout << endl;
	while(true){
		double d;
		cin >> d;
        myfl.set(d);
        myfl.print();
        cout << endl;
        myfl.print_binary();
        cout << endl;
	}
    return 0;
}
/*

    std::string sprintHexFloat(Format const *fmt, double d) {
        const char upperCase[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'P'};
        const char lowerCase[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'p'};
        const char *alpha = fmt->type == A ? upperCase : lowerCase;

        std::string result = fmt->type == A ? "0X" : "0x";
        std::string num;
        std::string hex;
        union {
            double f;
            struct {
                unsigned long long m:52;
                unsigned p:11;
                unsigned s:1;
            };
        } Float;

        Float.f = d;
        int p = Float.p - 1023;

        const char *sign;
        if (fmt->plus && d >= 0) {
            sign = "+";
        } else if (fmt->space && d >= 0) {
            sign = " ";
        } else if (d < 0) {
            sign = "-";
        } else {
            sign = "";
        }
        result = sign + result;

        //??????? Some operations on denormal floats
        if (Float.p == 0 && Float.m != 0) {
            while ((Float.m & ((long long) 1 << 51)) == 0) {
                p--;
                Float.m <<= 1;
            }
            Float.m <<= 1;

            num = "1";
        } else {
            if (Float.m == 0 && Float.p == 0) {
                p = 0;
                num = "0";
            }
            else
                num = "1";
        }

        while (Float.m) {
            char c = alpha[Float.m & 0xF];
            if (c != '0' || hex.size())
                hex = sprintChar(nullptr, c) + hex;
            Float.m >>= 4;
        }

        //correcting precision
        while (fmt->precision > hex.size() && fmt->precision != DEFAULT_PRECISION) {
            hex += "0";
        }

        if (hex.size()) {
            result += num + "." + hex + sprintChar(nullptr, alpha[16]) + format("%+d", p);
        } else if (fmt->sharp) {
            result += num + "." + sprintChar(nullptr, alpha[16]) + format("%+d", p);
        } else {
            result += num + sprintChar(nullptr, alpha[16]) + format("%+d", p);
        }

        return result;
    }

*/
