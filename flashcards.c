#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CORRECT 1
#define INCORRECT 0

struct card{
	char* word;
	char* definition;
	int history[3];
};

struct cardelem{
	struct card *c;
	struct cardelem *next;
};

struct card* newCard(char* word, char* definition){
	struct card* c = (struct card*)malloc(sizeof(struct card));
	c->history[0] = INCORRECT;
	c->history[1] = INCORRECT;
	c->history[2] = INCORRECT;
	c->word = strdup(word);
	c->definition = strdup(definition);
	return c;
}

struct cardelem* newDeckElement(struct card* card){
	struct cardelem* deckElement = (struct cardelem *) malloc(sizeof(struct cardelem));
    deckElement->c = card;
    return deckElement;
}

/// Displays the word on the card.
void display_word(struct card* c){
	printf("%s\n", c->word);
}

/// Simply displays the definition of the word.
void display_definition(struct card* c){
	printf("%s\n", c->definition);
}

/// Imports cards from a text file.
struct cardelem* import_text_cards(char* file){
	
	// Standard file opening and checking.
	FILE* f;
	if((f = fopen(file, "r")) == NULL){
		puts("Card file could not be opened.");
		abort();
	}

	struct cardelem *deck = (struct cardelem*)malloc(sizeof(struct cardelem));
	struct cardelem *cardp = deck;

	char cardbuffer[256];
	while((fgets(cardbuffer, sizeof cardbuffer, f)) != NULL){ 
		
		// Create a new card.
		char tempword[50], tempdef[50];
		sscanf(cardbuffer, "%49s\t%49s\n", tempword, tempdef);
		
		struct card* c = newCard(tempword, tempdef);	
		cardp->c = c;
		cardp->next = 		cardp = cardp->next;
		cardp->next = NULL;
	}
	return deck;
}

int shuffleDeck(struct cardelem* deck){
		
}

void ask(struct card* c){
	printf("Question (press any key to flip): %s\n", c->word);
	getchar();
	printf("Answer: %s\n", c->definition);
}

int check(){
	printf("Did you get it right? (y/N) ");
	int answer;
	char c = getchar();
	if (c == 'y' || c == 'Y') answer = CORRECT;
	else answer = INCORRECT;
	return answer;
}

void set_history(struct card* c, int answer){
	if (c == NULL) {
		puts("Card history could not be set. Card does not exist.");
		abort();
	}
	c->history[2] = c->history[1];
	c->history[1] = c->history[0];
	c->history[0] = answer;
}

int get_times_correct(struct card* c){
	int right, i;
	right = 0;
	for (i = 0; i < 3; i++){
		if (c->history[i] == CORRECT) right++;
	}
	return right;
}

struct cardelem* filter_incorrect(struct cardelem* deck){
	if (deck == NULL){
		puts("Card deck cannot be filtered: deck does not exist.");
		abort();
	}
	
	struct cardelem *filteredDeck, *deckPointer;
	
	while (deckPointer != NULL){
		if (deckPointer->c->history[0] == CORRECT){
			
		}	
		deckPointer = deckPointer->next;
	}
	return filteredDeck;	
}

int check_if_continue()
{
	puts("Do you want to continue with the cards that you got wrong?");
}

int quiz(struct cardelem *deck){
	struct cardelem *dp = deck;
	while(dp != NULL && dp->c != NULL ){
		ask(dp->c);
		set_history(dp->c, check());
		printf("You got this card correct %d times out of the last 3.\n", get_times_correct(dp->c));
		dp = dp->next;
	}
}

void print_usage(){
	printf("usage:  flashcard FILE\n\tFILE\t The file to load.\n");
}

int main(int argc, char* argv[]){
	if (argc != 2){
		print_usage();
		exit(0);
	}
	quiz(read_cards(argv[1]));
	return 0;
}
