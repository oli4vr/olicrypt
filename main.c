/* Personal encryption experiment
 * Simple stdin to stdout usage
 * by Olivier Van Rompuy
 *
 * I wrote this program to learn some basics about encryption.
 *
 * Per iteration/round the following is done to the data :
 * - 1st round only : Starting InvertXOR with 8192bit key
 * - Byte substitution (different translation tables per round)
 * - Leftway bitwise rotation *A (per 64bit words)
 * - InvertXOR with 8192bit key
 * - Rightway bitwise rotation *B (per 64bit words)
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "encrypt.h"

#define BUFFER_SIZE 65536

int main(int argc, char ** argv) {
 crypttale ct;
 unsigned char buffer[BUFFER_SIZE];
 unsigned char *keystr;
 unsigned char *opt;
 int rsize,wsize;
 unsigned char mode=1;
 unsigned char *cmd=argv[0];
 unsigned char badsyntax=0;
 int rnds=8;
 argc--;
 argv++;

 while (argc>1) {
  opt=*argv;
  if (*opt!='-') {badsyntax=1; argc=0;}
  else {
   switch(opt[1]) {
    case 'd':
	   mode=0;
	   break;
    case 'r':
	   argc--;
	   argv++;
	   if (argc>0) {rnds=atoi(*argv)&1023;}
	   else {badsyntax=1;}
	   break;
    default:
	   badsyntax=1;
	   break;
   }
   argc--;
   argv++;
  }
 }

 if (argc<1) {badsyntax=1;}
 else if (argv[0][0]=='-') {badsyntax=1;}

 if (badsyntax) {
  fprintf(stderr,"%s\n  by Olivier Van Rompuy\n\n  Syntax : %s [-d] [-r rounds] keystring\n",cmd,cmd);
  fprintf(stderr,"   -d\tDecrypt\n");
  fprintf(stderr,"   -r\t#Rounds\n");
  fprintf(stderr,"\n");
  return -1;
 }

 if (rnds > 256) rnds=256;
 fprintf(stderr,"%s %d\n",argv[0],rnds);
 init_encrypt(&ct,argv[0],rnds);
 
 rsize=fread(buffer,1,BUFFER_SIZE,stdin);
 while (rsize>0) {
  if (mode) {
   encrypt_data(&ct,buffer,rsize);
  } else {
   decrypt_data(&ct,buffer,rsize);
  }
  wsize=fwrite(buffer,1,rsize,stdout);
  if (wsize<rsize) {fprintf(stderr,"Write Error : Elements Read %d Writen %d\n",rsize,wsize);exit(1);}
  rsize=fread(buffer,1,BUFFER_SIZE,stdin);
 }

 return 0;
}
