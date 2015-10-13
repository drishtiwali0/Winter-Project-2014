//quick/merge/heap
#include<bits/stdc++.h>
#include<sys/time.h>
#include<time.h>
using namespace std;
double givenq[100000],givenm[100000], tmp[100000],givenh[100000];
timeval start_time,stop_time;
long long int compq,compm,comph;
int partitionOLD(double* a,int l,int r)        //partition function
{
	int front=l+1,rear=r,curr=l,t=0;
	while(front<rear)       //start from l+1 and r, compare with pivot element a[l], if not at their appropriate positions swap
	{
		compq+=2;
		if(a[curr]>=a[front])
			front++;
		else
		{
			double tmp=a[front];
			a[front]=a[rear];
			a[rear]=tmp;
			compq+=2;
			rear--;
		}
		compq+=2;                         //to count number of comparisons in quick sort
		if(a[rear]>=a[curr])
			rear--;
		else
		{
			double tmp=a[front];
			a[front]=a[rear];
			a[rear]=tmp;
			compq+=2;
			front++;
		}
	}
	if(a[front]<a[curr])
	{
		double tmp=a[front];
		a[front]=a[curr];
		a[curr]=tmp;
	}
	else
	{
		front--;
		double tmp=a[front];
		a[front]=a[curr];
		a[curr]=tmp;
	}
	compq+=4;
	return front;
}
int partitionREP(double* a, int l, int r, int* left, int* right )
{
	double piv=a[l];
	int start=l+1,end=r,front=l,back=r+1;
	while(start<end)
	{
		while(start<end)
		{
			if(a[start]<piv)
				start++;
			else if(a[start]==piv) 
			{
				a[start]=a[front+1];
				start++;
				front++;
			}
			else
				break;
		}
		while(start<end)
		{
			if(a[end]>piv)
				end--;
			else if(a[end]==piv)
			{
				a[end]=a[back-1];
				end--;
				back--;
			}
			else
				break;
		}
		if(start==end)	break;
		double tmp=a[start];
		a[start]=a[end];
		a[end]=tmp;
	}
	if(a[start]>piv)
		start--;
	end=start+1;
	for(int i=l;i<=front;i++)
	{
		int tmp=start-i+l;
		a[i]=a[tmp];
		a[tmp]=piv;
	}
	for(int i=r;i>=back;i--)
	{
		int tmp=end-i+r;
		a[i]=a[tmp];
		a[tmp]=piv;
	}
	*left=start-front+l-1;
	*right=end-back+r+1;
}	
int partition(double*a, int l, int r)
{
	/*int t1=(rand()%(r-l))+l,t;        //randomized quick sort
	int t2=(rand()%(r-l))+l;
	int t3=(rand()%(r-l))+l;
	if(a[t2]>=min(a[t1],a[t3]) && a[t2]<=max(a[t1],a[t3]))
		t=t2;
	else if(a[t1]>=min(a[t2],a[t3]) && a[t1]<=max(a[t2],a[t3]))
		t=t1;
	else
		t=t3;
	double tmp=a[l];
	a[l]=a[t];
	a[t]=tmp;*/
	double pivot=a[l];
	int left=l+1,right=r;
	while(left<right)
	{
		while(left<right && a[left]<=pivot)
		{
			left++;
			compq++;
		}
		while(left<right && a[right]>=pivot)
		{
			right--;
			compq++;
		}
		if(left==right)	break;
		double tmp=a[left];
		a[left]=a[right];
		a[right]=tmp;
	}
	if(a[left]>=pivot)
		left--;
	right=left+1;
	a[l]=a[left];
	a[left]=pivot;
	compq++;
	return left;
}		
void quicksort(double* a, int l,int r)                 //quick sort implementation
{
	//double extra[r-l];
	int nl,nr;
	if(l>=r)
		return;
	int i=partition(a,l,r);        //partition returns correct position of a[l] in sorted a[l].....a[r], and also ensures a
	                               //[x]<pivot for x<i, and a[x] > pivot for x>i
	quicksort(a,l,i-1);
	quicksort(a,i+1,r);
}
void mergesort(double * a, int l, int r)
{
	if(l>=r)
		return;
	int mid=(l+r)/2;
	mergesort(a,l,mid);                      //recursively sort frist and second half
	mergesort(a,mid+1,r);
	int i=l,j=mid+1,k=0;
	while(i<=mid && j<=r)                   //merge the 2 halves into a singlr temporary array after sorting
	{
		if(a[i]<a[j])
		{
			tmp[k]=a[i];
			k++;
			i++;
		}
		else
		{
			tmp[k]=a[j];
			k++;
			j++;
		}
		compm+=4;
	}
	while(i<=mid)
	{
		tmp[k]=a[i];
		compm+=2;
		k++;
		i++;
	}
	while(j<=r)
	{
		tmp[k]=a[j];
		compm+=2;
		k++;
		j++;
	}
	for(i=l;i<=r;i++)
	{
		a[i]=tmp[i-l];
		compm+=2;
	}
}
void mergesortSPACE(double* a, int l, int r)
{
	if(l>=r)
		return ;
	int mid=(l+r)/2;
	mergesortSPACE(a,l,mid);
	mergesortSPACE(a,mid+1,r);
	int i=l,j=mid+1,k=0;
	for(;i<mid+1;i++,k++)
		tmp[k]=a[i];
	i=l,k=0;
	while(k<=mid-l && j<=r)
	{
		if(tmp[k]<a[j])
		{
			a[i]=tmp[k];
			k++;
			i++;
		}
		else
		{
			a[i]=a[j];
			i++;
			j++;
		}
		compm++;
	}
	while(k<=mid-l)
	{
		a[i]=tmp[k];
		k++;
		i++;
	}
}
void mergesortCOPY(double* a, double* tmp,int l, int r, int t )
{
	if(l>=r && t==0)
		return ;
	else if(l>=r && t==1)
	{
		tmp[l]=a[l];
		//compm+=2;
		return;
	}
	int mid=(l+r)/2;
	mergesortCOPY(a,tmp,l,mid,t^1);                      //recursively sort first and second half
	mergesortCOPY(a,tmp,mid+1,r,t^1);
	int i=l,j=mid+1,k=l;
	if(t==1)
	{
		while(i<=mid && j<=r)                   //merge the 2 halves into a singlr temporary array after sorting
		{
			if(a[i]<a[j])
			{
				tmp[k]=a[i];
				k++;
				i++;
			}
			else
			{
				tmp[k]=a[j];
				k++;
				j++;
			}
			compm++;
		}	
		while(i<=mid)
		{
			tmp[k]=a[i];
			k++;
			i++;
		}
		while(j<=r)
		{
			tmp[k]=a[j];
			k++;
			j++;
		}
	}
	else
	{
		while(i<=mid && j<=r)                   //merge the 2 halves into a singlr temporary array after sorting
		{
			if(tmp[i]<tmp[j])
			{
				a[k]=tmp[i];
				k++;
				i++;
			}
			else
			{
				a[k]=tmp[j];
				k++;
				j++;
			}
			compm++;
		}	
		while(i<=mid)
		{
			a[k]=tmp[i];
			k++;
			i++;
		}
		while(j<=r)
		{
			a[k]=tmp[j];
			k++;
			j++;
		}
	}
}
void heapify(double*a, int i,int n)
{
	while(i<ceil(n/2))
	{
		int max=2*i+1;
		if(2*i+2<n && a[max]<a[2*i+2])
			max=2*i+2;
		if(a[i]<a[max])
		{
			comph++;
			double tmp=a[max];
			a[max]=a[i];
			a[i]=tmp;
			i=max;
		}
		else
			break;
	}
}
void extract_max(double* a, int* m)
{
	int n=*m;
	double tmp=a[0];
	a[0]=a[n];
	a[n]=tmp;
	n--;
	int i=0;
	while(2*i+1<=n)
	{
		int max=2*i+1;
		if(2*i+2<=n && a[max]<a[2*i+2])
			max=2*i+2;
		if(a[i]<a[max])
		{
			comph++;
			double tmp=a[max];
			a[max]=a[i];
			a[i]=tmp;
			i=max;
		}
		else break;
	}
	*m=n;
}
void heapsort(double* a, int n)
{
	int size=n;
	for(int i=ceil(size/2)-1;i>=0;i--)
		heapify(a,i,size);
	n--;
	for(int i=0;i<size;i++)
		extract_max(a,&n);
}
int main()
{
	int n=1000;
	srand(time(NULL));                 //seeding random number generation
	double num=0;
	long long int totalq=0,totalcompq=0,totalm=0,totalcompm=0,totalcomp1=0,totalh=0,totalcomph=0,totalcomp2=0;
	for(int my=0;my<5000;my++)
	{
		for(int i=0;i<n;i++)
		{
			num=(rand()%10000000+1)/10000000;
			givenq[i]=num;                      //givenq is sorted by quick sort
			givenm[i]=num;  
			givenh[i]=num;                   //givenm is sorted by mergesort
		}
		/*for(int i=0;i<n;i++)
			cout<<givenh[i]<<' ';
		cout<<endl;*/
		compm=0;
		gettimeofday(&start_time,NULL);
		mergesort(givenm,0,n-1);
		gettimeofday(&stop_time,NULL);
		long long int diffm= (stop_time.tv_usec - start_time.tv_usec)+(stop_time.tv_sec - start_time.tv_sec)*1000000;//checking time required for merge sort
		totalm+=diffm;
		
		compq=0;                              
		gettimeofday(&start_time,NULL);
		quicksort(givenq,0,n-1);
		gettimeofday(&stop_time,NULL);
		long long int diffq= (stop_time.tv_usec - start_time.tv_usec)+(stop_time.tv_sec - start_time.tv_sec)*1000000;//checking time required for quick sort
		totalq+=diffq;
		totalcompq+=compq;
		if(diffm<diffq)     //to count number of cases where merge sort takes lesser time than quick sort
			totalcomp1++;
		comph=0;
		gettimeofday(&start_time,NULL);
		//heapsort(givenh,n);
		gettimeofday(&stop_time,NULL);
		long long int diffh=(stop_time.tv_usec - start_time.tv_usec)+(stop_time.tv_sec - start_time.tv_sec)*1000000;
			totalh+=diffh;
		totalcomph+=comph;	
		if(diffh<diffq)
			totalcomp2++;
		/*for(int i=0;i<n;i++)
			cout<<givenh[i]<<' ';
		cout<<endl;*/	
		totalcompm+=compm;
	}
	printf("Time for quick sort version 2 : %lld  Number of comparisons for quick sort: %lld\n",totalq,totalcompq);
	printf("Time taken for merge sort version 1 : %lld Number of comparisons for merge sort: %lld\n",totalm,totalcompm);
	//printf("Time taken for heap sort :%lld Number of comparisons for heap sort : %lld\n",totalh,totalcomph);
	printf("Number of times merge sort performs better %lld\n",totalcomp1);
	//printf("Number of times heap sort outpeforms %lld\n",totalcomp2);
	return 0;
}
