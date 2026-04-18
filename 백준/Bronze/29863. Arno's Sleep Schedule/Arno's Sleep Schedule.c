#include <stdio.h>
main(){
int s,e;
if(scanf("%d %d",&s,&e)==2){
if(e<=s)printf("%d\n",e+24-s);
else printf("%d\n",e-s);
}
}