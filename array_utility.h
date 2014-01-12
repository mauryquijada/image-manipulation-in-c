/*************************************************

utility funtions for array operations.

*************************************************/

#define SWAP(a,b) tempr=(a); (a)=(b); (b)=tempr
#define Pi 3.141592653589
#define Sqrt2 1.414213562

char fname[50];
FILE *fp;

double *alloc1dd(n)
int n;
{ int i;
  double *array;
  if ( (array = (double*)malloc(n * sizeof(double)) )==NULL)
    { printf("Unable to allocate memory for 1D double array...\n"); exit(0); }
  for (i=0; i<n; i++) array[i]=0.0;
  return array;
}

double **alloc2dd(m, n)
int m,n;
{ int i,j; 
  double **array;
  if ( (array = (double **) malloc(m * sizeof(double*)) )==NULL) 
    { printf("Unable to allocate memory for 2D float array...\n"); exit(0); }
  for (i=0; i<m; i++)    array[i]=alloc1dd(n);
  return array;
}

float *alloc1df(int n)
{ int i;
  float *array;
  if ( (array = (float*)malloc(n * sizeof(float)) )==NULL)
    { printf("Unable to allocate memory for 1D float array...\n"); exit(0); }
  for (i=0; i<n; i++) array[i]=0.0;
  return array;
}

float **alloc2df(int m, int n)
{ int i,j; 
  float **array;
  if ( (array = (float **) malloc(m * sizeof(float*)) )==NULL) 
    { printf("Unable to allocate memory for 2D float array...\n"); exit(0); }
  for (i=0; i<m; i++)  array[i]=alloc1df(n);
  return array;
}

float ***alloc3df(int l, int m, int n)
{ int i;
  float ***array;
  //  printf("Allocating 3D array (%d x %d x %d)\n",l,m,n);
  if ( (array = (float ***) malloc(l * sizeof(float**)) )==NULL) 
    { printf("Unable to allocate memory for 3D float array...\n"); exit(0); }
  for (i=0; i<l; i++)  array[i]=alloc2df(m,n);
  return array;
}

float ****alloc4df(int k, int l, int m, int n)
{ int i;
  float ****array;
  if ( (array = (float ****) malloc(k * sizeof(float***)) )==NULL) 
    { printf("Unable to allocate memory for 4D float array...\n"); exit(0); }
  for (i=0; i<k; i++)    array[i]=alloc3df(l,m,n);
  return array;
}

float *****alloc5df(int j, int k, int l, int m, int n)
{ int i;
  float *****array;
  if ( (array = (float *****) malloc(j * sizeof(float****)) )==NULL) 
    { printf("Unable to allocate memory for 5D float array...\n"); exit(0); }
  for (i=0; i<j; i++)    array[i]=alloc4df(k,l,m,n);
  return array;
}

float ******alloc6df(i, j, k, l, m, n)
int i,j,k,l,m,n;
{ int h;
  float ******array;
  if ( (array = (float ******) malloc(i * sizeof(float*****)) )==NULL) 
    { printf("Unable to allocate memory for 6D float array...\n"); exit(0); }
  for (h=0; h<i; h++)    array[h]=alloc5df(j,k,l,m,n); 
  return array;
}

float *******alloc7df(i, j, k, l, m, n, o)
int i,j,k,l,m,n,o;
{ int h;
  float *******array;
  if ( (array = (float *******) malloc(i * sizeof(float******)) )==NULL) 
    { printf("Unable to allocate memory for 7D float array...\n"); exit(0); }
  for (h=0; h<i; h++)    array[h]=alloc6df(j,k,l,m,n,o); 
  return array;
}


dealloc2df(array,m,n)
float **array;
int m,n;
{ int i,j;
  for (i=0; i<m; i++) free(array[i]);
  free(array);
}

dealloc3df(array,l,m,n)
float ***array;
int l,m,n;
{ int i;
  for (i=0; i<l; i++)
    dealloc2df(array[i],m,n);
  free(array);
}

dealloc4df(array,k,l,m,n)
float ****array;
int k,l,m,n;
{ int i;
  for (i=0; i<k; i++)
    dealloc3df(array[i],l,m,n);
  free(array);
}


dealloc5df(array,j,k,l,m,n)
float *****array;
int j,k,l,m,n;
{ int i;
  for (i=0; i<j; i++)
    dealloc4df(array[i],k,l,m,n);
  free(array);
}


dealloc6df(array,i,j,k,l,m,n)
float ******array;
int i,j,k,l,m,n;
{ int h;
  for (h=0; h<i; h++)
    dealloc5df(array[h],j,k,l,m,n);
  free(array);
}


int *alloc1di(n)
int n;
{ int i, *array;
  if ( (array = (int*)malloc(n * sizeof(int)) )==NULL)
    { printf("Unable to allocate memory for 1D int array...\n"); exit(0); }
  for (i=0; i<n; i++) array[i]=0.0;
  return array;
}

