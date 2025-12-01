# A17 – Blackjack Twist Game

## Overview
Interactive terminal Blackjack with an optional advisor thread performing simplified Monte Carlo estimates and reporting rough EV for Hit vs Stand.

## Code Walkthrough
- Data: `Card`, `Hand`, `Shoe` structs.
- RNG: system `rand()` or xorshift via `-DUSE_XORSHIFT`.
- Advisor: C11 thread updates atomic snapshot values every ~100ms.
- Actions: Hit, Stand, Quit.
- Hand value: Aces counted as 11 then reduced to 1 if bust.

## Key Pitfalls
- Simplified EV logic (does not model dealer outcome fully).
- Thread termination: ensure atomic flag checked; avoid busy wait.
- Reshuffle logic simplistic; could bias distribution.

## Exercises
1. Implement proper dealer outcome simulation in EV.
2. Add Double and Split actions with rules.
3. Track Hi-Lo count using remaining cards.

## Further Reading
- Basic Blackjack strategy charts.
- Monte Carlo simulation techniques.
