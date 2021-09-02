
#ifndef TEAM_EXTRACTOR_H_D
#define TEAM_EXTRACTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FootballClub.h"


Player *union_teams(FootballClub *clubs, char *club_A, char *club_B) {
  if(clubs == NULL || club_A == NULL || club_B == NULL )
    return NULL ;
  FootballClub *ClubA, *ClubB ;
  Player *Lista = NULL , *buffer ;
  ClubB = ClubA = clubs ;
  while(ClubA != NULL ) {
    if( strcmp(ClubA->name, club_A) == 0 )
      break ;
    ClubA = ClubA->next ;
  }
  while(ClubB != NULL ) {
    if( strcmp(ClubB->name, club_B) == 0 )
      break ;
    ClubB = ClubB->next ;
  }
  if( ClubB == NULL || ClubA == NULL )
    return NULL ;
  // adauga toti jucatorii din clubul A :
  buffer = ClubA->players ;
  while( buffer != NULL ) {
    Lista = add_player_in_list2 ( Lista , buffer ) ;
    buffer = buffer->next ;
  }
  buffer = ClubB->players ;
  while( buffer != NULL ) {
    Lista = add_player_in_list2 ( Lista , buffer ) ;
    buffer = buffer->next ;
  }
  return Lista ;
  
}



Player *get_best_player(FootballClub *clubs, char *position) {
  if( clubs == NULL || position == NULL )
    return NULL ;
  FootballClub *buffer1 ;
  Player *buffer2, *buffer3 , *Best = NULL ;
  buffer1 = clubs ;
  while( buffer1 != NULL ) {
    buffer2 = buffer1->players ;
    while(buffer2 != NULL ) {
      if( strcmp ( position , buffer2->position ) == 0 )
	Best = add_player_in_list ( Best , buffer2 ) ;
      buffer2 = buffer2->next ;
    }
    buffer2 = NULL ;
    buffer1 = buffer1->next ;
  }
// avem o lista cu cel mai buni jucatori dar dezalocam
// deoarece ne intereseaza doar primul :
  buffer2 = Best->next ;
  while( buffer2!= NULL ) {
    buffer3 = buffer2 ;
    buffer2 = buffer3->next ;
    free(buffer3) ;
  }
  Best->next = NULL ;
  return Best ;
}



Player *get_top_players(FootballClub *clubs, int N) {
  if( clubs == NULL || N == 0 )
    return NULL ;
  FootballClub *buffer1 = clubs ;
  Player *buffer2, *buffer3, *Max , *Lista = NULL ;

  while(buffer1 != NULL ) {
    buffer2 = buffer1->players ;
    Max = NULL ;
    int max_score = -101 ;
    char *MaxName = "Z" ;
    int count = 0 ;
  // prima tura :
    while(buffer2 != NULL ) {
      if( buffer2->score > max_score || 
 (buffer2->score == max_score && strcmp(buffer2->name, MaxName ) < 0)){
	max_score = buffer2->score ;
        MaxName = buffer2->name ;
        Max = buffer2 ;
      }
      count++ ;
      buffer2 = buffer2->next ;
    }
    Lista = add_player_in_list( Lista , Max ) ;
  // in caz ca avem prea putini jucatori :
    if( count < N ) {
      buffer2 = buffer1->players ;
      while(buffer2 != NULL ) {
        if(buffer2 != Max ) 
         Lista = add_player_in_list( Lista , buffer2 ) ;
        buffer2 = buffer2->next ;
      }
    }
  // in caz ca avem mai mult jucatori decat ne este cerut :
    else {
      count = 0 ;
      Retry:
      buffer2 = buffer1->players ;
  // intai cautam elemente cu aceeasi valoare ca maximul :
      while(buffer2 != NULL ) {
        if( buffer2->score >= max_score && buffer2 != Max ) {
  // cautam dupa un jucator cu acelasi scor dar nume mai mic din punct de
  // vedere alfabetic
          buffer3 = buffer2->next ;
          while(buffer3 != NULL ) {
            if( strcmp( buffer3->name, buffer2->name ) < 0 && 
            buffer3->score >= buffer2->score && buffer3 != Max)
              buffer2 = buffer3 ;
            buffer3 = buffer3->next ;
          }
        Lista = add_player_in_list( Lista , buffer2 ) ;
        count++ ;
        }
  // in caz de am atins numarul dorit oprim totul :
        if(count == N - 1)
          break ;
        buffer2 = buffer2->next ;
      }
  // in caz de nu, cautam, plecand descrescator de la scorul maxim,
 // un al doilea cel mai mare element si tot asa, apeland functia goto
 // pentru a ne reintoarce mai sus :
      if( count < N - 1) {
        max_score-- ;
        goto Retry ;
      }
    }
    Max = NULL ;
    buffer2 = NULL ;
    buffer1 = buffer1->next ;
  }
  return Lista ;
        
}



