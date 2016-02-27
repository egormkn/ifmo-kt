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
FILE *file;
int id = 0, temp;

void writeToFile(const char *filename){
	file = fopen(filename, "wt");
	for(int i = 0; i < book.length; i++){
		fprintf(file, "%d %s %s\n", book.contacts[i].id, book.contacts[i].name, book.contacts[i].phone);
	}
	fclose(file);
}

int check(char *input){
	if (!strcmp(input, "")){
        printf("Empty string o_O.\n");
        return 0;
    }

    int i = 0;
    if (isalpha(input[0])){
        while (input[i] != '\0'){
            if (!isalpha(input[i++])){
                printf("Non-alphabet symbols found.\n");
                return 0;
            }
        }
    } else {
        while (input[i] != '\0'){
            if (isdigit(input[i++])){
                return 1;
            }
        }
        printf("Number must contain at least one digit.\n");
        return 0;
    }
    return 1;
}

 int issubstr(char *str, char *substr){
	char *s1 = malloc(strlen(str)*sizeof(char));
	char *s2 = malloc(strlen(substr)*sizeof(char));
	int i = 0;
	while(str[i] != '\0'){
		if (isalpha(str[i])){
			s1[i] = tolower(str[i]);
        }
        i++;
    }
    i = 0;
	while(substr[i] != '\0'){
		if (isalpha(substr[i])){
			s2[i] = tolower(substr[i]);
        }
        i++;
    }
	int r = strstr(s1, s2) != NULL;
	free(s1);
	free(s2);
	return r;
 }

void find(char *query){
	int found = 0;
	for(int i = 0; i < book.length; i++){
		if((isalpha(query[0]) && issubstr(book.contacts[i].name, query)) || (isdigit(query[0]) && !strcmp(book.contacts[i].phone, query))){
			printf("%d %s %s\n", i, book.contacts[i].name, book.contacts[i].phone);
			found = 1;
		}
	}
	if(!found){
		printf("Contact not found.\n");
	}
}

void delete(int i){
	if(i < 0 || i >= book.length){
		printf("Contact with id does not exist.");
		return;
	}
	book.length--;
	free(book.contacts[i].name);
	free(book.contacts[i].phone);
	book.contacts[i].id = book.contacts[book.length].id;
	book.contacts[i].name = book.contacts[book.length].name;
	book.contacts[i].phone = book.contacts[book.length].phone;
	book.contacts = (Contact*) realloc(book.contacts, (book.length + 1) * sizeof(Contact));
	// TODO: FILE UPDATE
}

void change(int i, char *cmd, char *value){
	if(i < 0 || i >= book.length){
		printf("Contact with id does not exist.");
		return;
	}
    if (!strcmp(cmd, "number")){
        strcpy(book.contacts[i].phone, value);
    } else if (!strcmp(cmd, "name")) {
        strcpy(book.contacts[i].name, value);
    } else {
        printf ("Unknown command.\n");
    }
}

void add(int mode, int id, char *name, char *phone){
	book.contacts = (Contact*) realloc(book.contacts, (book.length + 1) * sizeof(Contact));
	book.contacts[book.length].id = id;
	book.contacts[book.length].name = name;
	book.contacts[book.length].phone = phone;
	book.length++;
	// TODO: FILE UPDATE
}

int validate(char c, int mode){ // 0 - буквы, 1 - цифры
	switch (mode){
		case 0:
			return isalpha(c);
		case 1:
			return isdigit(c);
		default:
			return isalnum(c);
	}
}

char *getword(FILE *input, int mode){
    int l = 0, size = 1;
    char *word = NULL, c = fgetc(input);
    while (c != EOF){
		if(validate(c, mode)) {
			if ((l+1) == size){
				size *= 2;
				word = realloc(word, size * sizeof(char));
			}
			word[l++] = c;
			word[l] = '\0';
		} else if (isspace(c) && l > 0){
			break;
		}
		c = fgetc(input);
	}
    return word;
}

int main(int argc, char **argv){
	file = fopen(argv[1], "at+");
	if(file == NULL){
		printf("Failed to open file\n");
		return 0;
	}
	rewind(file);
	book.length = 0;
	book.contacts = NULL;
	char *name = NULL, *phone = NULL, *input = NULL, cmd[7]; /// ????
	while(!feof(file)){
		fscanf(file, "%d", &id);
		name = getword(file, 0);
		phone = getword(file, 1);
		printf("Loaded '%d %s %s'\n", id, name, phone);
		if (check(name) && check(phone)){
			add(0, id++, name, phone);
		}
	}
	fclose(file);
	
	while(1){
		scanf("%s", cmd);
		printf("> %s\n", cmd);
		if (strcmp(cmd, "find") == 0){
			input = getword(stdin, 2);
			if (check(input)){
				find(input);
			}
			free(input);
		} else if (!strcmp(cmd, "create")){
			name = getword(stdin, 0);
			phone = getword(stdin, 1);
			if (check(name) && check(phone))
			add(0, id++, name, phone);
		} else if (!strcmp(cmd, "delete")){
			int del;
			scanf("%d", &del);
			delete(del);
		} else if (!strcmp(cmd, "change")){
			scanf("%d %s", &id, cmd);
			// TODO: check
            input = getword(stdin, strcmp(cmd, "number") ? 0 : 1);
            if (check(input)) {
				change(id, cmd, input);
			}
		} else if (!strcmp(cmd, "exit")){
			writeToFile(argv[1]);
			free(name);
			free(phone);
			free(input);
			for(int i = 0; i < book.length; i++){
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
