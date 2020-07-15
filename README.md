# Drone-path-detection

We say that every point in our map can be defined as a pair of latitude and longitude. So using this information we are mapping those latitudes and longitudes into a 2 Dimensional matrix. 

From a research we know,

    new_latitude  = latitude  + (dy / r_earth) * (180 / pi) and 
    new_longitude = longitude + (dx / r_earth) * (180 / pi) / cos(latitude * pi/180);
    As long as dx and dy are small compared to the radius of the earth and you don't get too close to the poles.
    
    
    In india latitude ranges from 6 degree north to 30 degree north and value of cos(latitude*pi/180) is almost equal to one, and hence we can use above realtion and say that, 
    1 degree change in latitude and longitude can cause upto 111km change in land near india(approximately). And therefore, for 1m will have change of 10^-5 degree(approx).
    
    So for 2 km radius change in angle will be approximately 0.018 degree both in latitude and longitude
    So we can say, maximum permissible value for new latitudes and longitudes is +=0.02.
    
Now if we consider each point in a map as 1m x 1m block which is a part of 2D matrix of 4001x4001,
in which point(2000,2000) will represent latitude and longitude of our delivery station.

    we can find the coordinates in our matrix from the provided longitude and latitude by the given formula
    x=(new_latitude-old_latitude)x10^5+2000
    y=(new_longitude-old_longitude)x10^5+2000



We will get array of invalid points(Points where our drone cannot fly due to height etc). This Array will consist of all the locations which is invalid for drone i.e. drone can not fly over there. After getting those points they are marked as -1(invaid state) in our Drone map( 2D Matrix of 4001 x 40001).



Now BFS (Breadth First Search) is performed from source to destination keeping information about parent of each cell in a matrix. And after reaching the destination node/cell we retrace the path from that parent information and get the shortest path from source to destination. This information is then transferred to drone and drone follows this path.


### BFS- Breadth First Search
  
##### Steps

    1.) Insert the source node into the queue, and mark that node as visited.
    2.) Run a loop until the queue is empty and pop one node at each loop.
    3.) Check for all 8 possible directions of node and if it is possible to go there.
    4.) If possible insert that node with its parent in the queue.
    5.) Repeat process 2-4 until destination is reached.
    6.) Print the path with the help of parent information stored in the node.
    
The path provided by BFS are in terms of x and y coordinates, convert that coordinates back to latitudes and longitudes.
    
    Latitude= src_latitude+(x-2000)*10e-5;
    longitude= src_longitude+(y-2000)*10e-5;
    
    
 Open main.cpp for c++ code for the same!!!!!!!!!
