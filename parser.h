#ifndef PARSER_H
#define PARSER_H

#include <stdint.h>

#define MAX_ARGS 10


typedef struct Command_s
{
  char**             argv;
  uint8_t           argc;
  char*             input_file;
  char*             output_file;
  int               append;
  struct Command_s* pipe_to;
  int               background;
} Command_t;


//------------------------------------------------------------------------------
Command_t* Parse(char* input);


//------------------------------------------------------------------------------
void FreeCommand(Command_t* cmd);


#endif /* PARSER_H */