int **alloc2di(m, n)
int m,n;
{ int i,**array;
  if ( (array = (int **) malloc(m * sizeof(int*)) )==NULL) 
    { printf("Unable to allocate memory for 2D int array...\n"); exit(0); }
  for (i=0; i<m; i++)    array[i]=alloc1di(n);
  return array;
}


int ***alloc3di(l, m, n)
int l,m,n;
{ int i, ***array;
  if ( (array = (int ***) malloc(l * sizeof(int**)) )==NULL) 
    { printf("Unable to allocate memory for 3D int array...\n"); exit(0); }
  for (i=0; i<l; i++)    array[i]=alloc2di(m,n);
  return array;
}

int ****alloc4di(k, l, m, n)
int k,l,m,n;
{ int i, ****array;
  if ( (array = (int ****) malloc(k * sizeof(int***)) )==NULL) 
    { printf("Unable to allocate memory for 4D int array...\n"); exit(0); }
  for (i=0; i<k; i++)    array[i]=alloc3di(l,m,n);
  return array;
}

int *****alloc5di(j, k, l, m, n)
int j,k,l,m,n;
{ int i, *****array;
  if ( (array = (int *****) malloc(j * sizeof(int****)) )==NULL) 
    { printf("Unable to allocate memory for 5D int array...\n"); exit(0); }
  for (i=0; i<j; i++)    array[i]=alloc4di(k,l,m,n);
  return array;
}

int ******alloc6di(i, j, k, l, m, n)
int i,j,k,l,m,n;
{ int h, ******array;
  if ( (array = (int ******) malloc(i * sizeof(int*****)) )==NULL) 
    { printf("Unable to allocate memory for 6D int array...\n"); exit(0); }
  for (h=0; h<i; h++)    array[h]=alloc5di(j,k,l,m,n); 
  return array;
}

int *******alloc7di(i, j, k, l, m, n, o)
int i,j,k,l,m,n,o;
{ int h, *******array;
  if ( (array = (int *******) malloc(i * sizeof(int******)) )==NULL) 
    { printf("Unable to allocate memory for 7D int array...\n"); exit(0); }
  for (h=0; h<i; h++)    array[h]=alloc6di(j,k,l,m,n,o); 
  return array;
}


dealloc2di(array,m,n)
int **array;
int m,n;
{ int i;
  for (i=0; i<m; i++) free(array[i]);
  free(array);
}

dealloc3di(array,l,m,n)
int ***array;
int l,m,n;
{ int i;
  for (i=0; i<l; i++) dealloc2di(array[i],m,n);
  free(array);
}

dealloc4di(array,k,l,m,n)
int ****array;
int k,l,m,n;
{ int i;
  for (i=0; i<k; i++) dealloc3di(array[i],l,m,n);
  free(array);
}


dealloc5di(array,j,k,l,m,n)
int *****array;
int j,k,l,m,n;
{ int i;
  for (i=0; i<j; i++) dealloc4di(array[i],k,l,m,n);
  free(array);
}

dealloc6di(array,i,j,k,l,m,n)
int ******array;
int i,j,k,l,m,n;
{ int h;
  for (h=0; h<i; h++) dealloc5di(array[h],j,k,l,m,n);
  free(array);
}

unsigned char *alloc1db(n)
int n;
{ unsigned char i, *array;
  if ( (array = (unsigned char*)malloc(n * sizeof(unsigned char)) )==NULL)
    { printf("Unable to allocate memory for 1D int array...\n"); exit(0); }
  for (i=0; i<n; i++) array[i]=0.0;
  return array;
}

unsigned char **alloc2db(m, n)
int m,n;
{ unsigned char i,**array;
  if ( (array = (unsigned char **) malloc(m * sizeof(unsigned char*)) )==NULL) 
    { printf("Unable to allocate memory for 2D int array...\n"); exit(0); }
  for (i=0; i<m; i++)    array[i]=alloc1db(n);
  return array;
}


unsigned char ***alloc3db(l, m, n)
int l,m,n;
{ unsigned char i, ***array;
  if ( (array = (unsigned char ***) malloc(l * sizeof(unsigned char**)) )==NULL) 
    { printf("Unable to allocate memory for 3D int array...\n"); exit(0); }
  for (i=0; i<l; i++)    array[i]=alloc2db(m,n);
  return array;
}

unsigned char ****alloc4db(k, l, m, n)
int k,l,m,n;
{ unsigned char i, ****array;
  if ( (array = (unsigned char ****) malloc(k * sizeof(unsigned char***)) )==NULL) 
    { printf("Unable to allocate memory for 4D int array...\n"); exit(0); }
  for (i=0; i<k; i++)    array[i]=alloc3db(l,m,n);
  return array;
}

