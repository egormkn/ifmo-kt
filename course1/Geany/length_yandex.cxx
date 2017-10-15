


#include <cstdio>
#include <string>

using namespace std;

string input = "test";


void generate(string str, int len){
	printf("%s", str.c_str());
  if(str == input){
    printf("%d", len);
    exit(0); // Или что там в плюсах
  }
  for(char c = 0; c < 256; c++){
    generate(str + c, len + 1);
  }
}

int main(int argc, char **argv)
{
	
generate("", 0);
	return 0;
}

