#include<stdio.h>
#include<string.h>

			/* FUNCTIA CARE VERIFICA DACA UN SIR REPREZINTA UN 
					NUMAR NATURAL */

int numar_natural (char *sir) {
   int n ;
   for( n = 0 ; n < strlen( sir ) ; n ++ )
   {
// valoarea lui 0 in ASCII e 48 si a lui 9 e 57.
      if (sir [ n ] < 48 || sir [ n ] > 57) {
         return 0 ;
      }
   }
 
   return 1 ;
}

			// FUNCTIA CARE TRANSFORMA UN SIR INTR-UN NR NATURAL

int din_sir_in_numar ( char *caracter ) {  
   int numar = 0 ;
   while ( ( *caracter >= '0') && ( *caracter <= '9')) {
// functia tranforma un sir de caractere intr-un nr natural.
	numar = ( numar * 10 ) + ( *caracter - '0') ;
	caracter++ ;
   }
   return numar ;
}



			// FUNCTIA CE ELIMINA TRAILING WHITESPACE-URILE

int no_whitespace ( char * sir ) {
   int j ;
   int NewStrlen ;
   for ( j = 0 ; j < strlen ( sir ) ; j++ ) {
	if( sir [ j ] != ' ' && sir [ j ] != '\n' &&
	    sir [ j ] != '\t' ) {
	   NewStrlen = j ; 
	}
	if( sir [ j ] == '\n' ) {
	   sir [ NewStrlen + 1 ] = '\n' ;
	   NewStrlen ++;
	}
   }
   sir [ NewStrlen + 1 ] = '\0' ;

return 0 ;
}



			// FUNCTIA WRAP

int wrap ( char original[1000][1000] , char *max_line_length , char *null1 ,
	  char *null2 , char *null3 , char *null4 , 
	  int original_line_count ) {

   char *word ;
   int max_word_length = 0 ;
   int n ;
   char cannot [1000][1000] ;
   int k ;
// mai facem o matrice asemanatoare si una goala :
   for( k = 0 ; k <= original_line_count ; k++ ) {
    strcpy( cannot  [ k ] , original [ k ] ) ;
   }
// trebuie sa fie un numar.
   if( numar_natural ( max_line_length ) == 0 ) {
	printf("Invalid operation!\n") ;
        return -1 ; 
   }
// daca mai avem declaratii parametrii in plus la functia Wrap :
   if( ( *null1 != ',' ) || ( *null2 != ',' ) ||
       ( *null3 != ',' ) || ( *null4 != ',' ) ) {
   	printf("Invalid operation!\n") ;
	return -1 ; 
   }
// daca avem un cuvant mai mare decat max_line_length :
   for( n = 0 ; n <= original_line_count ; n++ ) {
      word = strtok ( cannot  [ n ] , " " ) ;
      strcpy( cannot [ n ] , " " ) ;
      while ( word != NULL ) {
        if( strlen ( word ) > max_word_length ) {
       	  max_word_length = strlen ( word ) ;
        }
        word = strtok ( NULL , " " ) ;
      } 
   }
   if( max_word_length > din_sir_in_numar ( max_line_length ) ) {
        printf("Cannot wrap!\n") ;
	return -1 ; 
   }

//Wrapul propriu-zis : 
   char matrix [ 1000 ] [ 1000 ] ;
   int q = 0 , t = 0 ;
   int y ;
   int space ; 
   int spaces [ 1000 ] ;
   int max = din_sir_in_numar ( max_line_length ) ;
// eliminam spatiile goale de la sfarsitul propozitiei :
// daca avem un paragraf nou retinem cate spatii are la inceput :
   for( n = 0 ; n <= original_line_count ; n++ ) {
	no_whitespace ( original [ n ] ) ;
        if( (n == 0 && strlen( original [ n ] ) > 1) ||
	(strlen( original [ n ] ) > 1 && strlen( original [ n - 1 ] ) == 1) ) {
 	   for( y = 0 ; y < strlen( original [ n ] ) ; y++ ) {
		if( original [ n ] [ y ] == ' ' ) {
		   space++ ;
                }
		else {
		   break ; 
		}
	   }
	   spaces [ t ] = space ;
	   space = 0 ;
	   t++ ;
	}
   }
   t = 0 ;
// impartim fiecare propozitie pe cuvinte :
   for( n = 0 ; n <= original_line_count ; n++ ) {
// in caz ca avem o linie goala ( \n ) :
 	if( strlen ( original [ n ] ) == 1 ) {
	   strcat( matrix [ q ] , original [ n ] ) ;
	   q++ ;
	   n++ ;
	}
	word = strtok ( original [ n ] , " '\n' ") ;
	while( word != NULL ) {
// daca avem un paragraf nou :
	   if( strlen ( matrix [ q ] ) == 0 ) {
	        if( spaces [ t ] >= max ) { 
		    strcat( matrix [ q ] , "\n" ) ;
		    spaces [ t ] = spaces [ 0 ] ;
		}
		for( y = 0 ; y < spaces [ t ] ; y++ ) {
		    strcat( matrix [ q ] , " " ) ;
		}
		strcat( matrix [ q ] , word ) ;
		t++ ;
	   }
// cat timp nu depaseste limita :
           else if( strlen ( matrix [ q ] ) + strlen ( word ) + 1 <= max ) {
	   	strcat( matrix [ q ] , " " ) ;
		strcat( matrix [ q ] , word ) ;
	   }
// daca o depaseste :
	   else {
		strcat( matrix [ q ] , "\n" ) ;
		q++ ;
		strcat( matrix [ q ] , word ) ;
	   }
           word = strtok ( NULL , " '\n' ") ;
        }
// in caz ca s-a terminat paragraful ( urm linie e goala ) :
	if( strlen( original [ n + 1 ] ) == 1 ) {
	    strcat( matrix [ q ] , "\n" ) ;
	    q++;
	}

   }
   strcat( matrix [ q ] , "\n" ) ;
// copiem in matricea originala :
   for( n = 0 ; n <= q ; n++ ) {
     strcpy( original [ n ] , matrix [ n ] ) ;
     strcpy( matrix [ n ] , " " ) ;
   }
// returnam noul original_line_count ;
return q;
}  


			// FUNCTIA CENTER

