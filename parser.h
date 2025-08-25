#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define MAX_ARGS 10


typedef struct
{
  uint8_t bitmap;
  char*   args[MAX_ARGS];
  int     arg_count;
} Parser_t;


//------------------------------------------------------------------------------
void Parse(char* input);


//------------------------------------------------------------------------------
void CleanParser(void);


//------------------------------------------------------------------------------
char** GetParserArgs(int* arg_count);

#endif /* PARSER_H */
