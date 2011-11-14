/****************************************************************/
/* VisX4 program v3dvol					                                                   */
/*            Compute function on a 3D image structure                            */
/* Syntax:                                                                                               */
/*        v3dvol if=infile of=outfile [-v]                                                         */
/****************************************************************/

#include "VisXV4.h"          /* VisX structure include file     */
#include "Vutil.h"           /* VisX utility header files       */
VisXfile_t *VXin,            /* input file structure            */
	            *VXout;           /* output file structure           */
VisXelem_t *VXlist;          /* VisX data structure             */
VisXparam_t par[] =          /* command line structure          */
{
    "if=",    0,   /* input file       */
    "of=",    0,   /* output file      */
    "-v",     0,   /* visible flag     */
     0,       0    /* list termination */
};
#define  IVAL   par[0].val
#define  OVAL   par[1].val
#define  VFLAG  par[2].val

main(argc, argv)
int argc;
char *argv[];
{

VisX3dim_t im;                     /* input v3dim structure        */
VisX3dim_t tm;                     /* temp structure */
VisXelem_t *vptr;
int	   i,j,k;                  /* index counters               */
unsigned char t;
int volume;
    Vparse(&argc, &argv, par);     /* parse the command line       */
    VXin  = VXopen(IVAL, 0);       /* open input file              */
    VXout = VXopen(OVAL, 1);       /* open the output file         */
    VXlist = VXread(VXin);         /* read file                    */
    if(VXNIL == (vptr = VXfind(VXlist, VX_PBYTE))){
        fprintf(stderr, "v3df: no byte images found\n");
        exit(1);
    }
    VXset3dim(&im, vptr, VXin); /* initialize input structure   */
    VXembed3dim(&tm, &im, 1, 1, 1, 1, 1, 1); /* embed input structure   */
    if(VFLAG){
        fprintf(stderr,"bbx is %f %f %f %f %f %f\n", im.bbx[0],
		im.bbx[1],im.bbx[2],im.bbx[3],im.bbx[4],im.bbx[5]);
    }

    /* simple pixel computation -- notice the order of the loops */
    volume = 0;
    for (k = im.zlo; k <= im.zhi; k++){
        for (i = im.ylo; i <= im.yhi; i++){
            for (j = im.xlo; j <= im.xhi; j++){
	            if(im.u[k][i][j] == 255) {
	                volume++;
	            }
	        }
        }
    }
	
	fprintf(stdout, "The volume of this 3d image is: %d\n", volume);
	     
    VXwrite(VXout, VXlist);       /* write data                   */
    VXclose(VXin);                /* close files                  */
    VXclose(VXout);
    exit(0);
}
