#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int NumberofComparisons;
void Merge(int *a,int m,int e)
{
	int i,j,k;
	int Temp_Array[e+1];
	for(i=0;i<=e;i++)
	{
		Temp_Array[i]=a[i];                       //creating temporary array for comparisons              
	}
	j=0;k=m+1;
	
	for(i=0;i<=e;i++)
	{
		if(Temp_Array[j]<=Temp_Array[k])         
		{
			a[i]=Temp_Array[j];
			Temp_Array[j]=1000000007;NumberofComparisons++;
			j++;
			j=j%(m+1);
		}	                                      //using the smaller value from the two halves first
		else if(Temp_Array[j]>=Temp_Array[k])
		{
			a[i]=Temp_Array[k];
			Temp_Array[k]=1000000007;NumberofComparisons++;
			k++;
			k=k%(e+1);
		}	
	}		
	
	return;
}		

void Merge_Sort(int *a,int n)
{
	if(1>=(n)) return;
	Merge_Sort(a,n/2);                        // sorting the two halves
	Merge_Sort(a+n/2,(n-n/2));
	Merge(a,(n/2)-1,n-1);                     // merging the two sorted halves in order
	
	return;
}	

int Partitioning_Index(int *a,int s,int e)
{
	int Pivot_Point=s;                       //choosing First element as Pivot Point 
	int temp;
	s++;
	while(s<=e)
	{
		while(a[s]<=a[Pivot_Point]&&s!=e+1)
		{
			s++;NumberofComparisons++;
		}
		
				
		while(a[e]>=a[Pivot_Point]&&e!=s-1)
		{
			e--;NumberofComparisons++;
		}
		NumberofComparisons +=2;
		if(e<=s) break;
		temp=a[s];                         //interchange elements which are not according to order
		a[s]=a[e];
		a[e]=temp;
		
	}
	s--;
	temp=a[Pivot_Point];
	a[Pivot_Point]=a[s];                   //put Pivot element at its position -'s' the last smaller element
	a[s]=temp;

    return s;
}			
		

void Quick_Sort(int *a,int s,int e)
{
	if(s>=e) return;
	int p;
	p=Partitioning_Index(a,s,e);                //a[p] is set to its expected place
	Quick_Sort(a,s,(p-1));                      //sorting the remaining parts
	Quick_Sort(a,(p+1),e);
	
	return;
}	

int main()
{
  //Initializations	
	int i,t=50000;                                    //Iterating Variable
	double totaltime=0;long long int totalcomp=0;
	int *a;                                   //Array Pointer
	int n,k=0,l;                                   //Size of Array
	n=100;
	double temp;clock_t tStart;
    FILE *f;
		f=fopen("anaquick100.txt","w+");
	while(t--)
	{srand(t);
	a=(int*)malloc(n*sizeof(int));            //Memory Allocation
	
	for(i=0;i<n;i++)
	{
		a[i]=rand()%1000000007;
	}
	NumberofComparisons=0;
	tStart = clock();
	Quick_Sort(a,0,n-1);
    temp= (double)(clock() - tStart)/CLOCKS_PER_SEC; 

	//fscanf(f1,"%d",&l);

	//if(l<temp) k++;
	/*for(i=0;i<n;i++)
	{
		printf("%d ",a[i]);
	}*/
	

	//fprintf(f1,"%.13f\n",temp);                         //Completing the program
	totaltime+=temp;
	totalcomp+=NumberofComparisons;
	fprintf(f,"%.13f %d\n",temp,NumberofComparisons);
	free(a);
    }
    // printf("%d\n",k);
    printf("%lf %lld\n",totaltime,totalcomp);  

    return 0;	
}
