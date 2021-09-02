#ifndef FOOTBALL_CLUB_H_D
#define FOOTBALL_CLUB_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// List node which contains information about one football player.
typedef struct Player {
	char *name;					// player's name
	char *position;				// player's game position
	int score;					// player's score
	int injured;				// indicator for injury (1 true, 0 false)
	struct Player *next;		// next list node
	struct Player *prev;		// previous list node
} Player;

// Structure which contains information about one football club.
typedef struct FootballClub {
	char *name;					// club's name
	Player *players;			// list with players in good shape
	Player *injured_players;	// list with injured players
	struct FootballClub *next;	// next list node
} FootballClub;


FootballClub *initialize_clubs(int clubs_no, char **names) {
  if(clubs_no <= 0 )
    return NULL ;
  FootballClub **Echipe ;
  Echipe = (FootballClub**)malloc(sizeof(FootballClub*)*clubs_no) ;
  int i ;
  for(i = 0 ; i < clubs_no ; i++ ) {
    Echipe[i] = (FootballClub*)malloc(sizeof(FootballClub)) ;
    if( Echipe[i] == NULL )
      return NULL ;
    Echipe[i]->name = names[i] ;
    Echipe[i]->players = Echipe[i]->injured_players = NULL ;
  }
  for(i = 0 ; i < clubs_no - 1 ; i++ ) {
    Echipe[i]->next = Echipe[i+1] ;
  }
  Echipe[clubs_no-1]->next = NULL ;
  return Echipe[0] ;
}



FootballClub *add_club(FootballClub *clubs, char *name) {
  FootballClub *NewClub ;
  NewClub = (FootballClub*) malloc ( sizeof(FootballClub)) ;
  if(NewClub == NULL )
    return NULL ;
  NewClub->name = name ;
  NewClub->players = NULL ;
  NewClub->injured_players = NULL ;
  NewClub->next = NULL ;

  if( clubs == NULL ) {
    clubs = NewClub ;
    return clubs ;
  }
  FootballClub *current_node ;
  current_node = clubs ;
  while ( current_node->next != NULL ) {
    current_node = current_node->next ;
  }
  current_node->next = NewClub ;
  return clubs ;
}



void add_player(FootballClub *clubs, char *club_name, 
				char *player_name, char *position, int score) {

  if( clubs == NULL || club_name == NULL || player_name == NULL ||
      position == NULL ) 
    return ;
  // cautam clubul :
  FootballClub *buffer ;
  buffer = clubs ;
  while( buffer != NULL ) {
    if( strcmp(buffer->name , club_name ) == 0 )
      break ;
    buffer = buffer->next ;
  }
  // daca nu gasim clubul respectiv :
  if( buffer == NULL ) 
    return ;
  // alocam o casuta jucatorului :
  Player *player ;
  player = (Player*) malloc ( sizeof(Player) ) ;
  if( player == NULL )
    return ;
  player->name = player_name ;					
  player->position = position ;
  if( score > 100 || score < -100 ) {
    return ;
  }				
  player->score = score ;
  player->injured = 0 ;
  player->next = player->prev = NULL ;						
  // cautam pozitia jucatorului in lista
  Player *buffer2, *buffer3 ;
  // in cazul in care lista e goala :
  if( buffer->players == NULL ) {
    buffer->players = player ;
    return ;
  }
  buffer2 = buffer->players ;
  int PosDif = 0 ;
  int NameDif = 0 ;
  // altfel cautam pozitia dupa cele 3 criterii :
  while(buffer2 != NULL) {
    PosDif = strcmp(buffer2->position , player->position) ;
    NameDif = strcmp(buffer2->name, player->name) ;
    if( (PosDif > 0)  || (PosDif == 0 && buffer2->score < player->score) ||
 (PosDif == 0 && NameDif > 0 && buffer2->score == player->score) ) {
      player->prev = buffer2->prev ;
      buffer2->prev = player ;
      if( player->prev != NULL )
        player->prev->next = player ;
      else
        buffer->players = player ;
      player->next = buffer2 ;
      return ;
      
    }
    buffer3 = buffer2 ;
    buffer2 = buffer2->next ;
  }
  // in cazul in care este pe ultima pozitie :
  buffer3->next = player ;
  player->prev = buffer3 ;
  return ;

}



