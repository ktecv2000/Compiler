| Stack 　　　　| Input　　　　　 | Action　 |
| ------| ------ | ------ |
| $ | id*id+num$ | shift |
| $id | *id+num$ | r5 |
| $F | *id+num$ | r4 |
| $T | *id+num$ | shift |
| $T* | id+num$ | shift |
| $T*id | +num$ | r5 |
| $T*F | +num$ | r2 |
| $T | +num$ | shift |
| $T+ | num$ | shift |
| $T+num | $ | r6 |
| $T+F | $ | r2 |
| $T | $ | r1 |
| $E | $ | accept |
