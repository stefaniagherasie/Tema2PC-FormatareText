//GHERASIE STEFANIA ELENA 
// 313 CB

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "functions.h"

#define SEPARATORS " ,"
#define OPERATIONS "WwCcLlRrJjPpIiOo"


int main(int argc, char *argv[]) {
  char buf[1000],               // buffer used for reading from the file
      original[1000][1000],     // original text, line by line
      result[1000][1000];       // text obtained after applying operations
  int original_line_count = 0,  // number of lines in the input file
      result_line_count = 0,    // number of lines in the output file
      i;

  if (argc != 4) {  // invalid number of arguments
    fprintf(stderr,
            "Usage: %s operations_string input_file output_file\n",
            argv[0]);
    return -1;
  }

  // Open input file for reading
  FILE *input_file = fopen(argv[2], "r");

  if (input_file == NULL) {
    fprintf(stderr, "File \"%s\" not found\n", argv[2]);
    return -2;
  }

  // Read data in file line by line
  while (fgets(buf, 1000, input_file)) {
    strcpy(original[original_line_count], buf);
    original_line_count++;
  }

  fclose(input_file);

  /*
   * TODO apply operations in operation_string (argv[1]) one by one and save
   * the result in the 'result' matrix.
  */


  int  j, k, ok,indent_length, line_index = 1, index, index_buf, line,
      start_line, end_line,max, max_line_length;
  int  values[10][20];

  char  arguments[10][20], buffer[1000], str[1000000];    
  char  *command = strdup(argv[1]);
  char  special_chr, list_type, ordering;
  
  ok = 1; k = 0; j = 1; i = 1;
 
  //despartim sirul initial in subsiruri pentru a obtine operatiile
  //numele operatiilor si ale argumente care nu sunt intregi sunt 
  //stocate in "arguments", iar valorile intregi in tabloul "values"

  char *operation = strtok(command, SEPARATORS);


  arguments[1][1]= operation[0];
  operation = strtok(NULL, SEPARATORS);
  while(operation) {
    
    if(isdigit(operation[0]) != 0) {
      values[line_index][i] = atoi(operation);
      i++; }
    else if(strchr(OPERATIONS,operation[0]) != NULL) {
      line_index++; i = 1; j = 1;
      arguments[line_index][j] = operation[0];
      }
    else {
      j++;
      arguments[line_index][j] = operation[0];
      
      }
    operation = strtok(NULL, SEPARATORS);
    }
    //verificam daca nu s-au introdus mai mult de 10 operatii
    if(line_index > 10) 
   {
      printf("Too many operations! Only the first 10 will be applied.\n" );
      line_index = 10;
    }

    //testam daca exista operatii invalide
    for(k = 1; k <= line_index; k++)
      if(strchr(OPERATIONS,arguments[k][1]) == NULL)
        {printf("Invalid operation");
         ok = 0;
         break;}
    //aplicam toate operatiile
    if(ok == 1)
    for(k = 1; k <= line_index; k++) {
      //operatiile LRCJ au start_line si end_line pe 
      //prima/a doua pozitie in values
      if(strchr("LRCJlrcj",arguments[k][1])  != 0) {
        start_line = values[k][1];
        end_line = values[k][2];
        if(end_line == 0 || end_line > original_line_count)
          end_line = original_line_count -1;
      }

      //operatia Center 
      if(arguments[k][1] == 'C' || arguments[k][1] == 'c') {

          if(start_line < original_line_count)
            center(original,start_line, end_line, original_line_count);
      }
      
      //operatia Align Left
      else if(arguments[k][1] == 'L' || arguments[k][1] == 'l') {

          if(start_line < original_line_count)
          align_left(original,start_line, end_line);
      }

      //operatia Align Righ pentru care se calculeaza 
      //lungimea maxima a unei linii
      else if(arguments[k][1] == 'R' || arguments[k][1] == 'r') {
          if(start_line < original_line_count){
             max = max_length(original,original_line_count);
            
          for(i = start_line; i<= end_line; i++ )
            if(original[i][0] != '\n')
              align_right(original[i],max);}
          }
          
      //operatia Paragraf
      else if(arguments[k][1] == 'P' || arguments[k][1] == 'p') {
        //se obtin parametrii necesari
        indent_length = values[k][1];
        start_line = values[k][2];
        end_line = values[k][3];
        if(end_line == 0 || end_line > original_line_count)
          end_line = original_line_count - 1;

        if(start_line < original_line_count)
          for(i = start_line; i <=end_line; i++)
            //se testeaza daca ne aflam pe prima linie 
            //sau pe ultima dintr-un paragraf
            if(original[i-1][0] == '\n'|| i == 0)
              paragraphs(original[i], indent_length);
      }          

      //operatia Liste Neordonate
      else if(arguments[k][1] == 'I' || arguments[k][1] == 'i') {
          //se obtin parametrii caracteristici
          list_type = arguments[k][2];
          special_chr = arguments[k][3];
          start_line = values[k][1];
          end_line = values[k][2];
          if(end_line == 0 || end_line > original_line_count)
            end_line = original_line_count -1; 

          if(start_line < original_line_count)
            lists(original,list_type,special_chr,start_line,end_line);
      }
      
      //operatia Liste Ordonate 
      else if(arguments[k][1] == 'O' || arguments[k][1] == 'o') {
          //se obtin parametrii caracteristici
          list_type = arguments[k][2];
          special_chr = arguments[k][3];
          ordering = arguments[k][4];
          start_line = values[k][1];
          end_line = values[k][2];
          if(end_line == 0 || end_line > original_line_count)
            end_line = original_line_count - 1;

          if(start_line < original_line_count) {
            //se aliniaza la stanga
            align_left(original,start_line, end_line);
            //se apeleaza functia de ordonare dupa care se listeaza ca la I
            ordered_lists(original, ordering,start_line, end_line);
            lists(original,list_type,special_chr,start_line,end_line);
          }
      }

      //operatia Justify
      else if(arguments[k][1] == 'J' || arguments[k][1] == 'j') {
          remove_trailing_ws(original, original_line_count);
          max = max_length(original,original_line_count);

          if(start_line < original_line_count)
            for( i = start_line; i <= end_line; i++)
              if(i != original_line_count -1 && strlen(original[i+1]) != 1){
                //se aliniaza la stanga si se aplica functia justify
                align_left(original, i, i);
                justify(original[i],max);
              }

      }

      //operatia  Wrap
      else if(arguments[k][1] == 'W' || arguments[k][1] == 'w') {
          remove_trailing_ws(original, original_line_count);
          //se obtin parametrii necesari
          max_line_length = values[k][1];
          //se initializeaza un sir str care contine toate liniile matricei
          strcpy(str, "");
          for(i =0 ; i <= original_line_count; i++){
            //se testeaza daca avem un rand gol,caz in care il marcam 
            //in str prin "~"
           // if(original[i][0] == '\n' )
            //  original[i][0] = '~';
            strcat(str, original[i]);
          }
          //se sterg toate caracterele \n din str
          newline(str);
          
          while(str[index] != '\0') {
            //testam daca matricea a continut trailing whitespace 
            //si in acest caz le stergem din str

            //if(str[index] == ' ' && str[index+1] == ' '){
             //memmove(str + index , str + index +1, strlen(str) - index+1);
             //index--;              
            //}

            //inseram liniile goale
            if(str[index] == '\n'){
             str[index] = '\n';
             memmove(str + index +1, str + index, strlen(str) - index+1);
             str[index+1] = '\n';
             index++;
            }
            index++;
          } 
          //se apeleaza functia de wrap pentru str
          wrap(str, max_line_length);

          line = 0; index_buf=0; index = 0;
          //copiem continutul lui str in matricea initiala
          for(i =0 ; i <= original_line_count; i++)
              strcpy( original[i], "");
          strcpy(buffer, "");
          while(str[index] != '\0') {
            if(str[index] == '\n')
            {  
              strcpy(original[line], buffer);
              line++;
              memset(buffer, '\0', 1000);
              index_buf = 0;
            }
            else
            {
              buffer[index_buf] = str[index];
              index_buf++;
            }

            index++;
          }

          strcpy(original[line],buffer);
          original_line_count = line +1;
      }
    //dupa fiecare operatie se elimina trailing whitespaces
    for(i = 0; i <= original_line_count; i++)
    remove_trailing_ws(original, i);
      }

  //se copiaza matricea initiala in cea rezultat
  for (i = 0; i < original_line_count; i++) {
    strcpy(result[i], original[i]);
  }
  result_line_count = original_line_count;
  // Open output file for writing
  FILE *output_file = fopen(argv[3], "w");

  if (output_file == NULL) {
    fprintf(stderr, "Could not open or create file \"%s\"\n", argv[3]);
    return -2;
  }

  // Write result in output file
  for (i = 0; i < result_line_count; i++) {
    fputs(result[i], output_file);
  }

  fclose(output_file);

}

