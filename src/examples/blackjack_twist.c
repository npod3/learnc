// Purpose: Terminal Blackjack with chips, betting, double-down, and simple advisor.
// Key Concepts: Game state modeling, shoe shuffle, hand values, input loop.
// Build Flags: -DUSE_XORSHIFT to use xorshift RNG (optional).
// Example Invocation: Select ID 117 from menu.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include "platform.h"

typedef struct { uint8_t rank; uint8_t suit; } Card; // rank 1..13, suit 0..3
typedef struct { Card cards[16]; size_t count; } Hand;
typedef struct { Card *cards; size_t size; size_t pos; int decks; } Shoe;

// RNG
static uint32_t rng_state = 1u;
static void rng_seed(uint32_t s){ if(s==0) s=1; rng_state=s; }
#ifdef USE_XORSHIFT
static uint32_t rng_next(void){ uint32_t x = rng_state; x ^= x << 13; x ^= x >> 17; x ^= x << 5; rng_state = x; return x; }
#else
static uint32_t rng_next(void){ return (uint32_t)rand(); }
#endif

static int shoe_init(Shoe *s, int decks){
    s->decks = decks;
    s->size = (size_t)52 * (size_t)decks;
    s->cards = (Card*)malloc(sizeof(Card)*s->size);
    if(!s->cards) return 0;
    size_t idx=0;
    for(int d=0; d<decks; ++d){
        for(int suit=0; suit<4; ++suit){
            for(int rank=1; rank<=13; ++rank){
                s->cards[idx++] = (Card){ (uint8_t)rank, (uint8_t)suit };
            }
        }
    }
    s->pos = 0;
    // Fisher-Yates shuffle
    for(size_t i=s->size-1;i>0;i--){ size_t j = (size_t)(rng_next() % (i+1)); Card tmp = s->cards[i]; s->cards[i]=s->cards[j]; s->cards[j]=tmp; }
    return 1;
}
static void shoe_shuffle(Shoe *s){
    for(size_t i=s->size-1;i>0;i--){ size_t j = (size_t)(rng_next() % (i+1)); Card tmp = s->cards[i]; s->cards[i]=s->cards[j]; s->cards[j]=tmp; }
    s->pos=0;
}
static void shoe_free(Shoe *s){ free(s->cards); s->cards=NULL; s->size=0; s->pos=0; s->decks=0; }
static Card deal_card(Shoe *s){ if(s->pos >= s->size){ shoe_shuffle(s); } return s->cards[s->pos++]; }

static int card_value(Card c){ if(c.rank==1) return 11; if(c.rank>=10) return 10; return (int)c.rank; }
static void hand_add(Hand *h, Card c){ if(h->count<16) h->cards[h->count++]=c; }
static int hand_value(const Hand *h){ int total=0, aces=0; for(size_t i=0;i<h->count;i++){ int v=card_value(h->cards[i]); total+=v; if(h->cards[i].rank==1) aces++; } while(total>21 && aces){ total-=10; aces--; } return total; }

static void render_card(Card c){ const char *ranks="A23456789TJQK"; const char *suits="CDHS"; char r = ranks[c.rank==1?0:c.rank-1]; char s = suits[c.suit]; printf("[%c%c]", r, s); }
static void render_hand(const char *label, const Hand *h, int hide_first){
    printf("%s: ", label);
    for(size_t i=0;i<h->count;i++){
        if(hide_first && i==0) { printf("[??]"); }
        else render_card(h->cards[i]);
        printf(" ");
    }
    if(!hide_first) printf("(=%d)", hand_value(h));
    printf("\n");
}

static void read_line(char *buf, size_t n){ if(n==0) return; if(fgets(buf,(int)n, stdin)==NULL){ buf[0]='\0'; return; } size_t L=strlen(buf); if(L && buf[L-1]=='\n') buf[L-1]='\0'; }
static int read_int_default(const char *prompt, int def){ char line[64]; printf("%s [%d]: ", prompt, def); fflush(stdout); read_line(line,sizeof line); if(line[0]=='\0') return def; int v=def; if(sscanf(line, "%d", &v)==1) return v; return def; }

// Simple basic suggestion based on player total and dealer upcard
static const char* advise_action(const Hand *player, const Hand *dealer){
    int pv=hand_value(player); int up = card_value(dealer->cards[1%dealer->count]);
    if(pv<=11) return "Hit";
    if(pv>=17) return "Stand";
    if(pv==12) return (up>=4 && up<=6)?"Stand":"Hit";
    if(pv>=13 && pv<=16) return (up>=2 && up<=6)?"Stand":"Hit";
    return "Hit";
}

