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

# Create the 'red' directory inside 'MudGame'
mkdir -p "$BASEDIR/MudGame/red"

# Define a function to create a room with a description
create_room() {
    mkdir -p "$BASEDIR/MudGame/red/$1"
    echo "$2" > "$BASEDIR/MudGame/red/$1/desc.txt"
    touch "$BASEDIR/MudGame/red/$1/$2"
}

# Create rooms with descriptions within the 'red' directory
create_room "start" "Red Start" #Start room
create_room "start/west" "Lava Pond" #room 1
create_room "start/east" "Dark Room" #room 2
create_room "start/east/east" "Foggy Tunnel" #room 3
create_room "start/east/east/north" "Shiny Hallway" # room 4
create_room "start/east/east/north/east" "Narrow Bridge" # room 5
create_room "start/east/east/north/east/north" "Elevator" # room 6
create_room "start/east/east/north/east/north/east" "Spiral Maze" # room 7
create_room "start/east/east/north/east/north/east/north" "Red Connect" # room C
create_room "start/west/north" "Coin Room" # room I

# Create symbolic links using absolute paths within the 'red' directory
ln -sfn "$BASEDIR/MudGame/red/start/east/east/north/east/north/east/north" "$BASEDIR/MudGame/red/start/east/east/north/east/north/east/north/south"
ln -sfn "$BASEDIR/MudGame/red/start/east/east/north/east/north/east" "$BASEDIR/MudGame/red/start/east/east/north/east/north/east/north/south"
ln -sfn "$BASEDIR/MudGame/red/start/east/east/north/east/north" "$BASEDIR/MudGame/red/start/east/east/north/east/north/east/west"
ln -sfn "$BASEDIR/MudGame/red/start/east/east/north/east" "$BASEDIR/MudGame/red/start/east/east/north/east/north/south"
ln -sfn "$BASEDIR/MudGame/red/start/west/north" "$BASEDIR/MudGame/red/start/west/north/south"
ln -sfn "$BASEDIR/MudGame/red/start/east/east/north" "$BASEDIR/MudGame/red/start/east/east/north/east/west"
ln -sfn "$BASEDIR/MudGame/red/start/east/east" "$BASEDIR/MudGame/red/start/east/east/north/south"
ln -sfn "$BASEDIR/MudGame/red/start/east" "$BASEDIR/MudGame/red/start/east/east/west"
ln -sfn "$BASEDIR/MudGame/red/start/west" "$BASEDIR/MudGame/red/start/west/north/south"
ln -sfn "$BASEDIR/MudGame/red/start" "$BASEDIR/MudGame/red/start/east/west"
ln -sfn "$BASEDIR/MudGame/red/start" "$BASEDIR/MudGame/red/start/west/east"

# Print the final directory structure to confirm