#pragma once
#include <iostream>

using namespace std;

template<int N>
struct NQueue
{
    NQueue(){}

    void Running()
    {
        int arr[N][N] = {0};
        Queue(0, arr);
    }

private:
    void Queue(int col, int arr[][N])
    {
        if (col == N)
        {
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < N; j++)
                {
                    cout<<arr[i][j]<<" ";
                }
                std::cout<<endl;
            }
            cout<<endl;
        }

        for (int i = 0; i < N; i++)
        {
            if (IsConrrect(i, col, arr))
            {
                arr[i][col] = 1;
                Queue(col+1, arr);
                arr[i][col] = 0;
            }
        }
    }
    bool IsConrrect(int row, int col, int arr[][N])
    {
        int row_s, col_s;
        //row
        for ( row_s = row,col_s = 0; col_s < N; col_s++)
        {
            if (arr[row_s][col_s] == 1 && col_s != col)
            {
                return false;
            }
        }
        
        //col
        for (col_s = col,row_s = 0; row_s < N; row_s++)
        {
            if (arr[row_s][col_s] == 1 && row_s != row)
            {
                return false;
            }   
        }

        //left top
        for (row_s = row-1, col_s = col - 1; row_s>=0 && col_s>=0; row_s--, col_s--)
        {
            if (arr[row_s][col_s] == 1)
            {
                return false;
            }
        }

        //right bootom
        for (row_s=row+1,col_s=col+1; row_s < N && col_s < N; row_s++,col_s++)
        {
            if (arr[row_s][col_s] == 1)
            {
                return false;
            }
            
        }
        
        //right top
        for (row_s=row-1,col_s = col+1; row_s>=0&& col_s<N; row_s--, col_s++)
        {
            if (arr[row_s][col_s] == 1)
            {
                return false;
            }
        }

        //left bottom
        for (row_s = row+1,col_s=col-1;row_s < N && col_s >=0; row_s++, col_s--)
        {
            if (arr[row_s][col_s] == 1)
            {
                return false;
            }
            
        }

        return true;
    }
};
