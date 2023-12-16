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

# Create the 'orange' directory inside 'MudGame'
mkdir -p "$BASEDIR/MudGame/orange"

# Define a function to create a room with a description
create_room() {
    mkdir -p "$BASEDIR/MudGame/orange/$1"
    echo "$2" > "$BASEDIR/MudGame/orange/$1/desc.txt"
    touch "$BASEDIR/MudGame/orange/$1/$2"
}

# Create rooms with descriptions within the 'orange' directory
create_room "start" "Orange Start" # Start room
create_room "start/east" "Coral Cavern" # room 1
create_room "start/east/south" "Pumpkin Patch" # room 2
create_room "start/east/south/east" "Autumn Falls" # room 3
create_room "start/east/south/east/south" "Peach Orchard" # room 4
create_room "start/east/south/east/east" "Ginger Forest" # room 5
create_room "start/east/south/east/east/east" "Spice Trail" # room 6
create_room "start/east/south/east/east/east/north" "Rusty Chamber" # room 7
create_room "start/east/south/east/east/east/north/north" "Orange Connect" # room C
create_room "start/east/south/east/east/east/south" "Coin Room" # room I

# Create symbolic links using absolute paths within the 'orange' directory
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east/east/north/north" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/north/north/south"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east/east/north" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/north/north/south"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east/east" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/north/south"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east/east" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/south/north"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/west"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east/east/east/south" "$BASEDIR/MudGame/orange/start/east/south/east/east/east/south/north"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east" "$BASEDIR/MudGame/orange/start/east/south/east/east/west"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south/east" "$BASEDIR/MudGame/orange/start/east/south/east/south/north"
ln -sfn "$BASEDIR/MudGame/orange/start/east/south" "$BASEDIR/MudGame/orange/start/east/south/east/west"
ln -sfn "$BASEDIR/MudGame/orange/start/east" "$BASEDIR/MudGame/orange/start/east/south/north"
ln -sfn "$BASEDIR/MudGame/orange/start" "$BASEDIR/MudGame/orange/start/east/west"
