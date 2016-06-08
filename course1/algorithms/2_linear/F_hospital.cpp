#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Node {
    long num;
    Node *next;
};

FILE *fin = fopen("hospital.in", "r");
FILE *fout = fopen("hospital.out", "w");
long n, k;
bool isOdd = false;
char c;
Node *head = NULL, *tail = NULL, *center = NULL;

int main() {
    fscanf(fin, "%ld\n", &n);

    for(long i = 0; i < n; i++) {
        fscanf(fin, "%c", &c);
//        printf(" Started %ld of %ld with %c\n", i+1, n, c);
        if(c == '-') {
            fscanf(fin, "\n");
            fprintf(fout, "%ld\n", head->num);
            Node *del = head;
            head = head->next;

            if(head == NULL) {
                center = NULL;
                tail = NULL;
            } else if(!isOdd) {
                center = center->next;
            }

            if(del != NULL) {
                delete del;
            }
        } else {
            fscanf(fin, "%ld\n", &k);
            Node *temp = new Node;
            temp->num = k;
            temp->next = NULL;

            if(head == NULL) {
                head = temp;
                center = temp;
                tail = temp;
            } else {
                if(c == '+') {
                    tail->next = temp;
                    tail = tail->next;
                }

                if(c == '*') {
                    temp->next = center->next;
                    center->next = temp;
                    if(temp->next == NULL){
                        tail = tail->next;
                    }
                }

                if(!isOdd) {
                    center = center->next;
                }
            }
        }

        isOdd = !isOdd;


//        printf("Finished %ld of %ld with %c\n", i+1, n, c);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