Player *get_players_by_score(FootballClub *clubs, int score) {
  if(clubs == NULL || score < -100 || score > 100)
    return NULL ;
  FootballClub *buffer1 ;
  Player *Lista = NULL , *buffer2 ;
  buffer1 = clubs ;
  while( buffer1 != NULL ) {
    buffer2 = buffer1->players ;
    while( buffer2 != NULL ) {
      if( buffer2->score >= score ) 
         Lista = add_player_in_list( Lista , buffer2 ) ;
      buffer2 = buffer2->next ;
    }
    buffer2 = buffer1->injured_players ;
    while( buffer2 != NULL ) {
      if( buffer2->score >= score ) 
       Lista = add_player_in_list( Lista , buffer2 ) ;
      buffer2 = buffer2->next ;
    }
    buffer2 = NULL ;
    buffer1 = buffer1->next ;
  }
  return Lista ;
}



Player *get_players_by_position(FootballClub *clubs, char *position) {
  if(clubs == NULL || position == NULL)
    return NULL ;
  FootballClub *buffer1 ;
  Player *Lista = NULL , *buffer2 ;
  buffer1 = clubs ;
  while( buffer1 != NULL ) {
    buffer2 = buffer1->players ;
    while( buffer2 != NULL ) {
      if( strcmp( position , buffer2->position) == 0 ) 
        Lista = add_player_in_list( Lista , buffer2 ) ;
      buffer2 = buffer2->next ;
    }
    buffer2 = buffer1->injured_players ;
    while( buffer2 != NULL ) {
      if( strcmp( position , buffer2->position) == 0 )  
        Lista = add_player_in_list( Lista , buffer2 ) ;
      buffer2 = buffer2->next ;
    }
    buffer1 = buffer1->next ;
  }
  return Lista ;
}



Player *get_best_team(FootballClub *clubs) {
  if( clubs == NULL )
    return NULL ;
  Player *buffer ;
  Player *Lista = NULL ;
  Player *ListaAtac = NULL ;
  Player *ListaMijloc = NULL ;
  Player *ListaFundas = NULL ;
  Player *ListaPortar = NULL ;

  ListaPortar = get_players_by_position(clubs , "portar") ;
  ListaAtac = get_players_by_position( clubs , "atacant" ) ;
  ListaMijloc = get_players_by_position( clubs , "mijlocas" ) ;
  ListaFundas = get_players_by_position( clubs , "fundas" ) ;
  int i = 0 ;
  // introducem in lista noastra cati jucatori ne sunt ceruti :
  buffer = ListaPortar ;
  Lista = add_player_in_list( Lista, buffer ) ; 
  buffer = ListaAtac ;
  for( i = 0 ; i < 3 ; i++ ) {
    if(buffer != NULL) {
      Lista = add_player_in_list( Lista , buffer ) ;
      buffer = buffer->next ;
    }
  }
  buffer = ListaMijloc ;
  for( i = 0 ; i < 3 ; i++ ) {
    if(buffer != NULL) {
      Lista = add_player_in_list( Lista , buffer ) ;
      buffer = buffer->next ;
    }
  }
  buffer = ListaFundas ;
  for( i = 0 ; i < 4 ; i++ ) {
    if(buffer != NULL) {
      Lista = add_player_in_list( Lista , buffer ) ;
      buffer = buffer->next ;
    }
  }
  // apoi dezalocam ListaAtac / Mijloc/ Fundas/ Portar :
  while( ListaAtac != NULL ) {
    buffer = ListaAtac ;
    ListaAtac = ListaAtac->next ;
    free(buffer) ;
  }
  while( ListaMijloc != NULL ) {
    buffer = ListaMijloc ;
    ListaMijloc = ListaMijloc->next ;
    free(buffer) ;
  }
  while( ListaFundas != NULL ) {
    buffer = ListaFundas ;
    ListaFundas = ListaFundas->next ;
    free(buffer) ;
  }
  while( ListaPortar != NULL ) {
    buffer = ListaPortar ;
    ListaPortar = ListaPortar->next ;
    free(buffer) ;
  }
  return Lista ;
}

#endif // TEAM_EXTRACTOR_H_INCLUDED