int center ( char original[1000][1000] , char *start_line , char *end_line ,
	  char *null1 , char *null2 , char *null3 ,
	  int original_line_count ) {
// cazurile speciale ale lui center :
   int startline ;
   int endline ;

   if( (*null1 != ',') || (*null2 != ',') || (*null3 != ',') ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n");
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n");
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ;
   }
   if( startline > original_line_count ) {
 	return 0 ; 
   } 
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }
// Center-ul propriu-zis :
   int lungime_maxima_rand = 0 ;
   int lungimi_rand [ original_line_count ] ;
   int i , j ;
   int diferenta ;
// verificam sa nu avem white_space-uri :
   for( i = 0 ; i<= original_line_count ; i++ ) {
	no_whitespace ( original [ i ] ) ;
   }
// calculam lungimea maxima + punem lungimile intr-un vector :
   for( i = 0 ; i < original_line_count ; i++ ) {
	lungimi_rand [ i ] = strlen( original [ i ] ) - 1 ;
	if( strlen( original [ i ] ) - 1 > lungime_maxima_rand ) {
	    lungime_maxima_rand = strlen( original [ i ] ) - 1 ;
	}
   }

   for( i = startline ; i <= endline ; i++ ) {
     if( lungimi_rand [ i ] != 0 ) {
	diferenta = lungime_maxima_rand - lungimi_rand [ i ] ;
	if( diferenta % 2 == 1 ) {
	    diferenta++ ;
	}
// mutam totul la dreapta cu cat este nevoie :
	for( j = lungimi_rand [ i ] + 1 ; j >= 0 ; j-- ) { 
	    original [ i ] [ j + diferenta/2 ] = original [ i ] [ j ] ;
	}
// umplem inceputul randului cu spatii :
	for( j = 0 ; j < diferenta/2 ; j++ ) {
	    original [ i ] [ j ] = ' ' ;
	}
     }
   }
return 0 ;
}



			// FUNCTIA ALIGN LEFT

