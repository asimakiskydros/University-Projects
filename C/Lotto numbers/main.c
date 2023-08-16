#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float fmetrics(int*,int,int,int);
int metric0(int*,int,int);
int metric1(int*,int,int);
int placeInOrder(float*,int*);
void printArrayDecreasing(float*,int);

int main()
{
    int numbers, metric,i=0,length=0,length_ranked;
    char *filename=malloc(100*sizeof(char));
    int *data=malloc(1000000*sizeof(int));
    int *ranked=calloc(50,sizeof(int));
    float metric_data[50]={0};
    FILE *fp;

    scanf("%d %d ", &numbers, &metric);
    fgets(filename,100,stdin);
    filename[strcspn(filename,"\n")]='\0';
    filename=realloc(filename,(strlen(filename)+1)*sizeof(char));
    fp=fopen(filename,"r");

    if(numbers<1 || numbers>49 || metric<0 || metric>3)
        printf("Wrong Input!");
    else if(fp==NULL)
        printf("File Error!");
    else
    {
        while(1)
        {
            if(feof(fp))
                break;
            fscanf(fp,"%d",&data[i]);
            i++;
            length++;
        }
        data=realloc(data,length*sizeof(int));
        fclose(fp);
        for(i=1;i<50;i++)
          metric_data[i]=fmetrics(data,metric,length,i);
        length_ranked=placeInOrder(metric_data,ranked);
        ranked=realloc(ranked,length_ranked*sizeof(int));
        for(i=0;i<numbers;i++)
          printf("%d ", ranked[i]);
    }
    return 0;
}

float fmetrics(int *dataarray,int metro,int megethos,int number)
{
	int K=megethos/7;
	float score;
    if(metro==0)
        score=metric0(dataarray,megethos,number);
    else if(metro==1)
        score=metric1(dataarray,megethos,number);
    else if(metro==2)
        score=metric1(dataarray,megethos,number)+metric0(dataarray,megethos,number);
    else 
    {
      int m0=metric0(dataarray,megethos,number);
      if(m0==0)
        return 0;
      score=metric1(dataarray,megethos,number)-(float)K/m0;
    }
    return score;
}

int metric0(int *dataarray,int megethos, int number)
{
    int i,count=0;
    for(i=0;i<megethos;i++)
        if(dataarray[i]==number)
           count++;
    return count;
}

int metric1(int *dataarray, int megethos, int number)
{
    int i, count=0;
    for(i=0;i<megethos;i++)
    {
      if(dataarray[i]==number)
            break;
      count++;
    }
    return count/7;
}

int placeInOrder(float *metricarray,int *orderlyarray)
{
    int i,j,max,count=0;
    for(i=1;i<50;i++)
    {
        max=1;
        for(j=2;j<50;j++)
            if(metricarray[j]>metricarray[max])
                max=j;
        orderlyarray[count]=max;
        metricarray[max]=-1000;
        count++;
    }
    return count;
}