unsigned char *****alloc5db(j, k, l, m, n)
int j,k,l,m,n;
{ unsigned char i, *****array;
  if ( (array = (unsigned char *****) malloc(j * sizeof(unsigned char****)) )==NULL) 
    { printf("Unable to allocate memory for 5D int array...\n"); exit(0); }
  for (i=0; i<j; i++)    array[i]=alloc4db(k,l,m,n);
  return array;
}

unsigned char ******alloc6db(i, j, k, l, m, n)
int i,j,k,l,m,n;
{ unsigned char h, ******array;
  if ( (array = (unsigned char ******) malloc(i * sizeof(unsigned char*****)) )==NULL) {
    printf("Unable to allocate memory for 6D int array...\n"); 
    exit(0); 
  }
  for (h=0; h<i; h++)    array[h]=alloc5db(j,k,l,m,n); 
  return array;
}


dealloc2db(array,m,n)
unsigned char **array;
int m,n;
{ int i;
  for (i=0; i<m; i++) free(array[i]);
  free(array);
}

dealloc3db(array,l,m,n)
unsigned char ***array;
int l,m,n;
{ int i;
  for (i=0; i<l; i++) dealloc2db(array[i],m,n);
  free(array);
}

dealloc4db(array,k,l,m,n)
unsigned char ****array;
int k,l,m,n;
{ int i;
  for (i=0; i<k; i++) dealloc3db(array[i],l,m,n);
  free(array);
}


dealloc5db(array,j,k,l,m,n)
unsigned char *****array;
int j,k,l,m,n;
{ int i;
  for (i=0; i<j; i++) dealloc4db(array[i],k,l,m,n);
  free(array);
}

dealloc6db(array,i,j,k,l,m,n)
unsigned char ******array;
int i,j,k,l,m,n;
{ int h;
  for (h=0; h<i; h++) dealloc5db(array[h],j,k,l,m,n);
  free(array);
}

write_image(filename,tmp,m,n)
float **tmp;
char filename[];
int m,n;
{ int i,j,k,l,s;
  float v, min, max;
  unsigned char w;
  FILE *fp;

/*  printf("\nDisplay black/white image %s of size (%d, %d).\n",filename,m,n); */

  min=9e9; max=-min;
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      { v=tmp[i][j]; if (min>v) min=v; if (max<v) max=v;  }
  v=255.0/(max-min);

  printf("Write image:  min=%f, max=%f, v=%f\n", min,max,v); 

  if ( (fp = fopen(filename, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",filename);
      exit(0);
    }
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", n,m, 255);
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      putc(w=(tmp[i][j]-min)*v,fp);
  fclose(fp);      
}

display_image(fname,tmp,m,n)
     float **tmp;
     int m,n;
     char *fname;
{ int i,j;
  float min,max,v;
  unsigned char w;
  FILE *fp;

  strcat(fname,".pgm");
  printf("\nDisplay 2D image: '%s'...\n",fname);
  min=9e9; max=-min;
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      { v=tmp[i][j]; if (min>v) min=v; if (max<v) max=v; }
  v=255/(max-min);

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open %s for writing, exiting.\n",fname);
      exit(0);
    }
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", n,m, 255);
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      putc(w=(tmp[i][j]-min)*v,fp);
  fclose(fp);      
}



print2d_1(a,m,n)
     int m,n;
     float **a;
{
  int i,j;
  for (i=0; i<m; i++)
    {
      for (j=0; j<n; j++)
	printf("%8.4f  ",a[i][j]);
      printf("\n");
    }
}

print2d_2(a,b,m,n)
     int m,n;
     float **a, **b;
{
  int i,j;
  for (i=0; i<m; i++)
    {
      for (j=0; j<n; j++)
	printf("%7.4f ",a[i][j]);
      printf("    ");
      for (j=0; j<n; j++)
	printf("%7.4f  ",b[i][j]);
      printf("\n");
    }
}

print4d(a,m,n,M,N)
     int m,n,M,N;
     float ****a;
{
  int i,j,I,J;
/*  printf("print4d: %d %d %d %d\n",m,n,M,N); */
  for (I=0; I<M; I++)
    {
      for (i=0; i<m; i++)
	{
	  for (J=0; J<N; J++)
	    {
	      for (j=0; j<n; j++)
		printf("%6.3f ",a[i][j][I][J]);
	      printf("  ");
	    }
	  printf("\n");
	}
      printf("\n");
    }
}




display3df(fname,data,N,m,n,bd)
float ***data;
int m,n,N;
char fname[];
{
  unsigned char w;
  int i,j,k,l,I,J,K,mc,nc;
  float min,max,u,v,**image;

  strcat(fname,".pgm");
  printf("Display 3D image: %s\n",fname);
  min=9e9; max=-min;
  for (J=0; J<N; J++)
    for (i=0; i<m; i++)
      for (j=0; j<n; j++)
	{ v=data[J][i][j];
	  if (min>v) min=v;  if (max<v) max=v;
	}
  v=255.0/(max-min);
  /*  printf("Display_3D: min=%f, max=%f, v=%f\n",min,max,v);  */

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }

  mc=bd+m+bd;  nc=bd+N*(n+bd); 
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
  for (k=0; k<mc; k++)
    for (l=0; l<nc; l++)
      {
	I=k/(m+bd); i=k-I*(m+bd)-bd;
	J=l/(n+bd); j=l-J*(n+bd)-bd;
	if (i<0 || j<0) w=255;
	else  w=(data[J][i][j]-min)*v;
	putc(w,fp);
      }

  fclose(fp);      
}