int align_left( char original[1000][1000] , char *start_line , char *end_line ,
	  char *null1 , char *null2 , char *null3 ,
	  int original_line_count ) {
// cazurile speciale ale lui align left :
   int startline ;
   int endline ;

   if( (*null1 != ',') || (*null2 != ',') || (*null3 != ',') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n");
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n");
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }
// Align-left-ul propriu-zis :
   int prima_litera = 0 ;
   int i , j ;

   for( i = startline ; i <= endline ; i++ ) {
      if( strlen ( original [ i ] ) > 1 ) {
	for( j = 0 ; j < strlen ( original [ i ] ) ; j++ ) {
	    if ( original [ i ] [ j ] != ' ' && original [ i ] [ j ] != '\t' &&
		 original [ i ] [ j ] != '\n' ) {
		prima_litera = j ;
		break ;
	    }
	}
	for( j = prima_litera ; j <= strlen ( original [ i ] ) ; j++ ) {
	    original [ i ] [ j - prima_litera ] = original [ i ] [ j ] ;
	}
      }
   }
// verificam sa nu avem white_space-uri :
   for( i = 0 ; i<= original_line_count ; i++ ) {
	no_whitespace ( original [ i ] ) ;
   }
return 0 ;
}




		// FUNCTIA ALIGN RIGHT

int align_right ( char original[1000][1000] , char *start_line , char *end_line ,
	  char *null1 , char *null2 , char *null3 ,
	  int original_line_count ) {
// cazurile speciale ale lui align right :
   int startline ;
   int endline ;

   if( (*null1 != ',') || (*null2 != ',') || (*null3 != ',') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }
// Align right-ul propriu-zis :
   int lungime_maxima_rand = 0 ;
   int lungimi_rand [ original_line_count ] ;
   int i , j ;
   int diferenta ;
// calculam lungimea maxima + punem toate lungimiile intr-un vector :
   for( i = 0 ; i < original_line_count ; i++ ) {
	lungimi_rand [ i ] = strlen( original [ i ] ) - 1 ;
	if( lungimi_rand [ i ] > lungime_maxima_rand ) {
	    lungime_maxima_rand = lungimi_rand [ i ] ;
	}
   }
// mutam totul la dreapta :
   for( i = startline ; i <= endline ; i++ ) {
   if( (lungimi_rand [ i ] != 0) && 
       (lungimi_rand [ i ] != lungime_maxima_rand) ) {
	diferenta = lungime_maxima_rand - lungimi_rand [ i ] ;
	for( j = lungime_maxima_rand ; j >= diferenta ; j-- ) {
	    original [ i ] [ j ] = original [ i ] [ j-diferenta ] ;
	}
	for( j = 0 ; j < diferenta ; j++ ) {
	    original [ i ] [ j ] = ' ' ;
	}
   }
   }
return 0 ;
}



			// FUNCTIA JUSTIFY 

int justify ( char original[1000][1000] , char *start_line , char *end_line ,
	  char *null1 , char *null2 , char *null3 ,
	  int original_line_count ) {
// cazurile speciale ale lui justify :
   int startline ;
   int endline ;

   if( (*null1 != ',') || (*null2 != ',') || (*null3 != ',') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }
// aliniem la stanga intervalul respectiv :
   align_left( original , start_line, end_line , null1 , null2 , null3 ,
   original_line_count ) ;

   int lungime_max = 0 ;
   int i ;
   int j , k ;
   int space_found = 0 ;
// calculam lungimea maxima :
   for( i = startline ; i <= endline ; i++ ) {
	if( strlen ( original [ i ] ) - 1 > lungime_max ) {
	    lungime_max = strlen ( original [ i ] ) - 1 ;
	}
   }
// cat timp lungimea propozitiei este < ca lungimea max adauga spatii :

   for( i = startline ; i<= endline ; i++ ) {
	k = 0 ;
     if( strlen( original [ i ] ) - 1 > 0 ) {
	while( strlen( original [ i ] ) - 1 < lungime_max ) {
// daca urm linie e nula inseamna ca propozitia e sf de paragraf si o ignoram :
	   if( strlen( original [ i + 1 ] ) <= 1 )  {
	      break ;
	   }
// daca gasim un spatiu mai punem unul langa el :
	   if( original [ i ] [ k ] == ' ' ) {
	      space_found = 1 ;
	      for( j = strlen( original [ i ] ) + 1 ; j > k + 1 ; j-- ) {
		 original [ i ] [ j ] = original [ i ] [ j - 1 ] ;
	      }
	      original [ i ] [ k + 1 ] = ' ' ;
	      k+= 2 ;
	   }
	   k++ ;
// daca am parcurs propozitia si nu avem spatii ( avem un singur cuvant) :
	   if( (k >= strlen( original [ i ] ) - 1 ) && (space_found = 0) ) {
	  	i++ ;
		break ;
	   }
// daca am pus spatii peste tot si tot nu avem lungimea buna, reincercam :
	   if( k >= strlen( original [ i ] ) - 1 )	{
		k = 0 ;
	   }
   	}
   	space_found = 0 ;
     }	
   }    
return 0 ;
}






			// FUNCTIA PARAGRAFE

