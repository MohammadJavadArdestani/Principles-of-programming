#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
void clear(char **myarr,int length,int Width) {
    for (int i = 0; i < length; i++)
        for (int j = 0; j < Width; j++)
            myarr[i][j] = ' ';
}
void printTable(char**myarr,int length,int Width){
    for(int i=0;i<2*length+1;i++){
        printf("=");}
    printf("\n");
    for(int i=0;i<length;i++){
        for(int j=0;j<Width;j++){
            printf("|");
            printf("%c",myarr[i][j]);}
        printf("|\n");}
    for(int i=0;i<2*length+1;i++)
        printf("=");
    printf("\n");
}

void checkSurvive(char**myarr,char ***mycoparr ,int length,int Width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < Width; j++) {
            int couunt = 0;
            if (myarr[i][j] == '*') {
                if (i != 0 && j != 0 && myarr[i - 1][j - 1] == '*')
                    couunt++;
                if (i != length - 1 && j != Width - 1 && myarr[i + 1][j + 1] == '*')
                    couunt++;
                if (i != 0 && j != Width - 1 && myarr[i - 1][j + 1] == '*')
                    couunt++;
                if (i != length - 1 && j != 0 && myarr[i + 1][j - 1] == '*')
                    couunt++;
                if (i != 0 && myarr[i - 1][j] == '*')
                    couunt++;
                if (j != 0 && myarr[i][j - 1] == '*')
                    couunt++;
                if (i != length - 1 && myarr[i + 1][j]=='*')
                    couunt++;
                if (j != Width - 1 && myarr[i][j + 1]=='*')
                    couunt++;
            }
            if(couunt==2 || couunt == 3)
                (*mycoparr)[i][j] = '*';

        }
    }

}
void checkGeneration(char**myarr,char ***mycoparr ,int length,int Width) {
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < Width; j++) {
            int couunt = 0;
            if (myarr[i][j] == ' ') {
                if (i != 0 && j != 0 && myarr[i - 1][j - 1] == '*')
                    couunt++;
                if (i != length - 1 && j != Width - 1 && myarr[i + 1][j + 1] == '*')
                    couunt++;
                if (i != 0 && j != Width - 1 && myarr[i - 1][j + 1] == '*')
                    couunt++;
                if (i != length - 1 && j != 0 && myarr[i + 1][j - 1] == '*')
                    couunt++;
                if (i != 0 && myarr[i - 1][j] == '*')
                    couunt++;
                if (j != 0 && myarr[i][j - 1] == '*')
                    couunt++;
                if (i != length - 1 && myarr[i + 1][j] == '*')
                    couunt++;
                if (j != Width - 1 && myarr[i][j + 1] == '*')
                    couunt++;
            }
            if (couunt == 3)
                (*mycoparr)[i][j] = '*';


        }
    }
}
void coparr(char**myarr,char**coparr,int length,int Width){
    for(int i=0;i<length;i++)
        for(int j=0;j<Width;j++)
            myarr[i][j]=coparr[i][j];
}