void transfer_player(FootballClub *clubs, char *player_name, 
					char *old_club, char *new_club) {

  if( clubs == NULL || player_name == NULL ||
     old_club == NULL || new_club == NULL ) 
    return ;

  FootballClub *newc, *oldc ;
  newc = oldc = clubs ;
  while( newc != NULL ) {
    if( strcmp( newc->name , new_club ) == 0 ) 
      break ;
    newc = newc->next ;    
  }
  while( oldc != NULL ) {
    if( strcmp( oldc->name , old_club) == 0 ) 
      break ;
    oldc = oldc->next ;    
  }
  if( newc == NULL || oldc == NULL )
    return ;
  Player *player ;
  player = oldc->players ;
  while( player != NULL ) {
    if( strcmp (player->name , player_name) == 0 ) 
      break ;
    player = player->next ;    
  }
// in caz ca nu este neaccidentat il cautam la accidentati :
  if( player == NULL ) {
    player = oldc->injured_players ;
    while( player != NULL) {
      if( strcmp (player->name , player_name) == 0 ) 
        break ;
      player = player->next ;    
    }
    if( player == NULL )
      return ;
// adaugam jucatorul accidentat la new_club in categoria accidentati :
    else {
      if( newc->injured_players == NULL ) {
        if(player->prev != NULL )
          player->prev->next = player->next ;
        else 
          oldc->injured_players = player->next ;
        if(player->next != NULL )
          player->next->prev = player->prev ;
        newc->injured_players = player ;
        player->next = player->prev = NULL ;
        return ;
      }
      Player *buffer1 = newc->injured_players , *buffer2 ;
      int NameDif = 0 ;
  // altfel cautam pozitia dupa nume :
      while(buffer1 != NULL) {
        NameDif = strcmp(buffer1->name, player->name) ;
        if( NameDif > 0  ) {
          if(player->prev != NULL )
            player->prev->next = player->next ;
          else 
            oldc->injured_players = player->next ;
          if(player->next != NULL )
            player->next->prev = player->prev ;
          player->prev = buffer1->prev ;
          buffer1->prev = player ;
          if( player->prev != NULL )
            player->prev->next = player ;
          else
            newc->injured_players = player ;
          player->next = buffer1 ;
          return ;
      
       }
       buffer2 = buffer1 ;
       buffer1 = buffer1->next ;
     }
     buffer2->next = player ;
     player->prev = buffer2 ;
     return ;
    }
  }
  // altfel daca este la neaccidentati :
  else {
    add_player( clubs, newc->name , player->name, 
	player->position, player->score ) ;
    if(player->prev != NULL )
      player->prev->next = player->next ;
    else 
      oldc->players = player->next ;
    if(player->next != NULL )
      player->next->prev = player->prev ;
    free(player) ;
  }
}




void remove_player(FootballClub *clubs, char *club_name, char *player_name) {
  if( clubs == NULL || club_name == NULL || player_name == NULL )
    return ;
  FootballClub *club = clubs ;
  while( club != NULL ) {
    if( strcmp(club->name , club_name) == 0 ) 
      break ;
    club = club->next ;    
  }
  if( club == NULL )
    return ;
  Player *player = club->players ;
  while( player != NULL ) {
    if( strcmp(player->name , player_name) == 0 ) 
      break ;
    player = player->next ;    
  }
  if( player == NULL ) {
    player = club->injured_players ;
    while( player != NULL ) {
      if( strcmp(player->name , player_name) == 0 ) 
        break ;
      player = player->next ;    
    }
    if( player == NULL )
      return ;
    else {
      if (club->injured_players == player)  
        club->injured_players = player->next;  
      if (player->next != NULL)  
        player->next->prev = player->prev;  
      if (player->prev != NULL)  
        player->prev->next = player->next; 
      free(player) ;
      return ; 
    }
  }

  else {
    if (club->players == player)  
      club->players = player->next;  
    if (player->next != NULL)  
      player->next->prev = player->prev;  
    if (player->prev != NULL)  
      player->prev->next = player->next;  
  }
    free(player) ;  
    return ;  
}




void update_score(FootballClub *clubs, char *club_name, 
					char *player_name, int score) {

  if( clubs == NULL || club_name == NULL || player_name == NULL )
    return ;
  if( score > 100 || score < -100 ) 
    return ;
  FootballClub *club ;
  club = clubs ;
  while( club != NULL ) {
    if( strcmp(club->name , club_name) == 0 ) 
      break ;
    club = club->next ;
  }
  if( club == NULL )
    return ;
  Player *player ;
  player = club->players ;
  while( player != NULL ) {
    if( strcmp(player->name , player_name) == 0 ) 
      break ;
    player = player->next ;
  }
  if( player == NULL ) {
    player = club->injured_players ;
      while( player != NULL ) {
        if( strcmp(player->name , player_name) == 0 ) 
          break ;
        player = player->next ;
      }
    if( player == NULL )
      return ;
    else {
      player->score = score ;
      return ;
    }
    
  }
  else {
    char *position = player->position ;
    player = NULL ;
    remove_player( clubs, club_name, player_name) ;
    add_player(clubs, club_name, player_name, position, score) ;
  }
    
}



