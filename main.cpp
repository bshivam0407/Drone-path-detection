#include<bits/stdc++.h>
using namespace std;
struct location{

    double latitude;
    double longitude;

};
struct Node
{
	// (x, y) represents coordinates of a cell in matrix
	int x, y;

	// parent stores the parent Node of the current cell
	// It will have only one entry i.e. parent node
	vector<Node> parent;

	// As we are using struct as a key in a std::set,
	// we need to overload below operators

	bool const operator==(const Node& ob) const
	{
		return x == ob.x && y == ob.y;
	}

	bool operator<(const Node& ob) const
	{
		return x < ob.x || (x == ob.x && y < ob.y);
	}
};
vector<location> finalPath; // final vector which will be used by drone to follow its path
void printPath(vector<Node> path,double src_lat,double src_lon)
{
	if (path.size() == 0)
		return ;

	printPath(path[0].parent,src_lat,src_lon);
	//converting points back to Latitude and longitude
	double final_x=src_lat+(path[0].x-2000)*0.00001;
	double final_y=src_lon+(path[0].y-2000)*0.00001;
	location final_points={final_x,final_y};
	finalPath.push_back(final_points);

	cout << "(" << path[0].x << ", " << path[0].y << ") ";
	return;
}
// The function returns false if pt is not a valid position
bool isValid(int x, int y)
{
	return (x >= 0 && x <= 4000) && (y >= 0 && y <= 4000);
}
int droneMap[4001][4001]={0};

//Drone can move in all 8 directions
int row[] = { -1,-1,-1, 0, 0, 1,1,1 };
int col[] = { 0, -1, 1, -1,1,-1,1,0 };


int main()
{

    double srclat,srclon;// These are longitudes and latitudes for delivery station.
    double destlat,destlon;
    cout<<"Source latitude and longitude: ";
    cin>>srclat>>srclon;
    cout<<endl;
    cout<<"Destination latitude and longitude: ";
    cin>>destlat>>destlon;
    int src_x=2000;
    int src_y=2000;
    int dest_x=(destlat-srclat)*100000+2000;
    int dest_y=(destlon-srclon)*100000+2000;

    /*(2*pi/360) * radius_earth = 111 km / degree
    for 1m will will have change of 10^-5 degree(approx)
    So for 2 km radius change in angle will be approximately 0.1 degree both in latitude and longitude
    So we can say, maximum permissible value for new latitudes and longitudes is +=0.02.

    Now if we consider each point in a map as 1m x 1m block which is a part of 2D matrix of 4001x40001,
    in which point(2000,2000) will represent latitude and longitude of our delivery station


    we can find the coordinates in our matrix from the provided longitude and latitude by the given formulas
    ch
    x=(new_latitude-old_latitude)x10^5+2000
    y=(new_longitude-old_longitude)x10^5+2000



    We will get array of invalid points(Points where our drone cannot fly due to height etc).
    This Array will consist of all the locations which is invalid for drone i.e. drone can not fly over there.

    */
    vector<location> invalidLocations;

    int n;// Number of invalid Locations
    cin>>n;
    for(int i=0;i<n;i++)
    {
        double invalidLatitude,invalidLongitude;
        cin>>invalidLatitude>>invalidLongitude;
        location invalidPoint;
        invalidPoint.latitude=invalidLatitude;
        invalidPoint.longitude=invalidLongitude;
        invalidLocations.push_back(invalidPoint);
        // We will be converting this points to x & y coordinate and will change the value of those
        // x and y coordinates to -1 stating that this point cannot come in the path.
        //x=(new_latitude-old_latitude)x10^5+2000
        //y=(new_longitude-old_longitude)x10^5+2000
        //using above formula we get the coordinates in the matrix.
        if(abs(invalidLatitude-srclat)>0.02 || abs(invalidLongitude-srclon)>0.02) //maximum permissible change is 0.02degrees
            continue;
        int x_coordinate=(invalidLatitude-srclat)*100000+2000;
        int y_coordinate=(invalidLongitude-srclon)*100000+2000;
        droneMap[x_coordinate][y_coordinate]=-1;
    }




    //Run BFS (Breadth First Search) algorithm from source to destination and find the shortest path
    int flag=0;
    queue<Node> q;
    Node srcNode = {src_x, src_y};
	q.push(srcNode);

	// set to check if matrix cell is visited before or not
	set<Node> visited;
	visited.insert(srcNode);

	// run till queue is not empty
	while (!q.empty())
	{
		// pop front node from the queue and process it
		Node curr = q.front();
		q.pop();

		int i = curr.x;
		int j = curr.y;

		// if destination is found, print the shortest path and
		// return the shortest path length
		if (i == dest_x  && j == dest_y)
		{
		    // send path to drone
            vector<Node> v;
            v.push_back(curr);

			cout << "Shortest path is: ";
			printPath(v,srclat,srclon);
			flag=1;
			break;
		}



		// check all 4 possible movements from current cell
		// and recur for each valid movement
		for (int k = 0; k < 8 ; k++)
		{
			// get next position coordinates using value of current cell
			int x = i + row[k] ;
			int y = j + col[k] ;

			// check if it is possible to go to next position
			// from current position
			if (isValid(x, y) && droneMap[x][y]!=-1)
			{
			    vector<Node> v;
                v.push_back(curr);
				// construct the next cell node
				Node next = { x, y, v };

				// if it not visited yet
				if (!visited.count(next))
				{
					// push it into the queue and mark it as visited
					q.push(next);
					visited.insert(next);
				}
			}
		}
	}
	if(flag==0)
        cout<<"No such path is found"<<endl;

}
