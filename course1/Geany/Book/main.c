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
int id = 0;

/*


bool checkInput(char *input)
{
    if (!strcmp(input, ""))
    {
        printf("Error: missing input.\n");
        return false;
    }

    int i = 0;
    if (isalpha(input[0]))
    {
        while (input[i] != '\0')
        {
            if (!isalpha(input[i++]))
            {
                printf("Error: only A-Z and a-z symbols are allowed in contact's name.\n");
                return false;
            }
        }
    }
    else
    {
        while (input[i] != '\0')
        {
            if (isdigit(input[i++]))
            {
                return true;
            }
        }
        printf("Error: contact's number must contain at least one digit.\n");
        return false;
    }
    return true;
}

int findByID(int id)
{
    int i;
    for (i = 0; i < book.size; i++)
    {
        if (book.persons[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

char *makeNeutral(char *input)
{
    int i = 0;
    bool isName = (isalpha(input[0]) ? true : false);
    char *answer = malloc(strlen(input)*sizeof(char));

    i = 0;
    int j = 0;
    if (!isName)
    {
        while(input[i] != '\0')
        {
            if (isdigit(input[i]))
            {
                answer[j++] = input[i];
            }
            i++;
        }
        answer[j] = '\0';
    }
    else
    {
        while(input[i] != '\0')
        {
            answer[i] = tolower(input[i++]);
        }
        answer[i] = '\0';
    }
    return answer;
}

void fileUpdate()
{
    freopen(fileName, "w", source);
    int i;
    for (i = 0; i < book.size; i++)
    {
        if (book.persons[i].id)
        {
            fprintf(source, "%d %s %s\n", book.persons[i].id, book.persons[i].name, book.persons[i].number);
        }
    }
    freopen(fileName, "a+", source);
    return;
}

 */


int findByID(int id){
    int i;
    for (i = 0; i < book.size; i++)
    {
        if (book.persons[i].id == id)
        {
            return i;
        }
    }
    return -1;
}


void find(char *query){
	// TODO: LOWERCASE, DELETE CHECK
	
	int found = 0;
	for(int i = 0; i < book.length; i++){
		if((isalpha(query[0]) && strstr(book.contacts[i].name, query) != NULL) || (isdigit(query[0]) && !strcmp(book.contacts[i].phone, query))){
			printf("%d %s %s\n", book.contacts[i].id, book.contacts[i].name, book.contacts[i].phone);
			found = 1;
		}
	}
	if(!found){
		printf("Contact not found.\n");
	}
}

void delete(int id){
	/*

	int i = findByID(id);
    if (i >= 0)
    {
        book.persons[i].id = 0;
        fileUpdate();
    }
    return;

	*/
}

void create(){
	
}

void change(int id, char *command, char *newValue){
	/*

	int i = findByID(id);
    if (i >= 0)
    {
        if (!strcmp(command, "number"))
        {
            strcpy(book.persons[i].number, newValue);
        }
        else if (!strcmp(command, "name"))
        {
            strcpy(book.persons[i].name, newValue);
        }
        else
        {
            printf ("Error: don't understand command \"%s\".\n", command);
            return;
        }
        fileUpdate();
    }
    return;
	
	 */
}

void add(int mode, int id, char *name, char *phone){
	book.contacts = (Contact*) realloc(book.contacts, (book.length + 1) * sizeof(Contact));
	book.contacts[book.length].id = id;
	book.contacts[book.length].name = name;
	book.contacts[book.length].phone = phone;
	book.length++;

	printf("***%d**%s**%s***\n", id, name, phone);




	/*

	book.size++;
    book.persons = realloc(book.persons, book.size*sizeof(Person));
    book.persons[book.size - 1].id = curID;
    book.persons[book.size - 1].name = name;
    book.persons[book.size - 1].number = number;
    fprintf(source, "%d %s %s\n", curID++, name, number);
    return;
	
	*/ 
}

int validate(char c, int mode){ // 0 - буквы, 1 - цифры
	switch (mode){
		case 0:
			return isdigit(c);
		case 1:
			return isalpha(c);
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
	while(!feof(file) && fscanf(file, "%d", &id) == 1){
		name = getword(file, 0);
		phone = getword(file, 1);
		add(0, id, name, phone);
	}
	
	while(1){
		scanf("%s", cmd);
		if (strcmp(cmd, "find") == 0){
			input = getword(stdin, 2);
			// if checkInput(input)
			find(input);
			free(input);
		} else if (!strcmp(cmd, "create")){
			name = getword(stdin, 0);
			phone = getword(stdin, 1);
			// if (checkInput(name) && checkInput(number))
			add(0, ++id, name, phone);
		} else if (!strcmp(cmd, "delete")){
			int del;
			scanf("%d", &del);
			// TODO: SMART DELETE
			delete(del);
		} else if (!strcmp(cmd, "change")){
			scanf("%d %s", &id, cmd);
            input = getword(stdin, strcmp(cmd, "number") ? 0 : 1);
            //if (checkInput(input)) {
            change(id, cmd, input);
		} else if (!strcmp(cmd, "exit")){
			fclose(file);
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
