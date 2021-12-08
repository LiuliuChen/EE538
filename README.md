# EE538 Final Project Report - Fall 2021 - TrojanMap

## Overview

## Step 1: Autocomplete the location name
```c++
std::vector<std::string> Autocomplete(std::string name);
```
- Implementation\
    Use ```strcasecmp(str1, str2)``` : compare 2 strinfs without sensitivity to case.
- Time Comlexity\
    O(N*m), where m is the length of the name, N is the size of the data.
- Output

   ![step1-img1](/data/s1-1.png)

   ![step1-img2](/data/s1-2.png)

   ![step1-img3](/data/s1-3.png)




## Step 2: Find the place's Coordinates in the Map
- Implementation

  we can use ```GetID()``` function to get the location ID from the location name, then we can get the longtitude and latitude directly.

- Time Complexity

   The time complexity of GetID() is O(N), therefore the complexity of GetPosition method is O(N).

- Output

    1. Target
    
        ![step2-img1](/data/s2-1.png)

    2. Ralphs

        ![step2-img2](/data/s2-2.png)

    3. The location does not exists

        ![step2-img3](/data/s2-3.png)


## Step 3: CalculateShortestPath between two places
- Algorithms

   | Dijkstra | Bellman_Ford |
   | :-----| :---- |
   | Greedy Approach | Dynamic Programming |
   | Doesn’t work when negative weight edges exist. | Works when Negative weight edges exist, and also detect negative weight cycle.
 |


- Time Complexity

  | Dijkstra | Bellman_Ford |
   | :-----| :---- |
   | O(E*log(V)) | O(VE) |

- Runtime Comparision

  | Source | Destination | Distance | Dijkstra | BellmanFord
   | :-----| :---- | :---- | :---- | :---- 
   | CVS | Ralphs | 1.14497 | 11019 | 1640435
   | Ralphs | Target | 0.839235 | 9397 | 1671992
   | Sonny Astani School of Civil Engineering | Massman Theatre | 0.0730368 | 5760 | 1666575
   | USC Parking | Target| 0.291199 | 9752 | 1682220
   | Metro 40 | CVS| 1.12397 | 9658 | 1754539

   From this graph, we can see when fidning the shortest path from one to another, the Dijkstra is always faster than the BellmanFord, it's less time consuming.



- Output

    1.  CVS - Ralphs
    
        ![step3-img1](/data/s3-1.png)
    
    2. Metro 40 - CVS

        ![ste3-img2](/data/s3-2.png) 

## Step 4: The Traveling Trojan Problem (AKA Traveling Salesman!)
- Algorithms

  | | Backtracking | 2-opt Heuristic |
   | :-----| :---- |:---- |
   | Approach | * Take the first node in location_ids as starting and ending point. <br>*Staring traversing from the source to its neighbors using DFS. <br>*Calculating and updating cost and paths. |*Take the location_ids as initial best path. <br>*Random choose 2 points i, k between the starting and ending points, reverse the path between i and k. <br>*Updating the best path and minimum cost.
   | Time Complexity| O(N!) | O(N^2)

- Runtime Comparision

    | Numbers of places | Backtracking | 2-opt(MAX_COUNT=5) | 2-opt(MAX_COUNT=30)
    | :-----| :---- |:---- |:---- |
    | 4 | 93 | 31 | 83
    | 6|2120|39|120
    |8|50739|63|174
    10|1979870|76|207
    12|31527610|83|268
    14| \ |80|353
    50| \ |375|1550
    100| \ |810|3537
    200| \ |1244|5942

    It tooks more than 5 minutes for backtracking when the numbers of places reaches to 14, so I skipped the calculation of bactracking when n>=14.
    
    For the 2 opt algorithm, I set the MAX_COUNT to stop iteration. If there's no improvement of my best path comparing to the old one, than do counting++, until it reaches the MAX_COUNT. With the larger MAX_COUNT, the spent time will increase.

- Distance Comparison

    | Numbers of places | Backtracking | 2-opt(MAX_COUNT=5) | 2-opt(MAX_COUNT=50) | 2-opt(MAX_COUNT=100)
    | :-----| :---- |:---- |:---- |:---- |
    | 4 | 3.74928 | 3.74928 | 3.74928 | 3.74928
    | 6| 3.91385 |4.12016 |4.06874 | 4.00806
    |8|5.6245|8.16689| 6.10004 | 5.63818
    10|5.90536 |8.85507 | 6.10048 | 5.91662
    12|5.93638 | 9.05072 | 7.22263 | 6.70297

    The distances calculated by 2-opt are larger than the bactracking in general, so it's not the optimal solution, but with the increase of MAX_COUNT, the distances are getiting shorter and closer to Bactracking. Considering the runtime of 2-opt, it's acceptable even if we didn't find the optimal using 2-opt.


- Output
    1. N=10 (Backtracking)
        - image
        ![ste4-img1](/data/s4-1.png)
        - animation
        ![step4-gif1](/data/s4-1-gif.gif)

    2. N=20 (2-opt)
        - image
        ![step4-img2](/data/s4-2.png)
        - animation
        ![step4-gif1](/data/s4-2-gif.gif)


## Step 5: Cycle Detection

- Time Complexity\
    In fact, cycle Detection function is a modification of DFS, therefore the time complexity should be O(N+E), where N is the number of nodes, and E is the sum of the sizes of adjacency lists of all nodes. 

- Output
    1. No Cycle
    ![step5-img1](/data/s5-1.png)
    ![step5-img2](/data/s5-2.png)

    2. Has Cycle
    ![step5-img3](/data/s5-3.png)
    ![step5-img4](/data/s5-4.png)

## Step 6: Topological Sort

- Time Complexity

    Topological sort is also using DFS, therefore time complexity should be the same as DFS: O(N+E).

- Output

    ![step6-img1](/data/s6-1.png)
    ![step5-img2](/data/s6-2.png)

## Step 7: Find K closest points

- Implementation

    Using priority queue, store the location id in a priority queue, according to the distance of this location from the source.

- Time Complexity

    O(N+K*log(N))
    
    ![step7-img1](/data/s7-1.png)

- Output

    1. location: CVS; K = 6

        ![step7-img2](/data/s7-2.png)
        ![step7-img3](/data/s7-3.png)

    2. location: Ralphs; K=12

        ![step7-img5](/data/s7-4.png)
        ![step7-img6](/data/s7-5.png)


## Conclusion