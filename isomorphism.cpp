#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <utility>
#include <string>  
using namespace std;

class Combinational_matrix_history_node{
  public:
    vector<vector<int> > combinational_matrix_history;
    Combinational_matrix_history_node *next;
};
// Start of the linkedlist, containing a list of all the previous configuration of combinational_matrix
Combinational_matrix_history_node *firstNode=NULL;
// End of the linked-list
Combinational_matrix_history_node *lastNode=NULL;

void updateHistory(vector<vector<int> > combinational_matrix){
   Combinational_matrix_history_node *n=new Combinational_matrix_history_node();
   n->combinational_matrix_history=combinational_matrix;
   n->next=NULL;
   if(firstNode!=NULL)
   {
      lastNode->next=n;
      lastNode=n;
   }
   else
   {
      firstNode=n;
      lastNode=n;
   }
}

void createAdjacencyMatrix(int &row, bool &ref, string lines,int &new_line,vector<vector<int> > &reference_matrix,vector<vector<int> > &combinational_matrix,int &graph_no,int &no_vertices)
{
    if(new_line==0){
       row=1;
       graph_no++;
       no_vertices=stoi(lines);
       if(reference_matrix.size()!=0)
          ref=false;
       new_line=stoi(lines);
    }
    else{
       vector<int> temp_reference_combinational(no_vertices+1,0);
       if(ref){
          if(reference_matrix.size()==0){
              vector<int> temp_reference_matrix(no_vertices+1,0);
              temp_reference_matrix[0]=graph_no;
              for(int i=1;i<temp_reference_matrix.size();i++)
                 temp_reference_matrix[i]=i;
              reference_matrix.push_back(temp_reference_matrix);
          }
          temp_reference_combinational[0]=row++;
          size_t pos = 0;
          string token;
          while ((pos = lines.find(",")) != string::npos) {
             token = lines.substr(0, pos);
             temp_reference_combinational[stoi(token)]=1;
             lines.erase(0, pos + 1);
          }
          temp_reference_combinational[stoi(lines)]=1;
          reference_matrix.push_back(temp_reference_combinational);
       }
       else{
          if(combinational_matrix.size()==0){
             vector<int> temp_combinational_matrix(no_vertices+1,0);
             temp_combinational_matrix[0]=graph_no;
             for(int i=1;i<temp_combinational_matrix.size();i++)
                temp_combinational_matrix[i]=i;
             combinational_matrix.push_back(temp_combinational_matrix);
          }
          temp_reference_combinational[0]=row++;
          size_t pos = 0;
          string token;
          while ((pos = lines.find(",")) != string::npos) {
             token = lines.substr(0, pos);
             temp_reference_combinational[stoi(token)]=1;
             lines.erase(0, pos + 1);
          }
          temp_reference_combinational[stoi(lines)]=1;
          combinational_matrix.push_back(temp_reference_combinational);      
       }
       new_line--;       
    }
}

void printMatrix(string str,vector<vector<int> > matrix)
{
    cout<<str<<endl;
    for(int i=0;i<matrix.size();i++)
    {
       for(int j=0;j<matrix[i].size();j++)
       {
          cout<<matrix[i][j]<<"\t";
       }
       cout<<endl;
    }
}

int RotationCheck(vector<vector<int> > &combinational_matrix, int index1, int index2)
{
    // Swap cols index1 & index2 then Swap rows index1 & index2
    vector<vector<int> > updated_combinational_matrix=combinational_matrix;
    for(int j=0;j<combinational_matrix[0].size();j++)
    {
       int vertex=updated_combinational_matrix[j][index1];
       updated_combinational_matrix[j][index1]=updated_combinational_matrix[j][index2];
       updated_combinational_matrix[j][index2]=vertex;
    }       
    for(int j=0;j<combinational_matrix[0].size();j++)
    {
       int vertex=updated_combinational_matrix[index1][j];
       updated_combinational_matrix[index1][j]=updated_combinational_matrix[index2][j];
       updated_combinational_matrix[index2][j]=vertex;
    }

    // Check if the new configuration is present in the linkedlist
    Combinational_matrix_history_node *currentNode=firstNode;
    while(currentNode!=NULL)
    {
       for(int i=1;i<combinational_matrix[0].size();i++)
       {
           vector<int>sub_updated_combinational_matrix (&updated_combinational_matrix[i][1],&updated_combinational_matrix[i][combinational_matrix[0].size()]);
           vector<int>sub_combinational_matrix_history (&currentNode->combinational_matrix_history[i][1],&currentNode->combinational_matrix_history[i][combinational_matrix[0].size()]);
           if(!equal(sub_combinational_matrix_history.begin(), sub_combinational_matrix_history.end(), sub_updated_combinational_matrix.begin()))
              break;
           if(i==combinational_matrix[0].size()-1)
              return 0;
       }
       currentNode=currentNode->next;
    }
    updateHistory(updated_combinational_matrix);
    combinational_matrix=updated_combinational_matrix;
    return 1;
}

