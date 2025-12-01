// Purpose: Finite State Machine parsing a tiny digit+operator expression: e.g. 12+3-4
// Example Invocation: ID 106

#include <stdio.h>
#include <ctype.h>

int example_parsing_fsm(void){
    const char *expr = "12+3-4";
    printf("[Parsing FSM] expr=%s\n", expr);
    enum { ST_START, ST_NUMBER, ST_OP } state = ST_START;
    int total=0, current=0, sign=+1;
    for(const char *p=expr; *p; ++p){
        char c=*p;
        switch(state){
            case ST_START:
                if(isdigit((unsigned char)c)){ current = c-'0'; state = ST_NUMBER; }
                break;
            case ST_NUMBER:
                if(isdigit((unsigned char)c)){ current = current*10 + (c-'0'); }
                else {
                    total += sign*current; current=0;
                    if(c=='+'||c=='-'){ sign = (c=='+')?+1:-1; state=ST_OP; }
                }
                break;
            case ST_OP:
                if(isdigit((unsigned char)c)){ current = c-'0'; state=ST_NUMBER; }
                break;
        }
    }
    total += sign*current;
    printf("Result=%d\n", total);
    printf("FSM parsing complete (no whitespace support in stub).\n");
    return 0;
}
