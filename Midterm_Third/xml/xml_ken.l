%{
#include "xml_ken.tab.h"
%}
%%

"<or>" {return OR_START;}
"</or>" {return OR_END;}
"<and>" {return AND_START;}
"</and>" {return AND_END;}
"<not>" {return NOT_START;}
"</not>" {return NOT_END;}
"<true/>" {yylval.ival = 1; return VAL;}
"<false/>" {yylval.ival = 0; return VAL;}
.|\n

%%

