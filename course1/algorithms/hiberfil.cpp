#include<stdio.h>
#include<string.h>
int main(void) {
    FILE* fd = NULL;
    FILE* out = NULL;
    unsigned char buff[2];
    unsigned char* chunk[1024];
    size_t length;
    fd = fopen("C:\\Users\\Egor\\Documents\\QCTF\\hiberfil.sys","r");
    out = fopen("C:\\Users\\Egor\\Documents\\QCTF\\a.png","w+");

    if(NULL == fd) {
        printf("\n fopen() Error!!!\n");
        return 1;
    }

    fread(buff,2,1,fd);

    while(1) {
        if(*buff==137) {
            fread(buff,2,1,fd);

            if(*buff==80) {
                fread(buff,2,1,fd);

                if(*buff==78) {
                    fread(buff,2,1,fd);

                    if(*buff==71) {
                        fread(buff,2,1,fd);

                        if(*buff==13) {
                            fread(buff,2,1,fd);

                            if(*buff==10) {
                                fread(buff,2,1,fd);

                                if(*buff==26) {
                                    fread(buff,2,1,fd);

                                    if(*buff==10) {
                                        int * a,*b,*c,*d,*e,*f,*g,*h,*i;
                                        *a=137;
                                        *b=80;
                                        *c=78;
                                        *d=71;
                                        *e=13;
                                        *f=10;
                                        *g=26;
                                        *h=10;
                                        fwrite(a,2,1,out);
                                        fwrite(b,2,1,out);
                                        fwrite(c,2,1,out);
                                        fwrite(d,2,1,out);
                                        fwrite(e,2,1,out);
                                        fwrite(f,2,1,out);
                                        fwrite(g,2,1,out);
                                        fwrite(h,2,1,out);
                                        break;
                                    } else continue;
                                } else continue;
                            } else continue;
                        } else continue;
                    } else continue;
                } else continue;
            } else fread(buff,2,1,fd);
        }
    }

    unsigned char type[4]= {0,0,0,0};

    while(type[0]!=73 || type[1]!=69 || type[2]!=78 || type[3]!=68) {
        fread(length,sizeof(int),1,fd);
        fread(type,4,1,fd);
        fread(chunk,length+4,1,fd);
        fwrite(length,sizeof(int),1,out);
        fwrite(type,4,1,out);
        fwrite(chunk,length+8,1,out);
    }

    fclose(fd);
    fclose(out);
    return 0;
}
