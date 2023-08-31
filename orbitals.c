#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int help(int, char *[]);
int basisInfo(FILE *, int* prim, int* cont);

int main(int argc, char *argv[]){

    char cad[129];
    int flag, flagBasis;
    int outsscanf;
    int  a,b,iop,norb,norb2;
    int prim, cont;
    double termID, termIND, termIT;
    double Index1, Index2;
    double alpha, beta;
    double nelec,tmpn;
    double elea,eleb;
    FILE *inp;

    iop = 0;

    iop = help(argc, argv);

    inp = fopen(argv[argc-1],"r");
    if( inp == NULL ){
        fprintf(stderr," Error to open the file [%s]\n",argv[argc-1]);
        exit(EXIT_FAILURE);
    }

    rewind(inp);
    norb2=norb=0;
    nelec = (double)0.;
    alpha = beta = (double) 0.;
    flag = 0;
    while(!feof(inp)){
        fgets(cad,128,inp);
        a = strncmp(cad,"Natural Orbital Occupation Numbers:",34);
        if( a == 0 ){
            // We enter the zone of orbital occupation
            flag = 1;
            b = 1;
            do{
                fgets(cad,128,inp);
                b = strncmp(cad,"N[",2);
                outsscanf = sscanf(cad,"N[%*d] = %lf",&tmpn);
                if( outsscanf == 1 ){
                // If the reading of the orbital and the occupation is correct, we analyze and count the orbital.
                if( tmpn > 0.0 ){ 
                    eleb = tmpn/2.;
                    elea = tmpn/2;
                    if( iop == 2 )
                        printf("   Orb %5d  -> % 12.8lf, %12.8lf\n",norb, elea, eleb);

                    alpha += sqrt( elea * (1. - elea));
                    beta  += elea * (1. - elea);
                    alpha += sqrt( eleb * (1. - eleb));
                    beta  += eleb * (1. - eleb);

                    nelec += tmpn;
                    norb2 += 2;
                }
                norb++;
                }
            }while( b == 0 );
        }
    }

    flagBasis =  basisInfo(inp, &prim, &cont);

    fclose(inp);

    if( flag == 1){
    printf(" norb [file]   : % 12d\n",norb);
    printf(" norb [natural]: % 12d\n",norb2);

    printf(" nelectrons    : % 12.8lf\n",nelec);

    termID = 0.25 * alpha - 0.5 * beta;
    termIND = 0.5 * beta;
    termIT = termID + termIND;
    Index1 = termIND / termIT;
    Index2 = termID / termIT;
    printf("\n");
    printf("            ID : % 12.8lf\n",termID);
    printf("           IND : % 12.8lf\n",termIND);
    printf("            IT : % 12.8lf\n",termIT);
    printf(" Index1=IND/IT         : % 12.8lf\n",Index1);
    printf(" Index2=ID/IT          : % 12.8lf\n",Index2);
    }else{
        printf(" The program has not found information of\n");
        printf("   Natural Orbital Occupation Numbers\n");
        printf(" in the file [%s]\n",argv[argc-1]);
    }

    if( flagBasis != 0 ){
        printf("\n");
        printf(" Number of contracted basis functions %5d\n", prim);
        printf(" Number of contracted shells %5d\n", cont);
        printf("\n");
    }else{
        printf(" The program has not found information of\n");
        printf("   Number of gaussian functions\n");
        printf(" in the file [%s]\n",argv[argc-1]);
    }

    exit(EXIT_SUCCESS);
}


int help(int argc, char *argv[]){

    if( argc == 1 ){
        printf(" The program needs more information to run!\n");
        printf(" Run the program like this\n");
        printf(" %s  file.log\n\n",argv[0]);
        printf(" Options :\n");
        printf("    -h   :  for help \n");
        printf("    -v   :  for version \n");
        printf("    -o   :  shows the orbitals and occupations \n");
        printf("\t %s -o file.log\n\n",argv[0]);
        exit(EXIT_SUCCESS);
    }

    if( argc == 2 ){
        if( argv[1][0] == '-' && argv[1][1] == 'v'){
            printf(" Version 0.1 \n");
            exit(EXIT_SUCCESS);
        }
        if( argv[1][0] == '-' && argv[1][1] == 'h'){
            printf(" %s  file.log\n\n",argv[0]);
            printf(" Options :\n");
            printf("    -h   :  for help \n");
            printf("    -v   :  for version \n");
            printf("    -o   :  shows the orbitals and occupations \n");
            printf("\t %s -o file.log\n\n",argv[0]);
            exit(EXIT_SUCCESS);
        }
        return  0;
    }
    if( argc == 3 ){
        if( argv[1][0] == '-' && argv[1][1] == 'o'){
            return 2;
        }
    }
    if( argc > 3 ){
        printf(" The program has more information to run\n");
        printf(" Run the program like this\n");
        printf(" %s  file.log\n\n",argv[0]);
        printf(" Options :\n");
        printf("    -h   :  for help \n");
        printf("    -v   :  for version \n");
        printf("    -o   :  shows the orbitals and occupations \n");
        printf("\t %s -o file.log\n\n",argv[0]);
        exit(EXIT_SUCCESS);
    }
}


int basisInfo(FILE *inp, int *iprim, int *icont){
    int out=0;
    int prim=0, cont=0;
    int a;
    char cad[129];

    char flag1[] = " # of contracted basis functions       ...";
    char flag2[] = " # of contracted shells         ...";

    prim = 0;
    cont = 0;
    rewind(inp);
    while(!feof(inp)){
        fgets(cad,128,inp);
        a = strncmp(cad, flag1, 32);
        if( a == 0 ){
            out +=1;
            sscanf(cad," # of contracted basis functions       ...%d",&prim);

        }
        a = strncmp(cad, flag2, 32);
        if( a == 0 ){
            out +=2;
            sscanf(cad," # of contracted shells         ...%d",&cont);
        }
    }
    (*iprim) = prim;
    (*icont) = cont;

    rewind(inp);
    return out;
}
