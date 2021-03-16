  .name   "Batman"
 .comment    "This city 
needs me"  #x

loop:
        sti r1, %:live, r1 
live:
        live %01
        ld %0, r1
        zjmp %:loop
