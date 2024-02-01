#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h> 
#include<fcntl.h>
#include<termios.h>
#include<signal.h>

//! arthur way
typedef char C,*S;typedef int I;typedef short H;typedef void V;typedef float F;typedef double E;typedef long J;
typedef unsigned long long UJ;typedef unsigned int UI;typedef unsigned short UH;typedef unsigned char G;

#define ZV static V
#define ZG static G
#define ZI static I
#define ZE static E

#define O printf
#define R return
#define NL O("\n");

//! easy math
#define ABS(x) (((x)>0)?(x):-(x))
#define MIN(x,y) ((y)>(x)?(x):(y))
#define MAX(x,y) ((y)>(x)?(y):(x))
#define IN(l,x,r) ((l)<=(x)&&(x)<=(r))

//! no stinking loops
#define W(a...) while(({a;}))
#define N(n,a...) {UI _n=(n),i=-1;W(++i<_n){a;}}
#define Nj(n,a...) {UI _n=(n),j=-1;W(++j<_n){a;}}

//! fail fast
#define P(x,y...) {if(x)R(y);} //< panic aka predicate

//:~
