#!/bin/bash

# Get the absolute path of the current directory
BASEDIR=$(pwd)

# Check if MudGame already exists, if not, create it
if [ ! -d "$BASEDIR/MudGame" ]; then
    echo "Creating MudGame directory..."
    mkdir -p "$BASEDIR/MudGame"
else
    echo "MudGame directory already exists."
fi

# Create the 'blue' directory inside 'MudGame'
mkdir -p "$BASEDIR/MudGame/blue"

# Define a function to create a room with a description
create_room() {
    mkdir -p "$BASEDIR/MudGame/blue/$1"
    echo "$2" > "$BASEDIR/MudGame/blue/$1/desc.txt"
    touch "$BASEDIR/MudGame/blue/$1/$2"
}
# Create rooms with descriptions
create_room "start" "Blue Start"
create_room "start/north" "Icy Cavern"
create_room "start/north/north" "Snow Corner"
create_room "start/north/north/east" "Blizzard Lair"
create_room "start/north/north/east/east" "Spike Pit"
create_room "start/north/north/east/east/south" "Crossway"
create_room "start/north/north/east/east/south/east" "Snow Maze"
create_room "start/north/north/east/east/south/east/east" "Polar Stairway"
create_room "start/north/north/east/east/south/east/east/north" "Blue Connect"
create_room "start/north/north/east/east/south/south" "Coin Room"

# Create symbolic links using absolute paths
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/east/north" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/east/north/south"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/east" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/east/north/south"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/east/west"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south/" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/east/west"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south/south" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/south/north"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east/south" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/south/north"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/east" "$BASEDIR/MudGame/blue/start/north/north/east/east/south/north"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north/east/" "$BASEDIR/MudGame/blue/start/north/north/east/east/west"
ln -sfn "$BASEDIR/MudGame/blue/start/north/north" "$BASEDIR/MudGame/blue/start/north/north/east/west"
ln -sfn "$BASEDIR/MudGame/blue/start/north" "$BASEDIR/MudGame/blue/start/north/north/south"
ln -sfn "$BASEDIR/MudGame/blue/start" "$BASEDIR/MudGame/blue/start/north/south"

# Print the final directory structure to confirm