display4df(fname,data,m,n,M,N,order,bd)
float ****data;
int m,n,M,N,order;
char fname[];
{
  FILE *fp;
  unsigned char w;
  int i,j,k,l,I,J,K,mc,nc;
  float min,max,u,v,**image;

  //  strcat(fname,".pgm");
  printf("Display 4D image: %s\n",fname);
  min=9e9; max=-min;
  for (I=0; I<M; I++)
    for (J=0; J<N; J++)
      for (i=0; i<m; i++)
	for (j=0; j<n; j++)
	  { v=data[i][j][I][J];
	    if (min>v) min=v;  if (max<v) max=v;
	  }
  v=255.0/(max-min);
  printf("Display_4D: min=%f, max=%f, v=%f\n",min,max,v);  

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }
  if (order)
    { mc=bd+M*(m+bd);  nc=bd+N*(n+bd); 
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(m+bd); i=k-I*(m+bd)-bd;
	    J=l/(n+bd); j=l-J*(n+bd)-bd;
	    if (i<0 || j<0) w=255;
	    else  w=(data[i][j][I][J]-min)*v;
	    putc(w,fp);
	  }
    }
  else
    { mc=bd+m*(M+bd);  nc=bd+n*(N+bd); 
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(M+bd); i=k-I*(M+bd)-bd;
	    J=l/(N+bd); j=l-J*(N+bd)-bd;
	    if (i<0 || j<0) w=255;
	    else  w=(data[I][J][i][j]-min)*v;
	    putc(w,fp);
	  }
    }

  fclose(fp);      
}


display5df(fname,data,K,m,n,M,N,order,bd)
float *****data;
int m,n,M,N,K,order;
char fname[];
{
  FILE *fp;
  unsigned char w;
  int i,j,k,l,I,J,ik,mc,nc;
  float min,max,u,v,**image;

  strcat(fname,".pgm");
  printf("Display D image: %s (%d %d %d %d %d)\n",fname,K,m,n,M,N);
  min=9e9; max=-min;
  for (k=0; k<K; k++)
    for (I=0; I<M; I++)
      for (J=0; J<N; J++)
	for (i=0; i<m; i++)
	  for (j=0; j<n; j++)
	    { v=data[k][i][j][I][J];
	      if (min>v) min=v;  if (max<v) max=v;
	    }
  v=255.0/(max-min);
  printf("Display_5D: min=%f, max=%f, v=%f\n",min,max,v);  

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }
  if (order)
    { mc=bd+M*(m+bd);  nc= K*(bd+N*(n+bd));
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(m+bd); i=k-I*(m+bd)-bd; ik=l/(bd+N*(n+bd));
	    J=(l-ik*(bd+N*(n+bd)))/(n+bd); j=l-ik*(bd+N*(n+bd))-J*(n+bd)-bd;
	    //	    printf("%d %d %d %d\n",i,j,I,J);
	    if (i<0 || j<0) w=255;
	    else  w=(data[ik][i][j][I][J]-min)*v;
	    putc(w,fp);
	  }
    }
  else
    { mc=bd+m*(M+bd);  nc=K*(bd+n*(N+bd));
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(M+bd); i=k-I*(M+bd)-bd; ik=l/(bd+n*(N+bd));
	    J=(l-ik*(bd+n*(N+bd)))/(N+bd); j=l-ik*(bd+n*(N+bd))-J*(N+bd)-bd;
	    if (i<0 || j<0) w=255;
	    else  w=(data[ik][I][J][i][j]-min)*v;
	    putc(w,fp);
	  }
    }

  fclose(fp);      


}


