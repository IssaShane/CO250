#include<iostream>
using namespace std;
int main()
{
   int i,j,k,n;
   float a[100][200],t;
   cout<<"Enter order of matrix-";
   cin>>n;
   cout<<"Enter elements of matrix"<<endl;
   for(i=0;i<n;i++)
      for(j=0;j<n;j++)
         cin>>a[i][j];
   for(i=0;i<n;i++)
   {
      for(j=n;j<2*n;j++)
      {
          if(i==j-n)
             a[i][j]=1;
         else
             a[i][j]=0;
       }
   }
   for(i=0;i<n;i++)
   {
      t=a[i][i];
      for(j=i;j<2*n;j++)
          a[i][j]=a[i][j]/t;
      for(j=0;j<n;j++)
      {
         if(i!=j)
         {
            t=a[j][i];
            for(k=0;k<2*n;k++)
                a[j][k]=a[j][k]-t*a[i][k];
          }
      }
   }
   cout<<"\n\nInverse matrix\n\n";
   for(i=0;i<n;i++)
   {
      for(j=n;j<2*n;j++)
         cout<<"\t"<<a[i][j];
      cout<<"\n";
    }
return 0;
}