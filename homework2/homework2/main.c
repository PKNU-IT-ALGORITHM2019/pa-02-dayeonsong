#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

typedef struct{
	int x;
	int y;
	int index;
}Point;

double min_dist;
int arr[20];
void read(Point city[],int *n,FILE*fp);
void TSP(Point city[],int k,int n);
void swap(Point city[],int k,int i);
double distance(Point city[],int n);

int main(void)
{
	int n,j,i;
	char file_name[15]="input*.txt";
	Point city[20];
	clock_t start,end;
	FILE*fp=NULL;

	for(j='0';j<'7';j++){
		min_dist=0;
		file_name[5]=j;
		fp=fopen(file_name,"rt");
		if(fp==NULL){
			puts("Failed to open file!");
			return -1;
		}	

		start=clock();
		read(city,&n,fp);
		TSP(city,0,n);
		end=clock();

		printf("*****input%c.txt***** \n",j);
		printf("answer: \n%.15f \n",min_dist);
		printf("[ ");
		for(i=0;i<n-1;i++)
			printf("%d, ",arr[i]);
		printf("%d ] \n",arr[i]);
		printf("실행시간:%f s \n\n",(end-start)/(double)CLOCKS_PER_SEC);
	}
	return 0;
}

void read(Point city[],int *n,FILE*fp)
{
	int i=0;
	char str[10];
	char*str1;

	*n=atoi(fgets(str,sizeof(str),fp));
	while(strcmp(fgets(str,sizeof(str),fp),"\n")!=0)
	{
		str1=strdup(strtok(str," "));//strdup이유: atoi함수실행을 위해 문자배열에 NULL추가
		city[i].x=atoi(str1);
		free(str1);
		str1=strdup(strtok(NULL," "));
		city[i].y=atoi(str1);
		free(str1);
		city[i].index=i;
		i++;
	}
}

void TSP(Point city[],int k,int n)
{
	int i;
	double dist;
	if(k==n){
		dist=distance(city,n);
		if(dist<min_dist||min_dist==0){
			min_dist=dist;
			for(i=0;i<n;i++)
				arr[i]=city[i].index;
		}
		return;
	}
	for(i=k;i<n;i++){
		swap(city,k,i);
		TSP(city,k+1,n);
		swap(city,k,i);
	}
}

void swap(Point city[],int k,int i)
{
	Point temp=city[k];
	city[k]=city[i];
	city[i]=temp;
}

double distance(Point city[],int n)
{
	int i;
	double result=0;
	for(i=0;i<n-1;i++){
		result+=sqrt((double)(city[i].x-city[i+1].x)*(city[i].x-city[i+1].x)+(city[i].y-city[i+1].y)*(city[i].y-city[i+1].y));
	}
	result+=sqrt((double)(city[i].x-city[0].x)*(city[i].x-city[0].x)+(city[i].y-city[0].y)*(city[i].y-city[0].y));
	return result;
}
	

