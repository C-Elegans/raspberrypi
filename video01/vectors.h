#include "io.h"
inline unsigned int GET32 ( unsigned int );
inline unsigned int GETPC ( void );
void BRANCHTO ( unsigned int );
void dummy ( unsigned int );
void start_l1cache();
void stop_l1cache();
void start_mmu(unsigned int, unsigned int);
