//GHERASIE STEFANIA ELENA
//313 CB

//returneaza starting whitespaces
int count_starting_ws(char matrix[1000][1000], int line)
{
  int count = 0, i = 0;

  if(matrix[line][0] == '\0')
    return 0;
  if(matrix[line][0] == '\n') 
    return 0;

  for(i = 0; i <= strlen(matrix[line]); i++) {
    if(isspace( matrix[line][i] ) ) 
      count++;
    else break;
  }
  return count;
}

//returneaza trailing whitespaces
int count_trailing_ws( char matrix[1000][1000], int line)
{
  int count = 0, i = 0;

  for(i = strlen(matrix[line])- 2; i >=0 ; i--){
    if(isspace( matrix[line][i] )) 
      count++;
    else break;
  }
  return count;
}

//elimina trailing whitespaces
void remove_trailing_ws(char matrix[1000][1000], int line_count)
  {
    int i,j, index;
    for(i = 0; i < line_count; i++){
      index = -1;
      j = 0;
      while(matrix[i][j] != '\0')
      {
        if(matrix[i][j] != ' ' && matrix[i][j] != '\t' && matrix[i][j] != '\n')
          index = j;
        j++;
      }
      matrix[i][index + 2 ]= '\0';
      matrix[i][index +1] = '\n';
    }
  }

//calculeaza dimensiunea maxima a liniilor
int max_length( char matrix[1000][1000],int line_count)
{ 
  int i, max_length;
  max_length = strlen(matrix[0]) - count_trailing_ws(matrix, 0);

  for(i = 1; i < line_count; i++ )
    if(strlen(matrix[i]) - count_trailing_ws(matrix, i) > max_length)
      max_length = strlen(matrix[i]) - count_trailing_ws(matrix, i);

  return max_length;

}

//center - calculeaza in new_spaces cate spatii
// trebuie adaugate pentru centare
void center(char matrix[1000][1000], int start_line,
            int end_line, int line_count)
{
  int i, j, max, starting_ws, trailing_ws, len, new_spaces;
  char buffer[1000];
  max= max_length(matrix, line_count);

  for(i = start_line; i <= end_line; i++) {
    starting_ws = count_starting_ws( matrix, i);
    trailing_ws= count_trailing_ws(matrix, i);
    len = strlen(matrix[i]) - starting_ws - trailing_ws - 1;
    new_spaces = (max-len)/2;

    strcpy(buffer, "");
    for(j = 1; j <= new_spaces; j++)
    strcat(buffer," ");
    strcat(buffer, matrix[i]);
    strcpy(matrix[i],buffer);

  }
}

//aliniere stanga - muta elementele la stanga,
//depinzand de starting whitespaces
void align_left(char matrix[1000][1000], int start_line, int end_line)
{
  int i, j,count;
  for(i = start_line; i <= end_line; i++){
    count = count_starting_ws( matrix,i);
     for(j = 0; j <= strlen(matrix[i]); j++)
      matrix[i][j] = matrix[i][j+count];
  }
}

//aliniere dreapta, afla cu cate pozitii trebuie mutata linia 
//la dreapta //se folosteste un buffer pt mutare
void align_right(char str[1000], int max)
{
  int j,poz;
  char buffer[1000];
  strcpy(buffer, "");

  poz = max - strlen(str);
  if(poz!= 0)
    {for(j = 1; j <= poz; j++)
      strcat(buffer, " ");
    strcat(buffer, str);
    strcpy(str,buffer);
    }

  }

//paragraf- indenteaza inceputul de paragraf cu valoarea ceruta
void paragraphs( char str[1000], int indent_length )
{
  int i;
  char buffer[1000];

  strcpy(buffer, "");

  for( i= 1; i <= indent_length; i++)
    strcat(buffer, " ");
  strcat(buffer, str);
  strcpy(str, buffer);
}

//trateaza cazul in care listele sunt de tip numeric
//se folosesc 2 siruri intermediare pentru a lista
void list_n(char str[1000], char special_chr, int index )
  {
    char buffer[1000],str1[50], str2[5];

    strcpy(buffer, "");
    sprintf(str1, "%d" , index);

    str2[0] = special_chr;
    str2[1] = ' ';
    str2[2] = '\0';

    strcat(buffer, str1);
    strcat(buffer, str2);
    strcat(buffer, str);
    strcpy(str, buffer);
  }