// Returns 1 if the graphs are isomorphic or 0 otherwise
int ISO_Algorithm(vector<vector<int> > &combinational_matrix, vector<vector<int> > reference_matrix, int &no_rotation)
{
    int i=1, result=-1, skipped=0;
    while(i<combinational_matrix[0].size())
    {
       vector<int>sub_combinational_matrix (&combinational_matrix[i][1],&combinational_matrix[i][combinational_matrix[0].size()]);
       vector<int>sub_reference_matrix (&reference_matrix[i][1],&reference_matrix[i][combinational_matrix[0].size()]);
       if(!equal(sub_reference_matrix.begin(), sub_reference_matrix.end(), sub_combinational_matrix.begin()))
       {
           // Find the j'th row greater than i, that closely matches row i
           int current_mismatch=0, matched_row=i;
           for(int j=1;j<combinational_matrix[0].size();j++)
              if(reference_matrix[i][j]!=combinational_matrix[i][j])
                  current_mismatch++;
           int prospective_mismatch=0;
           for(int j=i+1;j<combinational_matrix[0].size();j++)
           {
              for(int k=1;k<combinational_matrix[0].size();k++)
                 if(reference_matrix[i][k]!=combinational_matrix[j][k])
                    prospective_mismatch++;
              if(!prospective_mismatch)
              {
                 matched_row=j;
                 current_mismatch=prospective_mismatch;
                 break;
              }
              else if(prospective_mismatch<current_mismatch || (skipped==1 && prospective_mismatch==2))
              {
                 matched_row=j;
                 current_mismatch=prospective_mismatch;
              }
              prospective_mismatch=0;
           }
           if(matched_row!=i)
           {
              result=RotationCheck(combinational_matrix, matched_row, i);
              if(result)
              {
                if(!current_mismatch)
                   skipped=0;
                // Inforamtion of the indexes being swapped, for row closely matching the i'th row
                cout<<"Swapping for rows "<<matched_row<<" & "<<i<<endl;
                no_rotation++;
              }
              else if(skipped)
                      i++;
           }
           else if(skipped)
                   i++;
           if(i==combinational_matrix[0].size())
              break;

           // Find the mismatch at row i, then swap them
           int index1=0, index2=0;
           for(int x=1;x<combinational_matrix[0].size();x++)
              if(reference_matrix[i][x]!=combinational_matrix[i][x])
              {
                 if(index1==0)
                    index1=x;
                 else
                    index2=x;
              }
           if(index1)
           {
              result=RotationCheck(combinational_matrix, index1, index2);
              if(!result)
              {
                skipped=1;
              }
              else
              {
                // Inforamtion of the indexes being swapped, for mismatches at a particular row
                cout<<"Swapping for cols "<<index1<<" & "<<index2<<endl;
                no_rotation++;
                skipped=0;
                i=1;
              }
           }

           //cout<<skipped<<"--"<<i<<endl;
       }
       else
           i++;
    }
    if(skipped==0)
      return 1;
    else
      return 0;
}

int main(){
  vector<vector<int> > reference_matrix;
  vector<vector<int> > combinational_matrix;
  int graph_no=0,row=0,no_vertices=0,no_rotations_switching=0;
  string lines;
  bool ref=true;
  int new_line=0;
  std::fstream str_file,str;

  std::string input_file_name="input.txt";
  str_file.open(input_file_name, std::fstream::in);

  std::string input_file;
  str_file>>input_file;
  str.open(input_file, std::fstream::in);

  while(str >> lines){
     createAdjacencyMatrix(row,ref,lines,new_line,reference_matrix,combinational_matrix,graph_no,no_vertices);

     if(combinational_matrix.size()==no_vertices+1){
        cout<<"################################ LOADING NEW GRAPH ########################################"<<endl;

        updateHistory(combinational_matrix);
        printMatrix("Reference matrix before Rotations/Swappings...",reference_matrix);
        printMatrix("Combinational matrix before Rotations/Swappings...",combinational_matrix);

        int result=ISO_Algorithm(combinational_matrix, reference_matrix, no_rotations_switching);
        cout<<endl;
        if(result)
             cout<<"Results : Graph "<<reference_matrix[0][0]<<" and "<<combinational_matrix[0][0]<<" are Isomorphic"<<endl;
        else
             cout<<"Results : Graph "<<reference_matrix[0][0]<<" and "<<combinational_matrix[0][0]<<" are NOT Isomorphic"<<endl;
        cout<<endl;

        printMatrix("Combinational matrix after "+std::to_string(no_rotations_switching)+" Rotations/Swappings...",combinational_matrix);
        cout<<"################################ END OF COMPARISON ########################################"<<endl;
        cout<<endl;

        combinational_matrix.clear();
        no_rotations_switching=0;
        firstNode=NULL;
        lastNode=NULL;
     }
  }
  str.close();
  return 0;
}
