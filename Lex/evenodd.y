%token EVEN ODD

%%

input:
EVEN { printf("EVEN NUMBER\n"); return 0; }
|ODD { printf("ODD NUMBER\n"); return 0; }
; 