//trateaza cazul listelor alfabetice
//se folosesc doua siruri intemediare pentru a lista
void list_aA( char str[1000], char special_chr, int ascii_code)
  {
    char buffer[1000], string[5];

    string[0] = (char)ascii_code;
    string[1] = special_chr;
    string[2] = ' ';
    string[3] = '\0';

    strcpy(buffer, "");
    strcat(buffer, string);
    strcat(buffer, str);
    strcpy(str, buffer);
  }

//trateaza cazul listelor de tip bullet
void list_b( char str[1000],char special_chr)
{
    char buffer[1000], string[5];
    strcpy(buffer, "");

    string[0] = special_chr;
    string[1] = ' ';
    string[2] = '\0';

    strcat(buffer, string);
    strcat(buffer, str);
    strcpy(str, buffer);
}
  
//liste - studiaza cazul fiecarui tip de liste  
void lists( char matrix[1000][1000],char list_type,
            char special_chr, int start_line, int end_line)
{  
  int i,index;
  char ascii_code;
  switch(list_type) {
    case 'n':     //lista numerotata
      index = 1;
      for(i = start_line; i <= end_line; i++) {
        list_n(matrix[i], special_chr, index);
         index++;
      }
      break;

    case 'a':     //lista alfabetica a // se foloseste ASCII
      ascii_code = 97;
        for(i = start_line; i <= end_line; i++) {
          list_aA(matrix[i], special_chr, ascii_code);
            ascii_code++;
         }
      break;

      case 'A':    //lista alfabetica A // se foloseste ASCII
        ascii_code = 65;
          for(i = start_line; i <= end_line; i++) {
            list_aA(matrix[i], special_chr, ascii_code);
              scii_code++;
        }
        break;

      case 'b':   //lista bullet
        for(i = start_line; i <= end_line; i++)
          list_b(matrix[i],special_chr);
      break;

      default: break;
    }
}

//liste ordonate - se ordoneaza crescator/descrescator 
void ordered_lists(char matrix[1000][1000], char ordering, int start_line,int end_line)
{
  char buffer[1000];
  int i,j;
  if(ordering == 'a')     //crescator
    for(i = start_line; i <= end_line; i++)
      for(j = i+1; j <= end_line; j++){
        if(strcmp(matrix[i], matrix[j]) > 0) {}
          strcpy(buffer, "");
          strcpy(buffer, matrix[j]);
          strcpy(matrix[j], matrix[i]);
          strcpy(matrix[i], buffer);
      }
        
  else if(ordering == 'z')
    for(i = start_line; i <= end_line; i++)
      for(j = i+1; j <= end_line; j++) {
        if(strcmp(matrix[i], matrix[j]) < 0) {
           strcpy(buffer, "");
           strcpy(buffer, matrix[j]);
           strcpy(matrix[j], matrix[i]);
           strcpy(matrix[i], buffer);
         }
      }

}

//justify
void justify(char str[1000], int max)
{
  int j,i;

  for(j = 0; j < strlen(str); j++)
  for(i = 0; i < strlen(str)  && (strlen(str) < max); i++)
    //daca nu s-a atins inca lungimea maxima se muta linia cu o pozitie
    // la dreapta si se introduce un spatiu
    if(str[i] == ' ') {
      memmove(str +i +1, str +i ,strlen(str) - i);
      str[i+1] = ' ';
      i += 2;
    }
}

//returneaza lungimea unui cuvant
int word_length(char str[1000000])
{
  int index = 0;
  while(isspace(str[index]) == 0 && str[index] != '\0')
    index++;
  return index;
}

//inlocuieste caracterele \n din sirul str cu spatiu 
//pentru a putea apoi aplica operatia wrap
void remove_newline( char str[1000000])
{ 
  int index = 0;
  
  while(str[index] != '\0'){
    if( str[index] == '\n')
      str[index] = ' ';
    index++;  
  }  
}

//wrap
void wrap(char str[1000000], int max_line_length)
{
  int index = 0, len = 0;

  while(str[index] != '\0') {
    if(str[index] == '\n')  //intalneste \n si trece pe urmatoarea linie
      len = 0;          
     if(str[index] == ' ') {
      //la spatiu verifica daca cuvantul este complet si daca
      //are loc pe linie, fara sa depaseasca valoarea impusa
      if( len + word_length(&str[index+1]) > max_line_length){
        str[index] = '\n';
        len = 0;
      }
    }
    len++;
    index++;
  }

}