int paragrafe ( char original[1000][1000] , char *indent_length ,
 	 char *start_line , char *end_line , char *null1 , 
	 char *null2 , int original_line_count ) {

// cazurile speciale ale lui paragrafe :
   int startline ;
   int endline ;
   int count ;
   int i , j ;

   if( (*null1 != ',') || (*null2 != ',') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }
   if( numar_natural (indent_length) == 0 ) {
	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	count = din_sir_in_numar ( indent_length ) ;
   }
// ne asiguram ca nu avem white-space-uri :
   for ( i = 0 ; i <= original_line_count ; i++ ) {
	no_whitespace ( original [ i ] ) ;
   }

// paragrafe propriu-zis :
   for( i = startline ; i <= endline ; i++ ) {
// daca e primul paragraf ( nu are \n deasupra lui ) :
   	if( i == 0 && strlen( original [ i ] ) > 1 ) {
	
	  for( j = strlen ( original [ i ] ) + count ; j >= count ; j-- ) {
		original [ i ] [ j ] = original [ i ] [ j - count ] ;
	  }
 	  for( j = 0 ; j < count ; j++ ) {
		original [ i ] [ j ] = ' ' ;
	  }
	}
// daca e paragraf nou :
	if( strlen( original [ i ] ) > 1 && strlen( original [ i-1 ] ) <= 1 ) {

	  for( j = strlen ( original [ i ] ) + count ; j >= count ; j-- ) {
		original [ i ] [ j ] = original [ i ] [ j - count ] ;
	  }
 	  for( j = 0 ; j < count ; j++ ) {
		original [ i ] [ j ] = ' ' ;
	  }
        }	     
   }
return 0 ;
}




			// FUNCTIA LISTS

int lists ( char original[1000][1000] , char *list_type ,
 	 char *special_character , char *start_line , char *end_line ,
	 char *null1 , int original_line_count ) {

// cazurile speciale ale lui lists :
   int startline ;
   int endline ;

// verificam daca e ceva in neregula cu parametrii start si end :
   if( *null1 != ',' ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }

// verificam daca e in regula list_type-ul :
   if( (*list_type != 'n') && (*list_type != 'b') &&
       (*list_type != 'a') && (*list_type != 'A') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
// verificam daca avem un caracter special :
   if( *special_character == ',' ) {
 	printf("Invalid operation!\n") ;
	return 1 ; 
   }

   char matrix [ 1000 ] [ 1000 ] ;
   int j = 0 ;
   int i ;
   int z = 49 ;
   char k = 49 ;
// in matrix vom pune listele, mai intai modul de ordonare :
   if( *list_type == 'n' ) {
// un algoritm pt numerotarea corecta pana la cel mult 100 :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = z ;
	    matrix [ i ] [ j ] = k ;
	    k++ ;
	    if( k == 58 && j == 0 ) {
		j++ ;
		k = 48 ;
	    }
	    if( k == 58 && j > 0 ) {
		z++ ;
		k = 48 ;
	    }
        }
   } 

   k = 65 ;
   if( *list_type == 'A' ) {
// un algoritm pt numerotarea corecta de la A la Z :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = k ;
	    k++ ;
        }
   }

   k = 97 ;
   if( *list_type == 'a' ) {
// un algoritm pt numerotarea corecta de la a la z :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = k ;
	    k++ ;
        }
   }
// facem un asign_left pe intervalul cerut :
    align_left( original , start_line, end_line , "," , "," , "," ,
    original_line_count ) ;
