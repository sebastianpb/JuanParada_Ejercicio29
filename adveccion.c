#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

/*def initial(delta_x=0.05):
    L = 4.0
    N = L/delta_x + 1
    x = np.linspace(0.0, L, N)
    u = np.zeros(N)
    ii = x<2.0
    u[ii] = 1.0
    return x, u
*/

/*def Lax(u, t_max=0.45, delta_t = 0.015, delta_x=5.0):
    N_t = int(t_max/delta_t)
    u_final = u.copy()
    for i in range(N_t):
        F = flux(u)
        u_final[1:-1] = 0.5*(u[2:] + u[0:-2]) 
        u_final[1:-1] -= (0.5*delta_t/delta_x)*(F[2:] - F[0:-2]) 
        u = u_final.copy()
    return u_final
*/
    




void initial(double delta_x, double *x, double *u, int L) {
    double dN=(L/delta_x) + 1;
    printf("dn es %f",dN);
    int N=(int)dN;
    double fr=L/(N-1);
    printf("N= %d",N);
    int i;

    for(i = 0; i < N; i++)
    {
        x[i]=(double)i*fr;
        if(x[i]<2)
        {
            u[i]=1;
        }
        else{
            u[i]=0;
        }
    }
}


double *flux(double *u, int len) {
    double *ret = malloc(len);
    int i;
    if(!ret){
        return NULL;
    }

    for(i = 0; i < len; i++)
    {
        printf("siezeof(u): %lo\n",sizeof(u));
        ret[i] = 0.5*pow(u[i],2);
        printf("ret[%d]: %f\n",i,ret[i]);
    }
    return ret;
}

    
void Lax(double *u, double *u_final, double t_max, double delta_t, double delta_x, int N) {
    double fr=t_max/delta_t;
    double *F;
    int N_t=(int)fr;
    int i,j;

    for(i = 0; i < N_t; i++)
    {
        F=flux(u,sizeof(u)/sizeof(double));
        for(j=0;j<N-2;j++){
            u_final[j+1]=0.5*(u[j+2]+u[j]);
            u_final[j+1]-=(0.5*delta_t/delta_x)*(F[j+2] - F[j]) ;
        }
        u=u_final;
    }
}

int main(int argc, char **argv){

    int L=4;
    double delta_x=1;
    double dN=(L/delta_x) + 1;
    int N=(int)dN;
    double u[N];
    double x[N];
    
    double *fl;


    int i;
    for(i=0;i<10;i++)
    {
        u[i]=0.1+i;
        printf("u[%d]: %f\n",i,u[i]);
    }
    
    fl=flux(u,sizeof(u)/sizeof(double));
    initial(delta_x, x,u,L); 
    for(i=0;i<10;i++)
    {
        printf("fl[%d]= %f\n",i,*(fl+i));
    }
    
    for(i=0;i<N;i++)
    {
        printf("x[%d]= %f\n",i,x[i]);
        printf("u[%d]= %f\n",i,u[i]);
    }
    
    double *u_final=u;
    double t_max=1;
    double delta_t=1;

    Lax(u, u_final,  t_max, delta_t, delta_x, N);
        
    for(i=0;i<N;i++)
    {
        printf("u_final[%d]= %f\n",i,u_final[i]);
    }
    
}