int checkBounderLength(char ***myarr, char ***mycoparr, int length, int Width){
    for (int i = 0; i < Width; i++) {
        if((*myarr)[length-1][i] == '*'){
            *myarr = (char** )realloc((*myarr), (length+1)* sizeof(char *));
            (*myarr)[length] = (char *)malloc(Width* sizeof(char));
            for(int j=0 ; j<Width ; j++)
                (*myarr)[length][j] = ' ';
            *mycoparr = (char **)realloc(*mycoparr, (length+1)* sizeof(char *));
            (*mycoparr)[length] = (char *)malloc(Width* sizeof(char));
            for(int j=0 ; j<Width ; j++)
                (*mycoparr)[length][j] = ' ';
            length = length + 1;
            break;
        }
    }
    for (int i = 0; i < Width; i++) {
        if((*myarr)[0][i] == '*'){
            (*myarr) = (char** )realloc(*myarr, (length+1)* sizeof(char *));
            (*myarr)[length] = (char *)malloc(Width* sizeof(char));
            *mycoparr = (char** )realloc(*mycoparr, (length+1)* sizeof(char *));
            (*mycoparr)[length] = (char *)malloc(Width* sizeof(char));
            for(int j=0 ; j<Width ; j++)
                (*myarr)[length][j] = (*mycoparr)[length][j] = ' ';
            length = length + 1;
            for (int k = 0; k < length; k++) {
                for (int t = 0; t < Width; t++) {
                    if ((*myarr)[k][t] == '*') {
                        (*mycoparr)[k + 1][t] = (*myarr)[k][t];
                    }
                }
            }
            coparr(*myarr,*mycoparr,length,Width);
            clear(*mycoparr,length,Width);
            break;
        }
    }
    return length;
}
int checkBounderWidth(char **myarr, char **mycoparr, int length, int Width){
    for (int i = 0; i < length; ++i) {
        if(myarr[i][Width-1] == '*'){
            for (int j = 0; j < length; ++j) {
                myarr[j] = (char *)realloc(myarr[j], (Width+1)*sizeof(char));
                myarr[j][Width] = ' ';
            }
            for (int j = 0; j < length; ++j) {
                mycoparr[j] = (char *)realloc(mycoparr[j], (Width+1)*sizeof(char));
                mycoparr[j][Width] = ' ';
            }
            Width = Width + 1;
            break;
        }
    }
    for (int i = 0; i < length; i++) {
        if (myarr[i][0] == '*') {
            for (int j = 0; j < length; j++) {
                myarr[j] = (char *) realloc(myarr[j], (Width + 1) * sizeof(char));
                myarr[j][Width] = ' ';
            }
            for (int j = 0; j < length; j++) {
                mycoparr[j] = (char *) realloc(mycoparr[j], (Width + 1) * sizeof(char));
                mycoparr[j][Width] = ' ';
            }
            Width = Width + 1;
            for (int k = 0; k < length; k++) {
                for (int t = 0; t < Width; t++) {
                    if (myarr[k][t] == '*') {
                        mycoparr[k][t + 1] = myarr[k][t];
                    }
                }
            }
            coparr(myarr,mycoparr,length,Width);
            clear(mycoparr,length,Width);
            break;
        }
    }
    return Width;
}


int main() {
    int n;
    printf("please enter number of rows \n");
    scanf("%d",&n);
    int m=n;
    int temp=n;
    int t;
    printf("please enter number of check \n");
    scanf("%d",&t);
    char **orgmap;
    orgmap=(char**)malloc(n*sizeof(char*));
    for(int i=0;i<n;i++)
        orgmap[i]=(char*)malloc(m*sizeof(char));

    char **copmap;
    copmap=(char**)malloc(n*sizeof(char*));
    for(int i = 0;i<n;i++)
        copmap[i]=(char*)malloc(m*sizeof(char));
    clear(orgmap,n,m);
    clear(copmap,n,m);

    int x;
    int y;
    printf("please enter cordinates(enter -1 -1 to finish)\n ");
    while(1){
        scanf("%d%d",&x,&y);
        if(x==-1 || y==-1)
            break;
        else
            orgmap[x][y]='*';
    }

    printTable(orgmap,n,m);
    while (t>0) {
        n = checkBounderLength(&orgmap, &copmap, n, m);
        m = checkBounderWidth(orgmap, copmap, n, m);

        checkSurvive(orgmap, &copmap, n, m);
        checkGeneration(orgmap, &copmap, n, m);
        clear(orgmap, n, m);
        coparr(orgmap, copmap, n, m);
        clear(copmap,n,m);
        n = checkBounderLength(&orgmap, &copmap, n, m);
        m = checkBounderWidth(orgmap, copmap, n, m);
        printTable(orgmap, n, m);
        Sleep(1000);
        for(int i=0;i<10;i++)
            printf("\n");
        t--;
        if(n>temp || m>temp)
            break;
    }
    getchar();
    return 0;
}