static void settle_round(const Hand *player, const Hand *dealer, int bet, int *chips){
    int pv=hand_value(player), dv=hand_value(dealer);
    int playerBJ = (player->count==2 && pv==21);
    int dealerBJ = (dealer->count==2 && dv==21);
    if(playerBJ && !dealerBJ){ int win = (bet*3)/2; *chips += win; printf("Blackjack! You win +%d\n", win); return; }
    if(dealerBJ && !playerBJ){ *chips -= bet; printf("Dealer blackjack. You lose -%d\n", bet); return; }
    if(pv>21){ *chips -= bet; printf("You bust. -%d\n", bet); return; }
    if(dv>21){ *chips += bet; printf("Dealer busts. +%d\n", bet); return; }
    if(pv>dv){ *chips += bet; printf("You win +%d\n", bet); }
    else if(pv<dv){ *chips -= bet; printf("You lose -%d\n", bet); }
    else { printf("Push. 0\n"); }
}

int example_blackjack_twist(void){
    srand((unsigned)time(NULL)); rng_seed((uint32_t)time(NULL));
    printf("=== Blackjack Twist ===\n");
    int decks = read_int_default("Number of decks (1-8)", 1); if(decks<1) decks=1; if(decks>8) decks=8;
    Shoe shoe; if(!shoe_init(&shoe, decks)){ printf("Shoe init failed.\n"); return 1; }
    int chips = 100; int hands=0, wins=0, losses=0, pushes=0;

    for(;;){
        printf("\nChips: %d  (min bet 5). Enter 0 to quit.\n", chips);
        int bet = read_int_default("Bet", 10);
        if(bet==0) break;
        if(bet<5) { bet=5; }
        if(bet>chips) { bet=chips; }

        Hand player={0}, dealer={0};
        hand_add(&player, deal_card(&shoe));
        hand_add(&dealer, deal_card(&shoe));
        hand_add(&player, deal_card(&shoe));
        hand_add(&dealer, deal_card(&shoe));

        int can_double = (chips>=bet && player.count==2);
        int done=0;

        while(!done){
            printf("\n");
            render_hand("Dealer", &dealer, 1);
            render_hand("Player", &player, 0);
            printf("Advisor: %s\n", advise_action(&player, &dealer));
            printf("Action: (H)it  (S)tand  %s  (U)surrender  (R)eshuffle  (Q)uit round > ", can_double?"(D)ouble":"   "); fflush(stdout);
            char line[32]; read_line(line, sizeof line); char c = (line[0]? (char)line[0] : 'S');
            if((c=='h'||c=='H')){ hand_add(&player, deal_card(&shoe)); if(hand_value(&player)>21){ printf("You drew and busted!\n"); done=1; } }
            else if((c=='d'||c=='D') && can_double){ bet = (bet*2<=chips)? bet*2 : chips; hand_add(&player, deal_card(&shoe)); done=1; }
            else if((c=='s'||c=='S')){ done=1; }
            else if((c=='u'||c=='U')){ // surrender: lose half bet
                int loss = bet/2; printf("You surrendered. -%d\n", loss); // settle immediately
                chips -= loss; done=1; player.count=0; dealer.count=0; // mark as handled
            }
            else if((c=='r'||c=='R')){ shoe_shuffle(&shoe); printf("(Shoe reshuffled)\n"); }
            else if((c=='q'||c=='Q')){ printf("Round canceled (counts as stand).\n"); done=1; }
            else { printf("? Try H/S%s/Q\n", can_double?"/D":""); }
        }

        // Dealer plays if player not busted
        int pv = hand_value(&player);
        if(pv>0 && pv<=21){ while(hand_value(&dealer)<17){ hand_add(&dealer, deal_card(&shoe)); } }
        printf("\nFinal Hands:\n"); render_hand("Dealer", &dealer, 0); render_hand("Player", &player, 0);

        int before = chips; settle_round(&player, &dealer, bet, &chips);
        hands++;
        if(chips>before) wins++; else if(chips<before) losses++; else pushes++;
        printf("Chips now: %d   [W:%d L:%d P:%d]\n", chips, wins, losses, pushes);

        if(chips<5){ printf("You are out of chips. Game over.\n"); break; }
    }

    shoe_free(&shoe);
    printf("Thanks for playing!\n");
    return 0;
}
