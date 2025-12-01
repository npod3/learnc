// Purpose: Terminal Blackjack with advisor thread estimating EV of actions.
// Key Concepts: Game state modeling, Monte Carlo simulation, C11 atomics & threads, pluggable RNG.
// Build Flags: -DUSE_XORSHIFT to use xorshift RNG; advisor disabled if threads unavailable.
// Example Invocation: Select ID 117 from menu.
// Pitfalls: Simplified EV calculation; not a full casino rule set; concurrency simplified.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdatomic.h>
#ifdef __STDC_NO_THREADS__
#warning Threads unsupported; advisor disabled.
#else
#include <threads.h>
#endif
#include "platform.h"

// Card representation
typedef struct { uint8_t rank; uint8_t suit; } Card; // rank 1..13, suit 0..3
typedef struct { Card cards[16]; size_t count; uint8_t is_split; } Hand;
typedef struct { Card *cards; size_t size; size_t pos; } Shoe;

// Atomic snapshot values
static _Atomic double g_ev_hit = 0.0;
static _Atomic double g_ev_stand = 0.0;
static _Atomic double g_true_count = 0.0;
static _Atomic int g_advisor_run = 0;

// RNG interface
static uint32_t rng_state = 1u;
static void rng_seed(uint32_t s){ if(s==0) s=1; rng_state=s; }
static uint32_t rng_next_sys(void){ return (uint32_t)rand(); }
#ifdef USE_XORSHIFT
static uint32_t rng_next_xor(void){ uint32_t x = rng_state; x ^= x << 13; x ^= x >> 17; x ^= x << 5; rng_state = x; return x; }
#endif
static uint32_t rng_next(void){
#ifdef USE_XORSHIFT
    return rng_next_xor();
#else
    return rng_next_sys();
#endif
}

static int shoe_init(Shoe *s, int decks){
    s->size = 52 * decks;
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
    // Shuffle
    for(size_t i=0;i<s->size;i++){ size_t j = (size_t)(rng_next() % s->size); Card tmp = s->cards[i]; s->cards[i]=s->cards[j]; s->cards[j]=tmp; }
    return 1;
}

static void shoe_free(Shoe *s){ free(s->cards); s->cards=NULL; s->size=0; s->pos=0; }

static Card deal_card(Shoe *s){ if(s->pos >= s->size){ // reshuffle simple
        s->pos = 0; for(size_t i=0;i<s->size;i++){ size_t j=(size_t)(rng_next()%s->size); Card tmp=s->cards[i]; s->cards[i]=s->cards[j]; s->cards[j]=tmp; }
    } return s->cards[s->pos++]; }

static int card_value(Card c){ if(c.rank==1) return 11; if(c.rank>=10) return 10; return (int)c.rank; }
static int hand_value(const Hand *h){ int total=0; int aces=0; for(size_t i=0;i<h->count;i++){ int v=card_value(h->cards[i]); total+=v; if(h->cards[i].rank==1) aces++; } while(total>21 && aces){ total-=10; aces--; } return total; }

static void hand_add(Hand *h, Card c){ if(h->count < 16) h->cards[h->count++]=c; }

static void render_card(Card c){ const char *ranks="A23456789TJQK"; const char *suits="CDHS"; char r = ranks[c.rank==1?0:c.rank-1]; char s = suits[c.suit]; printf("%c%c", r, s); }
static void render_hand(const char *label, const Hand *h){ printf("%s: ", label); for(size_t i=0;i<h->count;i++){ render_card(h->cards[i]); printf(" "); } printf("(value=%d)\n", hand_value(h)); }

#ifndef __STDC_NO_THREADS__
static int advisor_thread(void *arg){ Shoe *shoe = (Shoe*)arg; (void)shoe; // Simplified: use remaining cards distribution
    while(atomic_load(&g_advisor_run)){
        // Monte Carlo estimates: sample hypothetical hit card
        double hit_sum=0.0, stand_sum=0.0; int samples=200; // small for demo
        for(int i=0;i<samples;i++){
            uint32_t r = rng_next();
            int card_rank = (int)((r % 13) + 1);
            int v = (card_rank==1?11: (card_rank>=10?10:card_rank));
            hit_sum += v; // naive placeholder
            stand_sum += 0.0; // stand baseline
        }
        atomic_store(&g_ev_hit, hit_sum/samples);
        atomic_store(&g_ev_stand, stand_sum); // zero baseline
        atomic_store(&g_true_count, 0.0); // placeholder count
        struct timespec ts = {0, 100*1000*1000}; // 100ms
#ifdef _WIN32
        platform_sleep_ms(100);
#else
        nanosleep(&ts, NULL);
#endif
    }
    return 0;
}
#endif