// punem caracterul special :
    for( i = 0 ; i <= endline-startline ; i++ ) {
	    strcat( matrix [ i ] , special_character ) ;
	    strcat( matrix [ i ] , " " ) ;
    }
// peste matrix punem matricea originala si apoi o trimitem inapoi :
    j = 0 ;
    for( i = startline ; i <= endline ; i++) {
	    strcat( matrix [ j ] , original [ i ] ) ;
	    j++ ;
    }
    j = 0 ;
    for( i = startline ; i <= endline ; i++) {
	    strcpy( original [ i ] , matrix [ j ] ) ;
	    strcpy( matrix [ j ] , " " ) ;
	    j++ ;
    }
// verifica daca are white-spaceuri :   
    for( i = 0 ; i <= original_line_count ; i++) {
	    no_whitespace( original [ i ] ) ;
    }

return 0 ;
}

			


			// FUNCTIA ORDERED_LISTS

int ordered_lists ( char original[1000][1000] , char *list_type ,
 	 char *special_character ,char *ordering , char *start_line ,
	 char *end_line , int original_line_count ) {
// in principiu este la fel ca "LISTS" pana la linia 750.
// cazurile speciale ale lui ordered_lists :
   int startline ;
   int endline ;

// verificam daca e ceva in neregula cu parametrii start si end :
   if( *start_line == ',' ) {
	startline = 0 ;
   }
   else  if( numar_natural (start_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	startline = din_sir_in_numar ( start_line ) ;
   }
   if( *end_line == ',' ) {
	endline = original_line_count - 1 ;
   }
   else  if( numar_natural (end_line) == 0 ) {
    	printf("Invalid operation!\n") ;
	return 1 ;
   }
   else {
	endline = din_sir_in_numar ( end_line ) ;
   }
   if( startline > endline ) {
	printf("Invalid operation!\n");
	return 1 ; 
   }
   if( startline > original_line_count ) {
	return 0 ; 
   }
   if( endline > original_line_count ) {
	endline = original_line_count - 1 ; 
   }

// verificam daca e in regula list_type-ul :
   if( (*list_type != 'n') && (*list_type != 'b') &&
       (*list_type != 'a') && (*list_type != 'A') ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }
// verificam daca avem caracter special :
   if( *special_character == ',' ) {
 	printf("Invalid operation!\n") ;
	return 1 ; 
   }
// verificam daca tipul de sortare este a sau z :
   if( *ordering != 'a' && *ordering != 'z' ) {
   	printf("Invalid operation!\n") ;
	return 1 ; 
   }

   char matrix [ 1000 ] [ 1000 ] ;
   int j = 0 ;
   int i , y ;
   int z = 49 ;
   char k = 49 ;
   int cmp ;
   char buffer [ 1000 ] ;
// in matrix vom pune listele, mai intai modul de ordonare :
   if( *list_type == 'n' ) {
// un algoritm pt numerotarea corecta pana la cel mult 100 :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = z ;
	    matrix [ i ] [ j ] = k ;
	    k++ ;
	    if( k == 58 && j == 0 ) {
		j++ ;
		k = 48 ;
	    }
	    if( k == 58 && j > 0 ) {
		z++ ;
		k = 48 ;
	    }
        }
   } 

   k = 65 ;
   if( *list_type == 'A' ) {
// un algoritm pt numerotarea corecta de la A la Z :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = k ;
	    k++ ;
        }
   }

   k = 97 ;
   if( *list_type == 'a' ) {
// un algoritm pt numerotarea corecta de la a la z :
	for( i = 0 ; i <= endline-startline ; i++ ) {
	    matrix [ i ] [ 0 ] = k ;
	    k++ ;
        }
   }

// punem caracterul special :
    for( i = 0 ; i <= endline-startline ; i++ ) {
	    strcat( matrix [ i ] , special_character ) ;
	    strcat( matrix [ i ] , " " ) ;
    }