display6df_old(fname,data,p,q,P,Q,PP,QQ,order)
float ******data;
int p,q,P,Q,PP,QQ,order;
char fname[];
{
  unsigned char w;
  int i,j,k,l,I,J,K,II,JJ,mc,nc,Wi,Wj,Di,Dj;
  int m,n,M,N,MM,NN;
  int bd1=1,bd2=3;
  float min,max,u,v,**image,******temp;

  printf("Display6D file: %s, [%d %d %d %d %d %d], order=%d\n",fname,p,q,P,Q,PP,QQ,order);

  if (order)
    { MM=p; NN=q; M=P; N=Q; m=PP; n=QQ;
      temp=alloc6df(MM,NN,M,N,m,n);
    }
  else
    { MM=PP; NN=QQ; M=P; N=Q; m=p; n=q;
      temp=alloc6df(m,n,M,N,MM,NN);
    }

  min=9e9; max=-min;
  for (II=0; II<MM; II++)
    for (JJ=0; JJ<NN; JJ++)
      for (I=0; I<M; I++)
	for (J=0; J<N; J++)
	  for (i=0; i<m; i++)
	    for (j=0; j<n; j++)
	      { 
		if (order)
		  v=temp[II][JJ][I][J][i][j]=data[II][JJ][I][J][i][j];
		else
		  v=temp[i][j][I][J][II][JJ]=data[i][j][I][J][II][JJ];
		if (min>v) min=v;  if (max<v) max=v;
	      }
  v=255.0/(max-min);
  //  printf("Display_6D: min=%f, max=%f, v=%f\n",min,max,v);  

  strcat(fname,".pgm");
  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }
  mc=bd2+MM*(bd2+M*(m+bd1)-bd1);  nc=bd2+NN*(bd2+N*(n+bd1)-bd1);
  printf("Dimensions of input: (%d %d)x(%d %d)x(%d %d)\n",m,n,M,N,MM,NN);
  printf("Dimensions of output: (%d %d)\n",mc,nc);

  fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);

  Di=bd2+M*(m+bd1)-bd1; Dj=bd2+N*(n+bd1)-bd1;
  //  printf("Di=%d, Dj=%d\n",Di,Dj);

  for (k=0; k<mc; k++)
    for (l=0; l<nc; l++)
      {
	w=160;
	II=k/Di;  Wi=k-II*Di-bd2; 
	if (Wi >= 0) { I=Wi/(m+bd1); i=Wi-I*(m+bd1); } 
	JJ=l/Dj; Wj=l-JJ*Dj-bd2;
	if (Wj >= 0) 
 	  { J=Wj/(n+bd1); j=Wj-J*(n+bd1); } 
	if (Wi>=0 && Wj>=0 && i<m && j<n)
	  if (order)
	    w=(temp[II][JJ][I][J][i][j]-min)*v;  
	  else
	    w=(temp[i][j][I][J][II][JJ]-min)*v;  
  	putc(w,fp);
      }
  fclose(fp);      
}