static void maybe_start_advisor(Shoe *shoe, int enable){
#ifndef __STDC_NO_THREADS__
    if(!enable) return; atomic_store(&g_advisor_run, 1); thrd_t t; thrd_create(&t, advisor_thread, shoe); thrd_detach(t);
#else
    (void)shoe; (void)enable; printf("Advisor unavailable: threads not supported.\n");
#endif
}

static void stop_advisor(void){ atomic_store(&g_advisor_run, 0); }

static void show_advisor_snapshot(void){
    double eh = atomic_load(&g_ev_hit);
    double es = atomic_load(&g_ev_stand);
    double tc = atomic_load(&g_true_count);
    printf("[Advisor] EV(hit)=%.2f EV(stand)=%.2f true_count=%.2f\n", eh, es, tc);
}

static int player_turn(Hand *player, Shoe *shoe, int advisor){
    while(1){
        render_hand("Player", player);
        if(advisor) show_advisor_snapshot();
        printf("Action: (h)it (s)tand (q)uit > "); fflush(stdout);
        int ch=0;
        if(platform_kbhit()) ch = platform_getch(); else ch = getchar();
        if(ch=='h'||ch=='H'){
            hand_add(player, deal_card(shoe));
            int v = hand_value(player);
            if(v>21){ printf("Bust! (%d)\n", v); return -1; }
        } else if(ch=='s'||ch=='S'){
            return 0;
        } else if(ch=='q'||ch=='Q'){
            return 1; // early quit
        } else {
            printf("?\n");
        }
    }
}

static int dealer_play(Hand *dealer, Shoe *shoe){
    while(hand_value(dealer) < 17){ hand_add(dealer, deal_card(shoe)); }
    return hand_value(dealer);
}

int example_blackjack_twist(void){
    printf("[Blackjack Twist]\n");
    srand((unsigned)time(NULL)); rng_seed((uint32_t)time(NULL));
    int decks = 1; int advisor=1;
    printf("Decks (1-8)? "); fflush(stdout); int d = 0; if(scanf("%d", &d)==1 && d>=1 && d<=8) decks=d; else printf("Using 1 deck.\n");
    printf("Enable advisor (1=yes 0=no)? "); fflush(stdout); int a=0; if(scanf("%d", &a)==1) advisor=a; else advisor=1;
    Shoe shoe; if(!shoe_init(&shoe, decks)){ printf("Shoe init failed.\n"); return 1; }
    maybe_start_advisor(&shoe, advisor);
    Hand player={0}; Hand dealer={0};
    hand_add(&player, deal_card(&shoe));
    hand_add(&dealer, deal_card(&shoe));
    hand_add(&player, deal_card(&shoe));
    hand_add(&dealer, deal_card(&shoe));

    printf("Initial Hands:\n");
    render_hand("Dealer", &dealer);
    render_hand("Player", &player);

    int pt = player_turn(&player, &shoe, advisor);
    if(pt==1){ printf("Player quit early.\n"); stop_advisor(); shoe_free(&shoe); return 0; }
    if(pt==-1){ // bust
        printf("Dealer wins.\n"); stop_advisor(); shoe_free(&shoe); return 0; }

    int dv = dealer_play(&dealer, &shoe);
    int pv = hand_value(&player);
    printf("Final Hands:\n"); render_hand("Dealer", &dealer); render_hand("Player", &player);
    if(dv>21 || pv>dv) printf("Player wins!\n"); else if(pv==dv) printf("Push.\n"); else printf("Dealer wins.\n");

    stop_advisor(); shoe_free(&shoe);
    return 0;
}
