

/******************************************************************************

                              AKIN ROBOTICS
                     MÜLAKAT SORULARI, AUG 2020, KONYA
                               UYGULAMA-2
             Traveling Salesman Problem Dynamic Programming in C++
                             Mustafa Altunok

*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#define INT_MAX 999999

int n = 6; // total number of points

// random point generation
int point0_x = 0;
int point0_y = 0;
int point1_x = rand() % 201 + (-100);
int point1_y = rand() % 201 + (-100);
int point2_x = rand() % 201 + (-100);
int point2_y = rand() % 201 + (-100);
int point3_x = rand() % 201 + (-100);
int point3_y = rand() % 201 + (-100);
int point4_x = rand() % 201 + (-100);
int point4_y = rand() % 201 + (-100);
int point5_x = rand() % 201 + (-100);
int point5_y = rand() % 201 + (-100);

//absolute values of random points for distance calculation

int apoint0_x = 0;
int apoint0_y = 0;
int apoint1_x = abs(point1_x);
int apoint1_y = abs(point1_y);
int apoint2_x = abs(point2_x);
int apoint2_y = abs(point2_y);
int apoint3_x = abs(point3_x);
int apoint3_y = abs(point3_y);
int apoint4_x = abs(point4_x);
int apoint4_y = abs(point4_y);
int apoint5_x = abs(point5_x);
int apoint5_y = abs(point5_y);


int distance(int x1, int y1, int x2, int y2)
{
    // Funciton for calculating distance between two points 
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
// differences between points
int dist00 = distance(apoint0_x, apoint0_y, apoint0_x, apoint0_y);
int dist01 = distance(apoint0_x, apoint0_y, apoint1_x, apoint1_y);
int dist02 = distance(apoint0_x, apoint0_y, apoint2_x, apoint2_y);
int dist03 = distance(apoint0_x, apoint0_y, apoint3_x, apoint3_y);
int dist04 = distance(apoint0_x, apoint0_y, apoint4_x, apoint4_y);
int dist05 = distance(apoint0_x, apoint0_y, apoint5_x, apoint5_y);
int dist10 = dist01;
int dist11 = 0;
int dist12 = distance(apoint1_x, apoint1_y, apoint2_x, apoint2_y);
int dist13 = distance(apoint1_x, apoint1_y, apoint3_x, apoint3_y);
int dist14 = distance(apoint1_x, apoint1_y, apoint4_x, apoint4_y);
int dist15 = distance(apoint1_x, apoint1_y, apoint5_x, apoint5_y);
int dist20 = dist02;
int dist21 = dist12;
int dist22 = 0;
int dist23 = distance(apoint2_x, apoint2_y, apoint3_x, apoint3_y);
int dist24 = distance(apoint2_x, apoint2_y, apoint4_x, apoint4_y);
int dist25 = distance(apoint2_x, apoint2_y, apoint5_x, apoint5_y);
int dist30 = dist03;
int dist31 = dist13;
int dist32 = dist23;
int dist33 = 0;
int dist34 = distance(apoint3_x, apoint3_y, apoint4_x, apoint4_y);
int dist35 = distance(apoint3_x, apoint3_y, apoint5_x, apoint5_y);
int dist40 = dist04;
int dist41 = dist14;
int dist42 = dist24;
int dist43 = dist34;
int dist44 = 0;
int dist45 = distance(apoint4_x, apoint4_y, apoint5_x, apoint5_y);
int dist50 = dist05;
int dist51 = dist15;
int dist52 = dist25;
int dist53 = dist35;
int dist54 = dist45;
int dist55 = 0;

// assigning the points to an array
int dist[6][6] = { {dist00, dist01, dist02, dist03, dist04, dist05},
                                 {dist10, dist11, dist12, dist13, dist14, dist15},
                                 {dist20, dist21, dist22, dist23, dist24, dist25},
                                 {dist30, dist31, dist32, dist33, dist34, dist35},
                                 {dist40, dist41, dist42, dist43, dist44, dist45},
                                 {dist50, dist51, dist52, dist53, dist54, dist55} };

// if all points visited
int VISITED_ALL = (1 << n) - 1;
int dp[64][6];

// tsp function, mask:set of points, pos:index

int tsp(int mask, int pos) {
    

    if (mask == VISITED_ALL) {
        return dist[pos][0]; // if visited all points then return to starting point
    }

    // lookup dp
    if (dp[mask][pos] != -1) {
        return dp[mask][pos];
    }
    int minPath = INT_MAX; // starTing minPath variable is int max

    // go to an unvisited point

    for (int point = 0; point < n; point++) {
       
        
        if ((mask & (1 << point)) == 0) {
            int newdist = dist[pos][point] + tsp(mask | (1 << point), point);
            minPath = min(minPath, newdist);
           
        }

    }
    
    return dp[mask][pos] = minPath;
    
}



int main()
{
    cout << "Random Point Array: " << endl;
    // outputting the array consisting of random points
    for (int i = 0; i < 6; ++i)
    {
        for (int j = 0; j < 6; ++j)
        {
            cout << dist[i][j] << " ";
        }
        cout << endl;

    }
    cout << endl;
    //  random point coordinates
    cout << "Source Point 0: " << "x:" << point0_x << " y:" << point0_y << "\n\n";
    cout << "Random Point 1: " << "x:" << point1_x << " y:" << point1_y << "\n\n";
    cout << "Random Point 2: " << "x:" << point2_x << " y:" << point2_y << "\n\n";
    cout << "Random Point 3: " << "x:" << point3_x << " y:" << point3_y << "\n\n";
    cout << "Random Point 4: " << "x:" << point4_x << " y:" << point4_y << "\n\n";
    cout << "Random Point 5: " << "x:" << point5_x << " y:" << point5_y << "\n\n";
    cout << endl;

    /* init the dp array */
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    cout << "Min Path is " << tsp(1, 0);
    cout << endl;
   

    return 0;
}


/*Random Point Array:
0 96 69 59 118 83
96 0 56 39 23 35
69 56 0 27 78 73
59 39 27 0 62 47
118 23 78 62 0 45
83 35 73 47 45 0

Source Point 0: x:0 y:0

Random Point 1: x:-59 y:76

Random Point 2: x:3 y:69

Random Point 3: x:-26 y:-54

Random Point 4: x:-79 y:-88

Random Point 5: x:-72 y:43


Min Path is 286

C:\Users\eda ase\source\repos\AKIN_Q2_V3\x64\Debug\AKIN_Q2_V3.exe (process 13612
) exited with code 0.
To automatically close the console when debugging stops, enable Tools->Options->
Debugging->Automatically close the console when debugging stops.
Press any key to close this window . . .
*/