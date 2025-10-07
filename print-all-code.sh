#!/bin/bash

# This script finds all .cpp files in the current directory and subdirectories,
# then prints their name and content.

# The -print0 and -d '' combination ensures that filenames with spaces are handled correctly.
find . -type f -name "*.cpp" -print0 | while IFS= read -r -d '' file; do
    # Print a header for each file
    echo "=================================================="
    echo "FILE: $file"
    echo "=================================================="

    # Print the content of the file
    cat "$file"

    # Add a couple of newlines for better separation in the output
    echo -e "\n"
done

echo "All .cpp files have been printed."
