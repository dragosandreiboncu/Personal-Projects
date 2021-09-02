#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {

			// DECLARARI :

unsigned long long codharta ;
int nrpiese ;
long long piese [ 800 ] ; // vectorul ce va retine piesele + mutarile lor.	
int zerouri = 0 , liniicomplete = 0 ; 
float scor ;

			/* DECLARARI FOLOSITE LA " FOR-URI " SAU " IF-URI " :
			         ( mai putin importante ) */ 

unsigned long long codharta2 ; // variabila in care vom salva harta.
int bit64 ; // o variabila care se misca pe cei 64 de biti.
int bit ; // o alta variabila in care vom pune pe rand bitii de 1 sau 0.
int mutare , mutare2 , mutare3 ; // variabile folosite pentru "for-uri".
int nivel ; // variabila folosita pentru a numara cele 8 nivele ale tabloului.
unsigned long long o_unitate = 1 ; // un tablou secundar cu 1 piesa.
unsigned long long liniefull = 255 ; // un tablou secundar cu 1 linie completa.
int linii = 0 ; // cand e dif de 0, se va afisa harta dupa eliminarea liniilor. 
int nrde1 = 0 ; // cand va deveni 8 inseamna ca avem o linie completa.
int tabloucomplet = 0 ; // va deveni 1 daca piese nu mai are loc in intregime.





			// HARTA INITIALA :



scanf ( "%lld", & codharta ) ;
	
scanf ( "%d", & nrpiese ) ;
	
for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- ) {	
  bit = codharta >> bit64  ; 
  if ( bit & 1 ) {
	printf ( "#" ) ;
  }
  else {
	printf ( "." ) ; 
  }
  if ( bit64 % 8 == 0 ) {
	printf ( "\n" ) ;
  }
}



			// DECLARAREA PIESELOR + MUTARILOR :
	
