#include <iostream>
#include <bits/stdc++.h>
using namespace std;
const int Size=8;
int visited[Size][Size];
char cpy_grid[Size][Size];
struct spot
{
    char color;
    vector<spot*> v; //vector to push adj nodes
};
spot* grid[Size][Size]; // 2d array of structs "nodes"
void intialize_grid()
{
    srand(time(0));
    for(int i=0; i<Size; i++)
    {

        for(int j=0; j<Size; j++)
        {
            spot *s=new spot(); // create pointer "struct" to node in each index in grid
            s->color='A'+rand()%5; // assign random color to node->data
            grid[i][j]=s; //store node in grid
            cpy_grid[i][j]=grid[i][j]->color;
        }

    }
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            cout<<grid[i][j]->color<<" ";
        }
        cout<<endl;
    }
}
void adjacency_matrix() // intialize 2d matrix
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            visited[i][j]=0;
        }
    }
}
void add_edge() //push to every node in the grid the adjacent nodes in node->vector
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            if(i==0&&j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
            }
            else if(i==0&&j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
            }
            else if(i==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
            }
            else if(i==Size-1&&j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);
            }
            else if(j==0)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);

            }
            else if(i==Size-1&&j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);

            }
            else if(i==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);
            }
            else if(j==Size-1)
            {
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);
            }
            else
            {
                grid[i][j]->v.push_back(grid[i][j+1]);
                grid[i][j]->v.push_back(grid[i][j-1]);
                grid[i][j]->v.push_back(grid[i+1][j]);
                grid[i][j]->v.push_back(grid[i-1][j]);
                grid[i][j]->v.push_back(grid[i+1][j+1]);
                grid[i][j]->v.push_back(grid[i+1][j-1]);
                grid[i][j]->v.push_back(grid[i-1][j+1]);
                grid[i][j]->v.push_back(grid[i-1][j-1]);
            }
        }
    }
}
bool check_valid(int i, int j)
{
    if (i >= 0 && i < Size && j >= 0 && j < Size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_visited_spot(int i,int j)
{
    if(visited[i][j]==0)
    {
        visited[i][j]=1;
        cpy_grid[i][j]='.';
        return true;
    }
    else
    {
        return false;
    }
}
bool connect_spots(int i,int j,spot*curr)
{
    for(int x=0; x<curr->v.size(); x++)
    {
        //check if the node i will connect is adjacent to curr and have same color and non visited
        if(curr->v[x]==grid[i][j] && curr->color==grid[i][j]->color&&check_visited_spot(i,j))
        {
            return true;
        }
    }
    return false;
}

void print_grid()
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            cout<<grid[i][j]->color<<" ";
        }
        cout<<endl;
    }
}
void move_spots()
{
    int k;
    for(int i=0; i<Size; i++)
    {
        k=i;
        for(int j=0; j<Size; j++)
        {
            if(visited[i][j]==1)
            {
                while(k!=0) //move spots from up to down untill reach row 0
                {
                    grid[k][j]->color=grid[k-1][j]->color;
                    cpy_grid[k][j]=grid[k][j]->color;
                    k--;
                }
                grid[k][j]->color='A'+rand()%5; // row 0 store random char
                cpy_grid[k][j]=grid[k][j]->color;
                k=i;
            }
        }
    }
    print_grid();
}
void print_copyGrid()
{
    for(int i=0; i<Size; i++)
    {
        for(int j=0; j<Size; j++)
        {
            cout<<cpy_grid[i][j]<<" ";
        }
        cout<<endl;
    }
}
int play_game()
{
    adjacency_matrix();
    spot*curr=new spot();
    int x,y;
    cout<<"Enter index of spot:";
    cin>>x>>y;
    if(!check_valid(x,y))
    {
        cout<<"enter valid index"<<endl;
    }
    check_visited_spot(x,y);
    curr=grid[x][y];
    print_copyGrid();
    int s=1;
    int m,n;
    while(true)
    {
        cout<<"Enter index of spot or enter -1 to end path:";
        cin>>m>>n;
        if(m==-1 && n==-1)
        {
            if(s<3)
            {
                cout<<"Spots less than 3 "<<endl;
                continue; // to skip iteration
            }
            break;
        }
        while(!check_valid(m,n))
        {
            cout<<"Invalid index"<<endl;
            cin>>m>>n;
        }
        while(!connect_spots(m,n,curr))
        {
            cout<<"NO matching spots"<<endl;
            cin>>m>>n;
        }
        curr=grid[m][n];
        print_copyGrid();
        s++; // count connected spots


    }
    move_spots();
    return s;
}
int main()
{
    intialize_grid();
    add_edge();
    int moves=0;
    int score=0;
    while(moves<5)
    {
        score+=play_game();
        moves++;
        cout<<"Your moves is"<<" "<<moves<<" "<<"out of 5"<<endl;
        cout<<"Your Score is"<<" "<<score*50<<endl;
    }
    cout<<"You reach the limit of moves"<<endl;
    cout<<"Thanks for playing game ";
    return 0;
}
