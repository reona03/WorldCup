# WorldCup
Annyeong
Comp Sci 839 (C++ FInal Project)

Part 1
For this project, you will be creating an application to input and display Major League Baseball
world series statistics. You will read in data (provided in a file) with the winning and losing
teams for each year of the world series.
The data file provided is in CSV (comma separated value) format.
<year>, <winning team>, <losing team >
The winning/losing team fields include the city and team name that will need to be separated.
There are also multiple word city and team names (i.e. “New York”, “Red Sox”) to deal with.
Requirements (Part 1):
1. Input all data from file (20 points)
a. Separate the team names from the city
b. For each team maintain
i. Team name
ii. Total number of wins
iii. Total number of losses
2. Provide a menu with options to: (20 points)
a. For each team with one or more world series win display
i. The team name and total wins sorted from most to least wins
ii. “None found” if no teams found
b. For each team with one or more world series loss display
i. The team name and total losses sorted from least to most losses
ii. “None found” if no teams found
c. For each team that has played in the world series but never won display
i. The team name
ii. “None found” if no teams found
d. For each team that has won a world series and never lost display
i. The team name
ii. “None found” if no teams found
Note: You can ignore the city (i.e. Brooklyn Dodgers, Los Angeles Dodgers are just Dodgers)
You can treat any teams that have changed their names as different teams.
Suggestions:
1. Define a structure or class to maintain the data
a. Team, Total Wins etc.
2. Declare an array of pointers to the above to collect the data
3. Add functions to search and sort the array
4. As you process the file search the array for an existing element
a. If found update the element data
b. If not found create a “new” object and add it to the array
5. It may be helpful to treat the multiple word cities as special cases
a. Check for: “Los”, “New” etc.
Be Aware:
I listed this as “Part 1” requirements so expect there to be a “Part 2” and possibly a “Part 3”.
A modular program with well designed ADT’s will make incorporating new requirements easier. 
  
 Part 2
 
 
 
 Requirements (Part 2):
1. Modify file processing to include year (10 points)
2. Add menu options to: (20 points)
a. Allow the user to search for a specific team and display the following for each
year they played in the world series
i. The year
ii. The opponent
iii. If they won or lost
b. Allow the user to specify a specific decade and display the following for each
year the world series was played (valid years 1900 to present)
i. The year
ii. The teams that played
iii. Who won
Note: A decade is a period of ten years starting with the year entered and includes the next 9
years (i.e. 1930 to 1939, 1964 to 1973). The world series my not have been played 10 times in
every decade. 


Requirements (Part 3):
1. Modify file processing to include the team city (10 points)
2. Add menu options to: (20 points)
a. List cities that have had one or more wins
i. Sort from most to least wins
ii. Display total wins (i.e. Chicago Cubs & Chicago White Sox have
combined for 6 wins)
b. List cities that have had world series wins from multiple teams
i. Sort by city
ii. List all teams that have won a world series while playing there
iii. List how many wins each team had while there (i.e. the Phillies and
Athletics both had wins while playing in Philadelphia but some of the
Athletics wins were in Oakland) 

