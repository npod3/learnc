# Operator Precedence (High → Low)

1. `()` function call, `[]` indexing, `.` `->`
2. Unary: `+` `-` `!` `~` `*` (dereference) `&` (address-of) `sizeof`
3. Multiplicative: `*` `/` `%`
4. Additive: `+` `-`
5. Shifts: `<<` `>>`
6. Relational: `<` `<=` `>` `>=`
7. Equality: `==` `!=`
8. Bitwise AND: `&`
9. Bitwise XOR: `^`
10. Bitwise OR: `|`
11. Logical AND: `&&`
12. Logical OR: `||`
13. Ternary: `?:`
14. Assignment: `=` `+=` `-=` `*=` `/=` `%=` `<<=` `>>=` `&=` `^=` `|=`

Tip: When unsure, add parentheses for clarity.
