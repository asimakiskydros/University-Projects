#include <stdio.h>
#include <stdlib.h>

typedef struct energy{
	int month;
	int code;
	int *codesWithEnergy;
	int amountEnergy0;
	int totalEnergy;
}energy;

typedef struct pair{
	int code;
	int data;
}pair;

void totals(pair* input,energy* output){
	int i,j=0;
	int countEnergy0=0;
	int countEnergy=0;
	int *ret=malloc(10*sizeof(int));
	for(i=0;i<10;i++){
		if(input[i].data==0)
			countEnergy0++;
		else
			ret[j++]=input[i].code;
		countEnergy+=input[i].data;
	}
	output->codesWithEnergy=ret;
	output->amountEnergy0=countEnergy0;
	output->totalEnergy=countEnergy;
}

int main(void) {
	FILE *fp;
	energy *arr;
	int i;
	int j=0;
	int k;
	int *countMonths=calloc(13,sizeof(int));
	pair *pairs;
	fp=fopen("energy.txt","r");
	if(fp==NULL)
		printf("File error\n");
	else{
		arr=malloc(29*sizeof(energy));
		while(1){
			if(feof(fp))
				break;
			fscanf(fp,"%d %d",&arr[j].code,&arr[j].month);
			countMonths[arr[j].month]++;
			pairs=malloc(10*sizeof(pair));
			for(i=0;i<10;i++)
				fscanf(fp,"%d %d",&pairs[i].code,&pairs[i].data);
			totals(pairs,&arr[j]);
			free(pairs);
			pairs=NULL;
			j++;
		}
		fclose(fp);
		for(k=0;k<29;k++){
			printf("month=%d,park code=%d,codes of turbines with power:",arr[k].month,arr[k].code);
			for(i=0;i<10;i++)
				printf("%d,",arr[k].codesWithEnergy[i]);
			printf(",turbines with 0 energy=%d,total energy=%d\n",arr[k].amountEnergy0,arr[k].totalEnergy);
		}
		for(k=1;k<13;k++)
			printf("month %d: %d times\n",k,countMonths[k]);
		
	}
	return 0;
}