display6df(fname,data,p,q,P,Q,PP,QQ,order)
float ******data;
int p,q,P,Q,PP,QQ,order;
char fname[];
{
  unsigned char w;
  int i,j,k,l,I,J,K,II,JJ,L,mc,nc,Wi,Wj,Di,Dj;
  int m,n,M,N,MM,NN,LL;
  int bd1=1,bd2=3;
  float min,max,u,v;

  printf("Display6D file: %s, [%d %d %d %d %d %d], order=%d\n",fname,p,q,P,Q,PP,QQ,order);

  min=9e9; max=-min;
  for (II=0; II<PP; II++)
    for (JJ=0; JJ<QQ; JJ++)
      for (I=0; I<P; I++)
	for (J=0; J<Q; J++)
	  for (i=0; i<p; i++)
	    for (j=0; j<q; j++)
	      { v=data[i][j][I][J][II][JJ];
		if (min>v) min=v;  if (max<v) max=v;
	      }
  v=255.0/(max-min);
  printf("Display_6D: min=%f, max=%f, v=%f\n",min,max,v); 

  if (order)
    { MM=p; NN=q; M=P; N=Q; m=PP; n=QQ;    }
  else
    { MM=PP; NN=QQ; M=P; N=Q; m=p; n=q;    }

  //  strcat(fname,".pgm"); 
  //  printf("FILEname: %s\n",fname); pause();

  if ( (fp = fopen(fname, "w")) == NULL) 
    { printf("Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }

  mc=bd2+MM*(bd2+M*(m+bd1)-bd1);  nc=bd2+NN*(bd2+N*(n+bd1)-bd1);
  printf("Dimensions of input: (%d %d)x(%d %d)x(%d %d)\n",m,n,M,N,MM,NN);
  printf("Dimensions of output: (%d %d)\n",mc,nc);
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);

  Di=bd2+M*(m+bd1)-bd1; Dj=bd2+N*(n+bd1)-bd1;
  //  printf("Di=%d, Dj=%d\n",Di,Dj);

  for (k=0; k<mc; k++)
    for (l=0; l<nc; l++)
      {
	w=200;
	II=k/Di;  Wi=k-II*Di-bd2; 
	if (Wi >= 0) { I=Wi/(m+bd1); i=Wi-I*(m+bd1); } 
	JJ=l/Dj; Wj=l-JJ*Dj-bd2;
	if (Wj >= 0) { J=Wj/(n+bd1); j=Wj-J*(n+bd1); } 
	if (Wi>=0 && Wj>=0 && i<m && j<n)
	  if (order)
	    w=(data[II][JJ][I][J][i][j]-min)*v;  
	  else
	    w=(data[i][j][I][J][II][JJ]-min)*v;  
  	putc(w,fp);
      }
  fclose(fp);      
}


display7df(fname,data,p,q,P,Q,PP,QQ,RR,order)
float *******data;
int p,q,P,Q,PP,QQ,RR,order;
char fname[];
{
  unsigned char w;
  int i,j,k,l,I,J,K,II,JJ,L,mc,nc,Wi,Wj,Di,Dj,DI,DJ;
  int m,n,M,N,MM,NN,LL;
  int bd1=1, bd2=3, bd3=3;
  float min,max,u,v;

  printf("Display6D file: %s, [%d %d %d %d %d %d], order=%d\n",fname,p,q,P,Q,PP,QQ,order);

  min=9e9; max=-min;
  for (L=0; L<RR; L++)
    for (II=0; II<PP; II++)
      for (JJ=0; JJ<QQ; JJ++)
	for (I=0; I<P; I++)
	  for (J=0; J<Q; J++)
	    for (i=0; i<p; i++)
	      for (j=0; j<q; j++)
		{ v=data[i][j][I][J][II][JJ][L];
		  if (min>v) min=v;  if (max<v) max=v;
		}
  if (max>min) v=255.0/(max-min); else v=1;
  printf("Display_7D: min=%f, max=%f, v=%f\n",min,max,v);  

  if (order)
    { LL=p; MM=q; NN=P; M=Q; N=PP; m=QQ; n=RR;    }
  else
    { LL=RR; MM=PP; NN=QQ; M=P; N=Q; m=p; n=q;    }

  //  strcat(fname,".pgm");
  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }

  Di=bd2+M*(m+bd1)-bd1; Dj=bd2+N*(n+bd1)-bd1;
  //  printf("Di=%d, Dj=%d\n",Di,Dj);

  DI=bd2+MM*Di; DJ=bd2+NN*Dj;
  mc=DI; nc=LL*DJ;

  printf("Dimensions of input: (%d %d)x(%d %d)x(%d %d)x%d\n",p,q,P,Q,PP,QQ,RR);
  printf("Dimensions of output: (%d %d)\n",mc,nc);

  fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);

  for (k=0; k<mc; k++)
    for (l=0; l<nc; l++)
      {
	w=160;
	II=k/Di;  Wi=k-II*Di-bd2; 
	if (Wi >= 0) { I=Wi/(m+bd1); i=Wi-I*(m+bd1); } 

	L=l/DJ; JJ=(l-L*DJ)/Dj; Wj=l-L*DJ-JJ*Dj-bd2;
	if (Wj >= 0) { J=Wj/(n+bd1); j=Wj-J*(n+bd1); } 

	//	printf("i=%d j=%d I=%d J=%d II=%d jj=%d L=%d\n",i,j,I,J,II,JJ,L);

	if (Wi>=0 && Wj>=0 && i<m && j<n)
	  if (order)
	    w=(data[L][II][JJ][I][J][i][j]-min)*v;  
	  else
	    w=(data[i][j][I][J][II][JJ][L]-min)*v;  
  	putc(w,fp);
      }
  fclose(fp);  
}


display4di(fname,data,m,n,M,N,order,bd)
int ****data;
int m,n,M,N,order;
char fname[];
{
  FILE *fp;
  unsigned char w;
  int i,j,k,l,I,J,K,mc,nc;
  float min,max,u,v,**image;

  strcat(fname,".pgm");
  printf("\nDisplay 4D image: %s\n",fname);
  min=9e9; max=-min;
  for (I=0; I<M; I++)
    for (J=0; J<N; J++)
      for (i=0; i<m; i++)
	for (j=0; j<n; j++)
	  { v=data[i][j][I][J];
	    if (min>v) min=v;  if (max<v) max=v;
	  }
  v=255.0/(max-min);

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }
  
  if (order)          /* (MxN) subimages of size (mxn) */
    { mc=bd+M*(m+bd);  nc=bd+N*(n+bd); 
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(m+bd); i=k-I*(m+bd)-bd;
	    J=l/(n+bd); j=l-J*(n+bd)-bd;
	    if (i<0 || j<0) w=255;
	    else  w=(data[i][j][I][J]-min)*v;
	    putc(w,fp);
	  }
    }
  else                /* (mxn) subimages of size (MxN) */
    { mc=bd+m*(M+bd);  nc=bd+n*(N+bd); 
      fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);
      for (k=0; k<mc; k++)
	for (l=0; l<nc; l++)
	  {
	    I=k/(M+bd); i=k-I*(M+bd)-bd;
	    J=l/(N+bd); j=l-J*(N+bd)-bd;
	    if (i<0 || j<0) w=255;
	    else  w=(data[I][J][i][j]-min)*v;
	    putc(w,fp);
	  }
    }

  fclose(fp);      
}