void update_game_position(FootballClub *clubs, char *club_name, 
							char *player_name, char *position, int score) {

  if( clubs == NULL || club_name == NULL || 
    player_name == NULL || position == NULL )
    return ;
  if( score > 100 || score < -100 ) 
    return ;
  FootballClub *club ;
  club = clubs ;
  while( club != NULL ) {
    if( strcmp(club->name , club_name) == 0 ) 
      break ;
    club = club->next ;
  }
  if( club == NULL )
    return ;
  Player *player ;
  player = club->players ;
  while( player != NULL ) {
    if( strcmp(player->name , player_name) == 0 ) 
      break ;
    player = player->next ;
  }
  if( player == NULL ) {
    player = club->injured_players ;
      while( player != NULL ) {
        if( strcmp(player->name , player_name) == 0) 
          break ;
        player = player->next ;
      }
    if( player == NULL )
      return ;
    else {
      player->score = score ;
      player->position = position ;
      return ;
    }
  }
  else {
    remove_player( clubs, club_name, player_name) ;
    add_player( clubs, club_name, player_name, position, score) ;
  }
    
}




void add_injury(FootballClub *clubs, char *club_name,
				char *player_name, int days_no) {
  if( clubs == NULL || club_name == NULL || player_name == NULL )
    return ;
  if( days_no < 0 ) 
    return ;
  FootballClub *club ;
  club = clubs ;
  while( club != NULL ) {
    if( strcmp(club->name , club_name) == 0 ) 
      break ;
    club = club->next ;
  }
  if( club == NULL )
    return ;
  Player *player, *player_injured ;
  player = club->players ;
  while( player != NULL ) {
    if( strcmp(player->name , player_name) == 0 ) 
      break ;
    player = player->next ;
  }
  if( player == NULL ) 
    return ;
  player_injured = (Player*)malloc(sizeof(Player)) ;
  if(player_injured == NULL )
    return ;
  player_injured->name = player->name ;
  player_injured->injured = 1 ;
  player_injured->position = player->position ;
  player_injured->score = player->score - 0.1 * days_no ;
  if( player_injured->score > 100 )
  player_injured->score = 100 ;
  if( player_injured->score < -100 )
  player_injured->score = -100 ;
  player_injured->next = player_injured->prev = NULL ;
  remove_player(clubs , club_name , player_name ) ;
  // adaugam noua casuta in lista injured_players :
  player = club->injured_players ;
  if(club->injured_players == NULL ) {
    club->injured_players = player_injured ;
    return ;
  }
  // in cazul in care pozitia jucatorului ar fi fix prima :
  if( strcmp(player->name, player_injured->name) > 0 ) {
    player_injured->next = player ;
    player->prev = player_injured ;
    club->injured_players = player_injured ;
    return ;
  }
  // altfel cautam pozitia dupa nume :
  while( player->next != NULL && strcmp(player->name, player_injured->name) <= 0 ) {
     player = player->next;
  }
  //dupa ce gaseste pozitia aplicam schimbarile :
  if( player != NULL ) {
    player_injured->next = player->next ;
    if( player_injured->next != NULL )
    player_injured->next->prev = player_injured ;
    player_injured->prev = player ;
    player->next = player_injured ;
    return ; 
  }
  
}




void recover_from_injury(FootballClub *clubs, char *club_name, 
							char *player_name) {
  if( clubs == NULL || club_name == NULL || player_name == NULL )
    return ;
  FootballClub *club ;
  club = clubs ;
  while( club != NULL ) {
    if( strcmp(club->name , club_name) == 0 ) 
      break ;
    club = club->next ;    
  }
  if( club == NULL )
    return ;
  Player *player ;
  player = club->injured_players ;
  while( player != NULL ) {
    if( strcmp(player->name , player_name) == 0 ) 
      break ;
    player = player->next ;    
  }
  if( player == NULL )
    return ;
  char *position = player->position ;
  int score = 0 ;
  score = player->score ;
  player = NULL ;
  remove_player( clubs, club_name , player_name ) ;
  add_player( clubs, club_name, player_name, position, score) ;
}



// Frees memory for a list of Player.
void destroy_player_list(Player *player) {
  Player *buffer ;
  while( player != NULL ) {
    buffer = player ;
    player = player->next ;
    free(buffer) ;
  }
}



