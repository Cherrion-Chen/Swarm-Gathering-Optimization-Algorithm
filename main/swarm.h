#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//群属性变量。
int dim,num;
double *lll;
double *best;

//群初始化，输入解空间维度和群个体数目。
void swarm_init(int d,int n){
	free(lll);
    dim=d;num=n;
    lll=(double *)calloc(n*d,sizeof(double));
}

//随机初始化，输入两个指针，指向各维度的最小值和最大值。
void rand_assign(double *a,double *b){
    double *p=lll;
    double x;
    for(int i=0;i<num;i++,p+=dim){
    	for(int k=0;k<dim;k++){
        	x=rand()/(double)RAND_MAX;
        	*(p+k)=*(a+k)+(*(b+k)-*(a+k))*x;
        }
    }
}

//返回群指针。 
double *address(){
    return lll;
}

//群中序数为n的个体的代价函数值。
double goal(int n,double (*f)(double *x)){
    return f(lll+n*dim);
}

//擂台算法寻找最优个体。
void find_best(double (*f)(double *x)){
    double mn=f(lll);double fb;
    best=lll;
    printf("1 ");
    for(int i=1;i<num;i++){
        fb=f((lll+i*dim));
        if(fb<mn){best=lll+i*dim;mn=fb;}
        printf("%d ",i+1);
    }
    printf("\nmin:%lf , ",mn);
}

//向最优个体移动。
void go(){
    double *start=lll;
    double x;
    for(int i=0;i<num;i++,start+=dim){
        for(int k=0;k<dim;k++){
            x=rand()/(double)RAND_MAX;
            *(start+k)+=(0.5+2.5*x)*(*(best+k)-*(start+k));
        }
    }
}

//集成各功能执行优化任务。
//输入优化次数、代价函数、是否可中断。 
double *optm(int n,double (*f)(double *x),int stoppable){
	srand(time(0));
    if (stoppable){
        for(int epoch=0;epoch<n-1;epoch++){
            double mn=f(lll);double fb;
    		best=lll;
    		printf("1 ");
    		for(int i=1;i<num;i++){
        		fb=f((lll+i*dim));
        		if(fb<mn){best=lll+i*dim;mn=fb;}
        		printf("%d ",i+1);
    		}
    		printf("\nmin:%lf , ",mn);
            double *start=lll;
    		double x;
    		for(int i=0;i<num;i++,start+=dim){
        		for(int k=0;k<dim;k++){
            		x=rand()/(double)RAND_MAX;
            		*(start+k)+=(0.5+2.5*x)*(*(best+k)-*(start+k));
        		}
    		}
            printf("iteration:%d/%d\n\n",epoch+1,n);
            freopen("parameters.txt","w",stdout);
            for(int j=0;j<dim;j++){printf("%lf ",*(best+j));}
            freopen("CON","a",stdout);
        }
    }
    else{
        for(int epoch=0;epoch<n-1;epoch++){
            double mn=f(lll);double fb;
    		best=lll;
    		printf("1 ");
    		for(int i=1;i<num;i++){
        		fb=f((lll+i*dim));
        		if(fb<mn){best=lll+i*dim;mn=fb;}
        		printf("%d ",i+1);
    		}
    		printf("\nmin:%lf , ",mn);
            double *start=lll;
    		double x;
    		for(int i=0;i<num;i++,start+=dim){
        		for(int k=0;k<dim;k++){
            		x=rand()/(double)RAND_MAX;
            		*(start+k)+=(0.5+2.5*x)*(*(best+k)-*(start+k));
        		}
    		}
            printf("iteration:%d/%d\n\n",epoch+1,n);
        }
    }
    find_best(f);
    printf("iteration:%d/%d\n\n",n,n);
    return best;
}

//释放内存。
void free_alloc(){
    free(lll);
}
