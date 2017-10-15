#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int id;
    char *name;
    char *phone;
} Contact;

typedef struct {
    Contact *contacts;
    int length;
} Contactbook;

Contactbook book;
char *filename;
    return r[mode];
int lastId = 0;

int validate(char c, int mode) {
    int r[3] = {isalpha(c), isdigit(c), isalnum(c)};
}

char *getword(FILE *input, int mode) { // 0 - буквы, 1 - цифры, 2 - авто
    int l = 0, size = 1, err = 0;
    char *word = NULL, c = fgetc(input);
    while (c != EOF) {
        if (!isspace(c)) {
            if (mode == 2) {
                mode = isalpha(c) ? 0 : 1;
            }
            if (validate(c, mode)) {
                if ((l + 1) == size) {
                    size *= 2;
                    word = realloc(word, size * sizeof(char));
                }
                word[l++] = c;
                word[l] = '\0';
            } else if ((c == '+' && l > 0) || (mode == 0) ||
                       (mode != 0 && c != '(' && c != ')' && c != '-' && c != '+')) {
                err = 1;
            }
        } else if (l > 0) {
            break;
        }
        c = fgetc(input);
    }
    if (err == 1) {
        free(word);
        word = NULL;
        printf("Incorrect input\n");
    }
    return word;
}

int getId(int id) {
    for (int i = 0; i < book.length; i++) {
        if (book.contacts[i].id == id) {
            return i;
        }
    }
    return -1;
}

void writeToFile() {
    FILE *file = fopen(filename, "wt");
    for (int i = 0; i < book.length; i++) {
        fprintf(file, "%d %s %s\n", book.contacts[i].id, book.contacts[i].name, book.contacts[i].phone);
    }
    fclose(file);
}

int issubstr(char *s1, char *s2) {
    int i = 0;
    char *a1 = malloc(strlen(s1) * sizeof(char));
    while (s1[i] != '\0') {
        a1[i] = tolower(s1[i]);
        i++;
    }
    a1[i] = '\0';
    i = 0;
    char *a2 = malloc(strlen(s2) * sizeof(char));
    while (s2[i] != '\0') {
        a2[i] = tolower(s2[i]);
        i++;
    }
    a2[i] = '\0';
    int r = (strstr(a1, a2) != NULL);
    free(a1);
    free(a2);
    return r;
}

void find() {
    char *query = getword(stdin, 2);
    if (query != NULL) {
        int found = 0;
        for (int i = 0; i < book.length; i++) {
            if ((isdigit(query[0]) && !strcmp(book.contacts[i].phone, query)) ||
                (isalpha(query[0]) && issubstr(book.contacts[i].name, query))) {
                printf("%d %s %s\n", book.contacts[i].id, book.contacts[i].name, book.contacts[i].phone);
                found = 1;
            }
        }
        if (!found) {
            printf("Contact not found.\n");
        }
    } else {
        printf("Search failed.\n");
    }
    free(query);
}

void delete(
int id
){
id = getId(id);
if(id == -1){
printf("Contact with this id does not exist.");
return;
}
book.length--;
free(book
.contacts[id].name);
free(book
.contacts[id].phone);
book.contacts[id].
id = book.contacts[book.length].id;
book.contacts[id].
name = book.contacts[book.length].name;
book.contacts[id].
phone = book.contacts[book.length].phone;
book.
contacts = (Contact *) realloc(book.contacts, book.length * sizeof(Contact));

writeToFile();

}

void change() {
    int id, mode;
    char cmd[7], *value;
    scanf("%d %s", &id, cmd);
    mode = strcmp(cmd, "number") ? 0 : 1;
    value = getword(stdin, mode);
    if (value != NULL) {
        id = getId(id);
        if (id == -1) {
            printf("Contact with this id does not exist.");
            free(value);
            return;
        }
        if (mode) {
            book.contacts[id].phone = value;
        } else {
            book.contacts[id].name = value;
        }
        writeToFile();
    } else {
        printf("Changing failed.\n");
        free(value);
    }
}

void create(FILE *file, int id) {
    char *name = getword(file, 0);
    char *phone = getword(file, 1);
    if (name != NULL && phone != NULL) {
        if (id > lastId) {
            lastId = id;
        }
        book.contacts = (Contact *) realloc(book.contacts, (book.length + 1) * sizeof(Contact));
        book.contacts[book.length].id = id;
        book.contacts[book.length].name = name;
        book.contacts[book.length].phone = phone;
        book.length++;
        writeToFile();
    } else {
        printf("Loading failed: %d %s %s\n", id, name, phone);
        free(name);
        free(phone);
    }
}

int main(int argc, char **argv) {
    filename = (argc > 1) ? argv[1] : "book.txt";
    FILE *file = fopen(filename, "at+");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 0;
    }
    rewind(file);
    book.length = 0;
    book.contacts = NULL;
    int id;
    while (fscanf(file, "%d", &id) != EOF) {
        create(file, id);
    }
    fclose(file);
    char cmd[7];
    while (1) {
        scanf("%s", cmd);
        if (!strcmp(cmd, "find")) {
            find();
        } else if (!strcmp(cmd, "create")) {
            create(stdin, lastId + 1);
        } else if (!strcmp(cmd, "delete")) {
            scanf("%d", &id);
            delete (id);
        } else if (!strcmp(cmd, "change")) {
            change();
        } else if (!strcmp(cmd, "exit")) {
            writeToFile();
            for (int i = 0; i < book.length; i++) {
                free(book.contacts[i].name);
                free(book.contacts[i].phone);
            }
            free(book.contacts);
            return 0;
        } else {
            printf("Unknown command. Try again.\n");
        }
        fflush(stdout);
    }
}