// Frees memory for a list of FootballClub.
void destroy_club_list(FootballClub *clubs) {
  FootballClub *buffer ;
  while( clubs != NULL ) {
    buffer = clubs ;
    clubs = clubs->next ;
    destroy_player_list(buffer->players) ;
    destroy_player_list(buffer->injured_players) ;
    free(buffer) ;
  }
}



// Displays a list of players.
void show_list(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	while (player) {
		fprintf(f, "(%s, %s, %d, %c) ", 
			player->name,
			player->position,
			player->score,
			player->injured ? 'Y' : '_');
		player = player->next;
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}



// Displays a list of players in reverse.
void show_list_reverse(FILE *f, Player *players, int free_memory) {
	fprintf(f, "P: ");
	Player *player = players;
	if (player) {
		while (player->next) {
			player = player->next;
		}
		while (player) {
			fprintf(f, "(%s, %s, %d, %c) ", 
				player->name,
				player->position,
				player->score,
				player->injured ? 'Y' : '_');
			player = player->prev;
		}
	}
	if (free_memory) {
		destroy_player_list(players);
	}
	fprintf(f, "\n");
}



// Displays information about a football club.
void show_clubs_info(FILE *f, FootballClub *clubs) {
	fprintf(f, "FCs:\n");
	while (clubs) {
		fprintf(f, "%s\n", clubs->name);
		fprintf(f, "\t");
		show_list(f, clubs->players, 0);
		fprintf(f, "\t");
		show_list(f, clubs->injured_players, 0);
		clubs = clubs->next;
	}
}




  // functie folosita in TeamExtractor.h
Player *add_player_in_list( Player *list , Player *element ) {
  // functia face acelasi lucru ca si add_player doar ca elementele
  // vor fi sortate in functie de scor apoi de nume :
  if( element == NULL )
    return NULL ;
  Player *player ;
  player = (Player*) malloc ( sizeof(Player) ) ;
  if( player == NULL )
    return NULL ;
  player->name = element->name ;					
  player->position = element->position ;				
  player->score = element->score ;
  player->injured = element->injured ;
  player->next = player->prev = NULL ;
  if( list == NULL ) {
    list = player ;
    return list ;
  }
  Player *buffer1 , *buffer = list ;
  int NameDif = 0 ;
  // altfel cautam pozitia dupa cele 2 criterii :
  while(buffer != NULL) {
    NameDif = strcmp(buffer->name, player->name) ;
    if( (buffer->score < player->score) ||
     ( NameDif > 0 && buffer->score == player->score) ) {
      player->prev = buffer->prev ;
      buffer->prev = player ;
      if( player->prev != NULL )
        player->prev->next = player ;
      else
        list = player ;
      player->next = buffer ;
      return list ;
      
    }
    buffer1 = buffer ;
    buffer = buffer->next ;
  }
  buffer1->next = player ;
  player->prev = buffer1 ;
  return list ;
}




Player *add_player_in_list2( Player *list , Player *element ) {
  // functia face acelasi lucru ca si add_player doar ca primeste
  // ca si argumente doar o lista de jucatori nu un club intreg :
  if( element == NULL )
    return NULL ;
  Player *player ;
  player = (Player*) malloc ( sizeof(Player) ) ;
  if( player == NULL )
    return NULL ;
  player->name = element->name ;					
  player->position = element->position ;				
  player->score = element->score ;
  player->injured = element->injured ;
  player->next = player->prev = NULL ;
  if( list == NULL ) {
    list = player ;
    return list ;
  }
  Player *buffer1 , *buffer = list ;
  int NameDif = 0 ;
  int PositionDif = 0 ;
  // altfel cautam pozitia dupa cele 3 criterii :
  while(buffer != NULL) {
    NameDif = strcmp(buffer->name, player->name) ;
    PositionDif = strcmp(buffer->position, player->position) ;
    if( ( PositionDif > 0 ) || (PositionDif == 0 && 
buffer->score < player->score) || (PositionDif == 0 && 
buffer->score == player->score && NameDif > 0) ){
      player->prev = buffer->prev ;
      buffer->prev = player ;
      if( player->prev != NULL )
        player->prev->next = player ;
      else
        list = player ;
      player->next = buffer ;
      return list ;
      
    }
    buffer1 = buffer ;
    buffer = buffer->next ;
  }
  buffer1->next = player ;
  player->prev = buffer1 ;
  return list ;
}
#endif // FOOTBALL_CLUB_H_INCLUDED
