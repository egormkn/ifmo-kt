

int check(char *input, int mode){
	if(input == NULL){
		return 0;
	}
	if (!strcmp(input, "")){
        printf("Empty string o_O.\n");
        return 0;
    }

    int i = 0;
    if (mode == 0){
        while (input[i] != '\0'){
            if (!isalpha(input[i++])){
                printf("Non-alphabet symbols found.\n");
                return 0;
            }
        }
    } else if (mode == 1){
        while (input[i] != '\0'){
            if (isdigit(input[i++])){
                return 1;
            }
        }
        printf("Number must contain at least one digit.\n");
        return 0;
    } else if (mode == 2){
		while (input[i] != '\0'){
            if (!isalnum(input[i++])){
                printf("Unexpected symbols found.\n");
                return 0;
            }
        }
	}
    return 1;
}

 int issubstr(char *str, char *substr){
	char *s1 = malloc((strlen(str)+1)*sizeof(char));
	char *s2 = malloc((strlen(substr)+1)*sizeof(char));
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
	int r = (strstr(s1, s2) != NULL);
	free(s1);
	free(s2);
	return r;
 }
