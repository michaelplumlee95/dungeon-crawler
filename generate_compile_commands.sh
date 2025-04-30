#!/bin/bash

# Set output file
OUT=compile_commands.json
echo "[" > $OUT

# Get full working dir
DIR=$(pwd)

# Extract each .cpp file from your SRCS
for file in main.cpp src/*.cpp; do
    echo "  {" >> $OUT
    echo "    \"directory\": \"$DIR\"," >> $OUT
    echo "    \"command\": \"g++ -std=c++17 -Wall -Wextra -g -Isrc -c $file\"," >> $OUT
    echo "    \"file\": \"$DIR/$file\"" >> $OUT
    echo "  }," >> $OUT
done

# Remove trailing comma on last line and close JSON array
sed -i '$ s/},/}/' $OUT
echo "]" >> $OUT

echo "✅ compile_commands.json created!"
