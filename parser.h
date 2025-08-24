#ifndef PARSER_H
#define PARSER_H


#define MAX_ARGS 10


typedef struct
{
  char* args[MAX_ARGS];
  int arg_count;
} Parser_t;


void Parse(char* input);
void CleanParser(void);

#endif /* PARSER_H */