// apoi sortam liniile respective intre ele :
    if( *ordering == 'a' ) {
	for( i = startline ; i < endline ; i++ ) {
      	    for(  y = i + 1 ; y <= endline ; y++ ) {
		   cmp = strcmp( original [ i ] , original [ y ] ) ; 
         	   if( cmp > 0 ) {
		   	  strcpy( buffer , original [ i ] ) ;
            	    	  strcpy( original [ i ] , original [ y ] ) ;
            	    	  strcpy( original [ y ] , buffer ) ;
		   }
             }
	}
    }
    if( *ordering == 'z' ) {
	 for( i = startline ; i < endline ; i++ ) {
      	    for( y = i + 1 ; y <= endline ; y++ ) {
		  cmp = strcmp( original [ i ] , original [ y ] ) ;
         	  if( cmp < 0 ) {
		   	  strcpy( buffer , original [ i ] ) ;
            	    	  strcpy( original [ i ] , original [ y ] ) ;
            	    	  strcpy( original [ y ] , buffer ) ;
		  }
	    }
	 }
    }
// facem un asign_left pe intervalul cerut :
    align_left( original , start_line, end_line , "," , "," , "," ,
    original_line_count ) ;
// peste matrix punem matricea originala si apoi o trimitem inapoi :
    j = 0 ;
    for( i = startline ; i <= endline ; i++) {
	    strcat( matrix [ j ] , original [ i ] ) ;
	    j++ ;
    }
    j = 0 ;
    for( i = startline ; i <= endline ; i++) {
	    strcpy( original [ i ] , matrix [ j ] ) ;
	    strcpy( matrix [ j ] , " " ) ;
	    j++ ;
    }
// verifica daca are white-spaceuri :   
    for( i = 0 ; i <= original_line_count ; i++) {
	    no_whitespace( original [ i ] ) ;
    }

return 0 ;
}






			// FUNCTIA MAIN