display4db(fname,data,m,n,M,N,bd)
unsigned char ****data;
int m,n,M,N;
char fname[];
{
  FILE *fp;
  unsigned char w;
  int i,j,k,l,I,J,K,mc,nc;
  float min,max,u,v,**image;

  strcat(fname,".pgm");
  min=9e9; max=-min;
  for (I=0; I<M; I++)
    for (J=0; J<N; J++)
      for (i=0; i<m; i++)
	for (j=0; j<n; j++)
	  { v=data[i][j][I][J];
	    if (min>v) min=v;  if (max<v) max=v;
	  }
  v=255.0/(max-min);
/*  printf("Display_4D: min=%f, max=%f, v=%f\n",min,max,v);  */

  if ( (fp = fopen(fname, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",fname);
      exit(0);
    }

  mc=bd+M*(m+bd);  nc=bd+N*(n+bd); 
/*  printf("[%d %d] = (%d %d) x (%d %d)\n",mc,nc,M,N,m,n);   */
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", nc,mc, 255);

  for (k=0; k<mc; k++)
    for (l=0; l<nc; l++)
      {
	I=k/(m+bd); i=k-I*(m+bd)-bd;
	J=l/(n+bd); j=l-J*(n+bd)-bd;
	if (i<0 || j<0) w=255;
	else  w=(data[i][j][I][J]-min)*v;
	putc(w,fp);
      }
  fclose(fp);      
}


pause()
{ int k;
  printf("\npaused... enter 1 to continue, enter 0 to quit: ");
  scanf("%d",&k);
  if(!k) exit(0);
}

msg_pause(char *msg)
{ 
  int k;
  printf("\n%s",msg);
  printf("\npaused... enter 1 to continue, enter 0 to quit: ");
  scanf("%d",&k);
  if(!k) exit(0);
}


prtvctr(v,n)   // print an n by 1 vector 
float *v;
int n;
{ int i;
  for (i=0; i<n; i++)
    printf("%7.3f ",v[i]);
  printf("\n");
}


prtmtrx(a,m,n) // print an n by n matrix 
float **a;
int m,n;
{ int i,j;
  for (i=0; i<m; i++){
    for (j=0; j<n; j++){
      printf("%7.3f ",a[i][j]);
    }
    printf("\n");
  }
}

mtxvtr(a,v,u,m,n)    // u[m]=a[m,n] v[n]
     float **a,*v,*u;
     int m,n;
{
  int i,j; 
  for (i=0; i<m; i++)
    { u[i]=0;
      for (j=0; j<n; j++)
	u[i]+=a[i][j]*v[j]; 
    }
}

mtxmtx(a,b,c,m,l,n,flg)   
float **a,**b,**c;
int m,n,l,flg;
{
  int i,j,k;
  switch (flg){
  case 0:      // c[m][n]=a[m][l]*b[l][n]   c=a*b
    for (i=0; i<m; i++)
      for (j=0; j<n; j++)
	{ c[i][j]=0;
	  for (k=0; k<l; k++)
	    c[i][j]+=a[i][k]*b[k][j]; 
	}
    break;
  case 1:     // c[m][n]=a[l][m]*b[l][n]   c=a^t*b
    for (i=0; i<m; i++)
      for (j=0; j<n; j++)
	{ c[i][j]=0;
	  for (k=0; k<l; k++)
	    c[i][j]+=a[k][i]*b[k][j]; 
	}
    break;
  case 2:     // c[m][n]=a[m][l]*b[n][l]   c=a*b^t
    for (i=0; i<m; i++)
      for (j=0; j<n; j++)
	{ c[i][j]=0;
	  for (k=0; k<l; k++)
	    c[i][j]+=a[i][k]*b[j][k]; 
	}
  }
}


eof_err()  // print end of file error message and exit 
{ printf("Unexpected end of file, exiting. \n");  exit(0); }

int getword(FILE *fp, char *word)  
{              
  int i=0,cha=' ';
  short end=0;

  do {   // Eliminate White Space and comments (from # to end of line) 
    cha=fgetc(fp);   
    if (cha=='#') 
      { do cha=fgetc(fp); while (!(cha=='\n')); }
  } while (isspace(cha) && (cha!=EOF));

  if (cha==EOF) return -1;
  else  // get chars until a whitespace or End of File
    do
      { word[i++]=cha; cha=fgetc(fp); }	// Get Single Word 
    while ( !(isspace(cha)) && (cha!=EOF) );
  
  if (cha==EOF) end=1;  // if end of the file then we are done reading chars 
  
  word[i]='\0';
  return end;  
}


float ***read_color_image(char *fname, int *m, int *n)
{
  int c,i,j,k,Max;
  float ***img;
  char word[10];
  FILE *fp;
  char magic[4];

  if ( (fp = fopen(fname, "r")) == NULL) {
    printf("Unable to open file: %s for reading, exiting.\n", fname);
    exit(0);
  }
  if (getword(fp,word)!=0) eof_err();
  strcpy(magic,word);

  if ( (strcmp(magic,"P5")!=0) && (strcmp(magic,"P6")!=0) ) {
    printf("\nBad file type, use raw grayscale (pgm) or raw color (ppm) file.\n");
    exit(0);
  }
  if (getword(fp,word)!=0) eof_err();  *n=atoi(word);
  if (getword(fp,word)!=0) eof_err();  *m=atoi(word);
  if (getword(fp,word)!=0) eof_err();  Max=atoi(word);

  //  printf("read black/white image: %s (%d x %d)\n",fname,*m,*n);  

  img=alloc3df(3,*m,*n);

  for (i=0; i<*m; i++)
    for (j=0; j<*n; j++) 
      for (k=0; k<3; k++) {
	c=fgetc(fp); if (c==EOF) eof_err();
	img[k][i][j]=c; 
      }

  fclose(fp); 
  return img;
}

float **read_bw_image(char *fname, int *m, int *n)
{
  int c,i,j,Max;
  float **img;
  char word[10];
  FILE *fp;
  char magic[4];

  if ( (fp = fopen(fname, "r")) == NULL) {
    printf("Unable to open file: %s for reading, exiting.\n", fname);
    exit(0);
  }

  if (getword(fp,word)!=0) eof_err();
  strcpy(magic,word);

  if ( (strcmp(magic,"P5")!=0) && (strcmp(magic,"P6")!=0) ) {
    printf("\nBad file type, use raw grayscale (pgm) or raw color (ppm) file.\n");
    exit(0);
  }
  if (getword(fp,word)!=0) eof_err();  *n=atoi(word);
  if (getword(fp,word)!=0) eof_err();  *m=atoi(word);
  if (getword(fp,word)!=0) eof_err();  Max=atoi(word);

  //  printf("\nread black/white image: %s (%d x %d)\n",fname,*m,*n);  

  img=alloc2df(*m,*n);

  for (i=0; i<*m; i++)
    for (j=0; j<*n; j++) {
      c=fgetc(fp); if (c==EOF) eof_err();
      img[i][j]=c; 
    }

  fclose(fp); 
  return img;
}

write_color_image(filename,image,m,n,s)
float ***image;
char filename[];
int m,n,s;
{ int i,j,k,l;
  float v, min, max, ***Image;
  unsigned char w;
  FILE *fp;

  //  printf("\nDisplay color image %s of size (%d, %d).\n",filename,m,n); 
  min=9e9; max=-min;
  for (k=0; k<3; k++)
    for (i=0; i<m; i++)
      for (j=0; j<n; j++)
	{ v=image[k][i][j]; if (min>v) min=v; if (max<v) max=v;  }
  v=254.99/(max-min);
  for (k=0; k<3; k++)
    for (i=0; i<m; i++)
      for (j=0; j<n; j++) 
	image[k][i][j]=v*(image[k][i][j]-min);
  printf("Write color image:  min=%f, max=%f, v=%f\n", min,max,v); 

  if ( (fp = fopen(filename, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",filename);
      exit(0);
    }
  fprintf(fp,"%s\n%d %d\n%d\n", "P6", s*n,s*m, 255);
  for (i=0; i<m; i++) {
    for (k=0; k<s; k++)
      for (j=0; j<n; j++)
  
	for (l=0; l<s; l++) {

	  putc(w=image[0][i][j],fp);
	  putc(w=image[1][i][j],fp);
	  putc(w=image[2][i][j],fp);
	}
}
  fclose(fp);      
}

write_bw_image(filename,image,m,n,s)
float **image;
char *filename;
int m,n,s;
{ int i,j,k,l;
  float v, min, max;
  unsigned char w;
  FILE *fp;

  printf("\nWrite black/white image %s of size (%d, %d).\n",filename,m,n); 

  min=9e9; max=-min;
  for (i=0; i<m; i++)
    for (j=0; j<n; j++)
      { v=image[i][j]; if (min>v) min=v; if (max<v) max=v;  }
  v=254.99/(max-min);
  printf("Write image:  min=%f, max=%f, v=%f\n", min,max,v); 
  if ( (fp = fopen(filename, "w")) == NULL) 
    { fprintf(stderr, "Unable to open image %s for writing, exiting.\n",filename);
      exit(0);
    }
  fprintf(fp,"%s\n%d %d\n%d\n", "P5", s*n,s*m, 255);
  for (i=0; i<m; i++)
    for (l=0; l<s; l++)
      for (j=0; j<n; j++)
	for (k=0; k<s; k++)
	  putc(w=(image[i][j]-min)*v,fp);
  fclose(fp);      
}