for ( mutare = 0 ; mutare < nrpiese; mutare ++ ) {

  scanf ( "%lld" , & piese [ mutare * 9 ] ) ; 
  scanf ( "%lld" , & piese [ mutare * 9 + 1 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 2 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 3 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 4 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 5 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 6 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 7 ] ) ;
  scanf ( "%lld" , & piese [ mutare * 9 + 8 ] ) ;

			// CELE 8 IPOSTAZE ALE PIESEI :

  for ( nivel = 8 ; nivel >= 0 ; nivel -- ) {

	// in caz ca piesa nu mai are loc in intregime:
	if ( ( piese [ mutare * 9 ] << 56 ) & codharta ) {
	  goto Tablou_Full ;
	}
  	
	// algoritmul pentru miscarea piesei de sus in jos:	
	codharta2 = codharta + ( piese [ mutare * 9 ] << ( 8 * nivel ) ) ;

	// afisarea hartii incepand de la nivelul 7, 8 fiind inafara hartii:
	if ( nivel<=7 )	{			
	  for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- ) {
		bit = codharta2 >> bit64  ;
		if ( bit & 1) 
		{ printf ( "#" ) ; }
		else
		{ printf ( "." ) ;  } 
		if ( bit64 % 8 == 0 ) 
		{ printf ( "\n" ) ; }

	  } 
	}
	
	printf( "\n" ) ; 
	
			// COLIZIUNILE :

	if (( ( piese[mutare*9] << ( 8*( nivel-1) )) & codharta ) !=0 ) {

	
	Tablou_Full:
	// in caz ca piesa se intinde pe 2 linii si nu are loc pe tot tabloul:
	  if ( (piese[mutare*9] & (piese [ mutare * 9 ] << 8))
	     && (codharta & ( piese[mutare*9] << 48)) )  {
		codharta=codharta2 ;
		tabloucomplet=1 ;
		goto Gameover ;
	  }	
	// in caz ca piesa se intinde doar pe o linie:		
	  else if ( codharta & (piese [mutare*9] << 56) ) {
		codharta=codharta2 ;
		tabloucomplet=1;
		goto Gameover ;
	  }
	// in caz ca are loc, verificam daca avem linii complete:				 
	  else { 
		goto Linii;
	  }
	}
			
			// MUTARILE LA STANGA SI LA DREAPTA :

	for( mutare2=1 ; mutare2<=8 ; mutare2++ ) {
	for( mutare3=1 ; mutare3<=abs( piese[mutare*9+mutare2] ) ; mutare3++) {
	// in cazul mutarilor la dreapta:
	  if ( ( piese [ mutare * 9 + mutare2 ] > 0 ) && ( nivel == 9 - mutare2 ) ) {
		if ( nivel > 1 ) {
	       if (( (( piese[mutare*9] << ( 8*(nivel-1)-1 )) & codharta) == 0) 
	    && (( (( piese[mutare*9] << 8) >> 1) & (128 + (128 << 8))) == 0)) {
		  piese [ mutare * 9 ] = piese [ mutare * 9 ] >> 1 ;
		}
		}
	/* la nivelul 1 a intervenit o problema asa ca l-am luat separat:
		( 8 * ( nivel - 1 ) devenea numar negativ */
		if ( nivel ==1 ) {
	       if (( (( piese[mutare*9] >> 1) & codharta ) == 0) 
	    && (( (( piese[mutare*9] << 8) >> 1) & (128 + (128 << 8))) == 0)) {
		  piese [ mutare * 9 ] = piese [ mutare * 9 ] >> 1;
		}                      
		}
	  }
	// in cazul mutarilor la stanga:
	  else if ( (piese[mutare*9 + mutare2] < 0) && (nivel == 9-mutare2) ) {
	       if (( (( piese[mutare*9] << (1 + 8*(nivel-1))) & codharta) == 0)
	    && ( (( piese[mutare*9] << 1 ) & (256 + (256 << 8)) ) == 0) ) {
		  piese [ mutare * 9 ] = piese [ mutare * 9 ] << 1 ;
	 	}
	  }
	}
	}
									
  }  
  
  Linii: 		// LINIILE COMPLETE SI ELIMINAREA LOR :

  codharta = codharta2 ;	
  for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- ) {                               
	if ( codharta & ( o_unitate << bit64 ) ) {
	  nrde1++ ;
	}
	if ( (bit64 % 8 == 0 ) && ( nrde1 != 8 ) ) {
	  nrde1 = 0 ;
	}
	else if ( ( bit64 % 8 ==0 ) && ( nrde1 ==8 ) ) {
	  linii++ ;
	  nrde1 = 0 ; 
	  codharta = ( codharta - ( liniefull << ( 8 * ( bit64 / 8 ) )  ) ) ;
	  for ( bit = bit64 ; bit<=63 ; bit++ ) {
		if ( codharta & (o_unitate<<bit) ) {
		  codharta = codharta - ( o_unitate << bit ) ;
		  codharta = codharta + ( o_unitate << ( bit-8 ) ) ; 
		}
	  }
	}
  }

  liniicomplete = liniicomplete + linii ;
  if ( linii ) {						 
	for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- ) {
	  bit = codharta >> bit64  ;
	  if ( bit & 1) {
		printf ( "#" ) ;
	  }
	  else {
		printf ( "." ) ;
	  }
	  if ( bit64 % 8 == 0 ) {
		printf ( "\n" ) ;
	  }
	} 
  }
  linii = 0 ; 
}




			// SCORUL :

// in caz ca piesa nu mai are loc pe tablou, afisam imaginea din nou:
Gameover :
if ( tabloucomplet  ) {
  for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- ) {
	bit = codharta >> bit64  ;
	if ( bit & 1) {
	  printf ( "#" ) ;
	}
	else {
	  printf ( "." ) ;
	}
	if ( bit64 % 8 == 0 ) {
	  printf ( "\n" ) ;
	}
  } 
  printf( "\n" ) ;
}

// acum vom numara zerourile de pe harta finala:
for ( bit64 = 63 ; bit64 >= 0 ; bit64 -- )  {
  bit = codharta >> bit64  ;
  if ( ( bit & 1 ) == 0 ) {
	zerouri++ ;
  } 
} 
	
scor = sqrt(zerouri) + pow ( 1.25 , liniicomplete ) ;

printf( "GAME OVER! \nScore:" ) ; 
printf( "%.2f " , scor ) ;
printf( "\n" ) ;

return 0 ; 

}
