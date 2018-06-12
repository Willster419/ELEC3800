#!/bin/sh
#Willard Wider
#6/12/18
#ELEC3800
#lab08
#some shell script to search a text file

#welcome and setup search
echo "Welcome to searching for good artists"
num_found_artists=0
#load the text file to search
echo "wait, loading the file to search..."
mapfile -t artists < text_file.txt
#read then write console input
echo "Input your artist name, and i'll let you know if it's good"
read artist_search
printf "you request %s\n" "$artist_search"
#format the look of the search
#Artist,           Album,                     Song
#printf "Artist\t           Album\t                     Song\n"
#loop throuhg text file, if search term is there then incriment a counter
for i in "${artists[@]}"
do
  #echo "$i"
  if [[ $i = *"$artist_search"* ]]
  then
    #echo "found match: $i"
    #split out and put each term so it looks nice
    IFS=',' read -r -a array <<< "$i"
    printf "${array[0]}\t${array[1]}\t${array[2]}\n"
    num_found_artists=$(expr $num_found_artists + 1)
  fi
done
#search end
printf "Search done, with %d results\n" "$num_found_artists"
#inform the user if there were no results
if [ "$num_found_artists" == 0 ]
then
  echo "(your requested artist must not be good then)"
fi
#exit message
echo "this concludes your search"
