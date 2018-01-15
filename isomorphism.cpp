#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <string>  
using namespace std;

int main(){
  vector<vector<int> > reference_matrix;
  vector<vector<int> > combinational_matrix;
  int graph_no=0,row=0,no_vertices=0;

  std::fstream str;
  str.open("input.txt", std::fstream::in);
  int lines;
  bool ref=true,not_isomorphic=false;
  int new_line=0;
  while(str >> lines){
  if(new_line==0){
    row=1;
    graph_no++;
    no_vertices=lines;
    if(reference_matrix.size()!=0){
      ref=false;
    }
    new_line=lines;
  }
  else{
     vector<int> temp(no_vertices+1,0);
     if(ref){
     if(reference_matrix.size()==0){
       vector<int> temp(no_vertices+1,0);
       temp[0]=graph_no;
       for(int i=1;i<temp.size();i++)
          temp[i]=i;
       reference_matrix.push_back(temp);
     }
     temp[0]=row++;
     while(lines%10!=0){
        temp[lines%10]=1;
        lines/=10;
     }
     reference_matrix.push_back(temp);
     }
     else{
     if(combinational_matrix.size()==0){
       vector<int> temp(no_vertices+1,0);
       temp[0]=graph_no;
       for(int i=1;i<temp.size();i++)
          temp[i]=i;
       combinational_matrix.push_back(temp);
     }
     temp[0]=row++;
     while(lines%10!=0){
        temp[lines%10]=1;
        lines/=10;
     }
     combinational_matrix.push_back(temp);      
     }
     new_line--;       
  }
  if(combinational_matrix.size()==no_vertices+1){
  cout<<"Reference matrix before swapping..."<<endl;
  for(int i=0;i<reference_matrix.size();i++)
  {
     for(int j=0;j<reference_matrix[i].size();j++)
     {
         cout<<reference_matrix[i][j]<<" ";
     }
     cout<<endl;
  }
  cout<<"Combinational matrix before swapping..."<<endl;
  for(int i=0;i<combinational_matrix.size();i++)
  {
     for(int j=0;j<combinational_matrix[i].size();j++)
     {
         cout<<combinational_matrix[i][j]<<" ";
     }
     cout<<endl;
  }

  vector<string> swap_history;
  for(int i=1;i<combinational_matrix.size();i++)
  {
     vector<int>sub_combinational_matrix (&combinational_matrix[i][1],&combinational_matrix[i][combinational_matrix[0].size()]);
     vector<int>sub_reference_matrix (&reference_matrix[i][1],&reference_matrix[i][reference_matrix[0].size()]);
     if(!equal(sub_reference_matrix.begin(), sub_reference_matrix.end(), sub_combinational_matrix.begin())){
       int min_mismatch=0,index_of_min_match=i;
       for(int j=0;j<sub_combinational_matrix.size();j++)
       {
           if(sub_combinational_matrix[j]!=sub_reference_matrix[j]){
              min_mismatch++;
           }
           if(min_mismatch>1)
              break;
       }
       for(int j=i+1;j<combinational_matrix.size();j++)
       {
          vector<int>sub_combinational_matrix1 (&combinational_matrix[j][1],&combinational_matrix[j][combinational_matrix[0].size()]);
          if(equal(sub_reference_matrix.begin(), sub_reference_matrix.end(), sub_combinational_matrix1.begin())){
             min_mismatch=0;
             index_of_min_match=j;
             break;
          }
          else
          {
             int temp_min_mismatch=1;
             for(int x=0;x<sub_combinational_matrix1.size();x++)
             {
                if(sub_combinational_matrix1[x]!=sub_reference_matrix[x])
                   temp_min_mismatch++;
                if(temp_min_mismatch>1)
                   break;
                if(x==sub_combinational_matrix1.size()-1 && temp_min_mismatch<min_mismatch)
                   index_of_min_match=j;
             }             
          }
       }

       
       //cout<<"swapping rows for i="<<i<<" :"<<i<<" & "<<index_of_min_match<<endl;
       for(int m=0;m<swap_history.size();m++)
           if(swap_history[m]==to_string(i)+to_string(index_of_min_match) || swap_history[m]==to_string(index_of_min_match)+to_string(i)){
              cout<<"Graph "<<reference_matrix[0][0]<<" & "<<combinational_matrix[0][0]<<" are NOT ISOMORPHIC"<<endl;
              not_isomorphic=true;
              break;
           }
       if(not_isomorphic)
         break;
       string temp=to_string(i)+to_string(index_of_min_match);
       swap_history.push_back(temp);
       temp=to_string(index_of_min_match)+to_string(i);
       swap_history.push_back(temp);
       for(int j=0;j<combinational_matrix[0].size();j++)
       {
          int vertex=combinational_matrix[index_of_min_match][j];
          combinational_matrix[index_of_min_match][j]=combinational_matrix[i][j];
          combinational_matrix[i][j]=vertex;
       }
       for(int j=0;j<combinational_matrix[0].size();j++)
       {
          int vertex=combinational_matrix[j][index_of_min_match];
          combinational_matrix[j][index_of_min_match]=combinational_matrix[j][i];
          combinational_matrix[j][i]=vertex;
       }
/*
  for(int m=0;m<combinational_matrix.size();m++)
  {
     for(int n=0;n<combinational_matrix[i].size();n++)
     {
         cout<<combinational_matrix[m][n]<<" ";
     }
     cout<<endl;
  }
*/


       int swap_column1=0,swap_column2=0;
       vector<int>sub_combinational_matrix1 (&combinational_matrix[i][1],&combinational_matrix[i][combinational_matrix[0].size()]);
       if(!equal(sub_reference_matrix.begin(), sub_reference_matrix.end(), sub_combinational_matrix1.begin())){	
         for(int j=0;j<sub_combinational_matrix1.size();j++){
            if(sub_combinational_matrix1[j]!=sub_reference_matrix[j]){
              if(swap_column1==0)
                 swap_column1=j+1;
              else
                 swap_column2=j+1;
            }
         }
       }

       //cout<<"swapping cols for i="<<i<<" :"<<swap_column1<<" & "<<swap_column2<<endl;
       if(swap_column1==0 || swap_column2==0)
       {
          cout<<"Graph "<<reference_matrix[0][0]<<" & "<<combinational_matrix[0][0]<<" are NOT ISOMORPHIC"<<endl;
          break;
       }
       for(int m=0;m<swap_history.size();m++)
           if(swap_history[m]==to_string(swap_column1)+to_string(swap_column2) || swap_history[m]==to_string(swap_column2)+to_string(swap_column1)){
              cout<<"Graph "<<reference_matrix[0][0]<<" & "<<combinational_matrix[0][0]<<" are NOT ISOMORPHIC"<<endl;
              not_isomorphic=true;
              break;
           }
       if(not_isomorphic)
         break;
       temp=to_string(swap_column1)+to_string(swap_column2);
       swap_history.push_back(temp);
       temp=to_string(swap_column2)+to_string(swap_column1);
       swap_history.push_back(temp);
       for(int j=0;j<combinational_matrix[0].size();j++)
       {
          int vertex=combinational_matrix[j][swap_column1];
          combinational_matrix[j][swap_column1]=combinational_matrix[j][swap_column2];
          combinational_matrix[j][swap_column2]=vertex;
       }       
       for(int j=0;j<combinational_matrix[0].size();j++)
       {
          int vertex=combinational_matrix[swap_column1][j];
          combinational_matrix[swap_column1][j]=combinational_matrix[swap_column2][j];
          combinational_matrix[swap_column2][j]=vertex;
       }
/*
  for(int m=0;m<combinational_matrix.size();m++)
  {
     for(int n=0;n<combinational_matrix[i].size();n++)
     {
         cout<<combinational_matrix[m][n]<<" ";
     }
     cout<<endl;
  }
*/

       i=1;
     }
     if(i==combinational_matrix.size()-1){
       cout<<"Graph "<<reference_matrix[0][0]<<" & "<<combinational_matrix[0][0]<<" are ISOMORPHIC"<<endl;
       cout<<"Mapping of the graphs"<<endl;
       for(int m=1;m<combinational_matrix.size();m++)
          cout<<m<<"\t";
       cout<<endl;
       for(int m=1;m<combinational_matrix.size();m++)
          cout<<combinational_matrix[0][m]<<"\t";
       cout<<endl;
     }
  }

/*
  cout<<"Combinational matrix after swapping..."<<endl;
  for(int i=0;i<combinational_matrix.size();i++)
  {
     for(int j=0;j<combinational_matrix[i].size();j++)
     {
         cout<<combinational_matrix[i][j]<<" ";
     }
     cout<<endl;
  }
*/
  combinational_matrix.clear();
  swap_history.clear();
  not_isomorphic=false;
  }
  } 
  str.close();

  return 0;
}