int main( int argc , char *argv [ ] ) {

			// DECLARARI :
  char buff [ 1000 ] ;
  char original [ 1000 ] [ 1000 ] ;
  char original_backup [ 1000 ] [ 1000 ] ;
  char rezultat [ 1000 ] [ 1000 ] ;
  char *Tokkens ;
  char *sir_comenzi [ 10 ] ;
  char *sir_comanda [ 6 ] ;
  int i , j ;
  int nr_operatii = 0 ;
  int caractere = 0 ;
  int original_line_count = 0 ;
  int original_line_count_backup ;
  int result_line_count = 0 ;
  int invalid = 0 ;




// in caz ca nr de argumente nu este corect :
  if ( argc != 4 ) {  
    fprintf ( stderr ,
	      "Usage: %s operations_string input_file output_file\n",
              argv [ 0 ] ) ;
  return -1 ;
  }



			// INPUT FILE :
			
// deschidem fisierul txt primit ca input :
  FILE *input_file = fopen ( argv [ 2 ] , "r" ) ;
// in caz ca fisierul nu exista :
  if ( input_file == NULL ) {
    fprintf( stderr , "File \"%s\" not found\n" , argv [ 2 ] ) ;
  return -2 ;
  }
  
// punem in matricea "original" textul din fisierul input :
  while ( fgets( buff , 1000 , input_file) ) {
    strcpy( original [ original_line_count ] , buff) ;
    strcpy( original_backup [ original_line_count ] , buff) ;
    original_line_count++ ;
  }
  fclose(input_file) ;
    original_line_count_backup = original_line_count ;



  			// O PARTE DIN CAZURILE SPECIALE :

// daca avem mai mult de 10 operatii :
  for( i = 0 ; i < strlen ( argv [ 1 ] ) ; i++ ) {
    caractere++ ;
    if( (argv [ 1 ] [ i ] == ',') || (i == strlen ( argv [ 1 ] ) - 1) ) {
	nr_operatii++;
// daca o operatie are mai mult de 20 de caractere :
        if( caractere >= 21 ) {
	    argv [ 1 ] [ i-caractere + 1 ] = 'X' ;
// acum operatia respectiva va fi 'X' ce este o litera invalida.
        }
        caractere = 0 ;
    }
    if( (nr_operatii == 10) && ( i <= strlen ( argv [ 1 ] ) - 1) ) {
	printf( "Too many operations! Only the first 10 will be applied.\n" ) ;
	break ;
    } 
  }
// impartim operatiile intre ele :
  Tokkens = strtok ( argv [ 1 ] , "," ) ;
  i = 0 ;
  while ( Tokkens != NULL ) {
     sir_comenzi [ i ] = Tokkens ; 
     Tokkens =  strtok ( NULL , "," ) ;
     i++ ;
  } 
// in caz ca nu avem argumente eliminam spatiile finale :
   for( i = 0 ; i<= original_line_count ; i++ ) {
	no_whitespace ( original [ i ] ) ;
   }


			// APLICAREA ARGUMENTELOR :

// pentru fiecare operatie in parte, luam fiecare parametru :
  for ( i = 0 ; i < nr_operatii ; i++ ) {
    j = 0 ;
// mai intai punem pe fiecare pozitie a lui sir_comanda o , ce inseamna NULL :
    while ( j < 6 ) {
	sir_comanda [ j ] = "," ; 
	j++ ; }
// despartim parametrii intre ei : 
    Tokkens = strtok ( sir_comenzi [ i ] , " " ) ;
    j = 0 ;
    while ( Tokkens != NULL ) {
// in caz ca sunt declarati mai mult de 6 parametrii ( maximul ) :
	if ( j == 6 ) {
// din nou, denumim operatia "," pentru a fi considerata invalida.
	  sir_comanda [ 0 ] = "," ;
	  Tokkens =  strtok ( NULL , " " ) ;
          break;
	}
	sir_comanda [ j ] = Tokkens ; 
    	Tokkens =  strtok ( NULL , " " ) ;
    	j++ ;
     } 
    switch( *sir_comanda [ 0 ] ) {

        case 'w': 
	    *sir_comanda[0]='W'; 
   	case 'W':
            original_line_count = wrap( original , sir_comanda [ 1 ] , 
		sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
            break;

	case 'c':
	    *sir_comanda[0]='C';
   	case 'C':
      	    invalid = center( original , sir_comanda [ 1 ] ,
		sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
     	    break;

	case 'l': 
	    *sir_comanda[0]='L'; 
   	case 'L':
            invalid = align_left( original , sir_comanda [ 1 ] ,
		 sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
            break;

	case 'r': 
	    *sir_comanda[0]='R'; 
   	case 'R':
            invalid = align_right( original , sir_comanda [ 1 ] ,
		sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
            break;

	case 'j':
	    *sir_comanda[0]='J';
   	case 'J':
      	    invalid = justify( original , sir_comanda [ 1 ] ,
		sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
     	    break;

	case 'p': 
	    *sir_comanda[0]='P'; 
   	case 'P':
      	    invalid = paragrafe( original , sir_comanda [ 1 ] ,
		sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
            break;

	case 'i': 
	    *sir_comanda[0]='I'; 
   	case 'I':
             invalid = lists( original , sir_comanda [ 1 ] ,
		 sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
            break;

	case 'o':
	    *sir_comanda[0]='O';
   	case 'O':
             invalid = ordered_lists( original , sir_comanda [ 1 ] ,
		 sir_comanda [ 2 ] , sir_comanda [ 3 ] , sir_comanda [ 4 ] ,
		sir_comanda [ 5 ] , original_line_count ) ;
     	    break;

  	default:
            printf("Invalid operation!\n");
	    invalid = 1 ;
            break;
    }
// daca o operatie a fost Invalida, fisierul va deveni cel initial :
  	if ( invalid == 1 || original_line_count == -1 ) {
          original_line_count = original_line_count_backup ;
	     for( i = 0 ; i <= original_line_count ; i++ ) {
    		strcpy( original [ i ] , original_backup [ i ] ) ;
  	     }
          goto Save ;
        }

  } 

Save:
// salvam matricea "original" in cea "rezultat"
  for( i = 0 ; i <= original_line_count ; i++ ) {
    strcpy( rezultat [ i ] , original [ i ] ) ;
  }
  result_line_count = original_line_count ;


		// OUTPUT FILE :

// deschidem fisierul txt primit ca output :
  FILE *output_file = fopen( argv [ 3 ] , "w" ) ;
// in caz ca fisierul nu exista :
  if (output_file == NULL) {
    fprintf ( stderr , "Could not open or create file \"%s\"\n" , argv [ 3 ] ) ;
   return -2 ;
  }

// intregram matricea "rezultat" in fisierul output :
  for( i = 0 ; i <= result_line_count ; i++ ) {
    fputs( rezultat [ i ] , output_file ) ;
  }

  fclose(output_file) ;
  return 0 ;
}
