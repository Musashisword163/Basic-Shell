#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
char *builtinStr[] = {"cd","exit","gondorCallsForAid"};
int myCD(char **args){
    if(args[1] == NULL){fprintf(stderr, "okehMastah: Are thou Dumb, shouldn't you write in the directory you wanna go to ??\n");}
    else {if(chdir(args[1]) !=0){perror("okehMastah: ");}}
    return 1;
}

int numOfBuiltIns(){return (sizeof(builtinStr)/sizeof(char *));}

int dramaticExit(char **args){return 0;}

int skillIssues(char **args){
    int k= numOfBuiltIns();
    printf("This is a shell developed purely for the purpose of Trolling, and making my sorry self believe that I was doing somehting productive\n");
    printf("You type Arguments, and hit Enter I reply\n");
    printf("The following functions are built in: \n");
    for(int i=0;i <k;i++){printf("%d- %s\n",i,builtinStr[i]);}
    printf("You can enter the 'gondorCallsForAid' command for help\n");
    return 1;
}

int (*builtinFunct[])(char **) = {&myCD,&dramaticExit,&skillIssues};

int launchLine(char **args){
    pid_t pid,wpid;
    int status;
    pid = fork();
    if(pid<0){perror("okehMastah: It seems that fork has failed");}  //Fork Failed
    else if(pid==0){//Fork Succeeded but, the replacement of the forked process with the desired program image failed
        if(execvp(args[0], args)==-1){perror("okehMastah: It seems that fork has failed");}
    }
    else{//Parent will wait for the child for the Execution of the child to get completed
        do{wpid = waitpid(pid, &status, WUNTRACED);}while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}

#define TOKEN_DELIM " \t\r\n\a"
#define TOKEN_BUFFER 64;
char **splitLine(char *line){
    int bufSize = TOKEN_BUFFER
    int position = 0;
    char **tokens = malloc(sizeof(char *)*bufSize); //It will kinda act like an array of pointers, where each pointer corresponds to an argument
    if(!tokens){printf("okehMastah: There seems to be an allocation Error\n");return NULL;}
    char *token = strtok(line, TOKEN_DELIM);
    while(token !=NULL){
        tokens[position] = token;
        position++;
        if(position>=bufSize){tokens = realloc(tokens, bufSize * sizeof(char *));bufSize=bufSize*2;}
        if(!tokens){printf("okehMastah: There seems to be an allocation Error\n");return NULL;}
        token = strtok(NULL, TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *readLine2(void){ //Never gonna use this
    char *line = NULL;
    ssize_t bufSize=0;
    if(getline(&line, &bufSize, stdin) ==-1){
        if(feof(stdin)){exit(EXIT_SUCCESS);} //We have recieved the EOF, which means that the command was stored int he buffer successfully
        else{perror("readLine2");exit(EXIT_FAILURE);}
    }
    return line;
}

#define RL_BUFFER 1024;
char *readLine(void){
    int bufSize = RL_BUFFER
    char *buffer = malloc(sizeof(char)*bufSize);
    int c;  //c is an integer cuz some of the characters liek EOF is an EOF
    int position=0;
    if(!buffer){printf("okehMastah: There seems to be an allocation Error\n");return NULL;}
    while(1){               //Now read all the characters in the buffer
        c = getchar();
        if(c==EOF||c=='\n'){buffer[position] = '\0';return buffer;}
        else {buffer[position] = c;}
        position++;
        if(position >=bufSize){
            bufSize+=RL_BUFFER;
            buffer = realloc(buffer, bufSize);
            if(!buffer){fprintf(stderr, "okehMastah: There seems to be an allocation Error\n");return NULL;}
        }
    }
}

int executeLine(char **args){
    int k=numOfBuiltIns();
    if (args[0] == NULL) {return 1;}//Empty COmmand was entered
    for(int i=0;i<k;i++){if(strcmp(args[0], builtinStr[i])==0){return (*builtinFunct[i])(args);}}
    return launchLine(args);
}

void readCommand(void){
    printf("You can enter the 'gondorCallsForAid' command for help\n");
    char *line; //Pointer to the first line (probably) and pointer to each character iteratively
    char **args; //Pointer to the arguiment for each command (probably)
    int status=1;
    while(status){
        printf("OkehMastah> ");
        line = readLine();if(line==NULL){EXIT_FAILURE;}
        args = splitLine(line);if(args==NULL){EXIT_FAILURE;}
        status = executeLine(args);
        free(line);free(args);
    }
}

int main(){
    //Load the config files
    readCommand();//will Interpret the Command
    //Perform the termination
    return EXIT_SUCCESS;
}
