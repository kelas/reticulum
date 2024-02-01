#include "r.h"

#if 1
#define D       32
#define STEPS   20
#else
#define D       64
#define STEPS   10
#endif

#define SPEED   .04f
#define STROKE  .07f
#define FADE    1.0f
#define SPIN    .07f
#define DIR     1
#define px      p->x
#define py      p->y
#define pz      p->z

//!terminal emulator
I fbp;C fb[6+29*D*D+D*2];//framebuffer:pos,sof+rgb+nl
#define SOF "\x1b[0;0f"
#define FB(a...) fbp+=sprintf(fb+fbp,a);
#define RGB(c) FB("\x1b[38;2;%d;%d;%dm\u2022\u2022\x1b[0m",c.r,c.g,c.b)
static struct termios orig_termios;ZI vim_send(S s,I n){R write(STDOUT_FILENO,s,n);}
ZI vim_cursor(I c){R vim_send(c?"\x1b[?25h":"\x1b[?25l",6);}//cursor on/off
ZV vim_die(S err){vim_cursor(1);vim_send("\x1b[2J\x1b[H",7);perror(err);exit(1);}
ZV vim_raw_off(){vim_cursor(1);if(tcsetattr(STDIN_FILENO,TCSAFLUSH,&orig_termios)==-1)vim_die("tcsetattr");}
ZI vim_clr(){R vim_send("\x1b[1;1H\x1b[2J",10);}ZV vim_exit(){vim_clr();vim_raw_off();exit(0);}
ZV vim_raw_on(){tcgetattr(STDIN_FILENO,&orig_termios);atexit(vim_raw_off);signal(SIGINT,vim_exit);
 struct termios raw=orig_termios;raw.c_iflag&=~(BRKINT|ICRNL|INPCK|ISTRIP|IXON);
 raw.c_oflag&=~(OPOST);raw.c_cflag|=(CS8);raw.c_lflag&=~(ECHO|ICANON|IEXTEN);raw.c_iflag&=IGNBRK;
 raw.c_cc[VMIN]=0;raw.c_cc[VTIME]=1;tcsetattr(STDIN_FILENO,TCSAFLUSH,&raw);vim_clr();vim_cursor(0);}

//!reticulum
#define T(t,d) struct t{d;};typedef struct t t;
T(rgb,G r;G g;G b)T(xyz,F x;F y;F z)UJ frame;F rays[D];
#define NRM(rgb,xyz) (G)(MIN(FADE,(rgb+sin(xyz))/l)*255)//normalize+clamp
F len(xyz*p){R sqrt(px*px+py*py+pz*pz);}F ln(F x,F y){R sqrt(x*x+y*y);}
F sdf(xyz*p){pz-=frame*SPEED;F a=pz*SPIN,c=cos(a),s=sin(a),x=c*px+s*py,y=c*py-s*px;
 px=x;py=y;R STROKE-ln(cos(px)+sin(py),cos(py)+sin(pz));}
V frag(I x,I y,xyz*p){xyz t=*p;F f=sdf(&t);px+=f*rays[x],py+=f*rays[y],pz+=f*.5*DIR;}
I main(){F l;xyz p;rgb t,buf[D*D];N(D,rays[i]=(F)i/D-.5)vim_raw_on();
 W(1){FB(SOF)N(D,Nj(D,p.x=p.y=p.z=0;G steps=STEPS;W(steps--)frag(i,j,&p);l=len(&p);
  t=buf[i*D+j];t.r=NRM(2,p.x);t.g=NRM(5,p.y);t.b=NRM(9,p.z);RGB(t))FB("\r\n"))
  vim_send((S)fb,fbp),fbp=0,frame++;}R 0;}

//:~
