#!/bin/bash

# Function to initialize and update submodules
update_submodules() {
  echo "Initializing and updating submodules..."

  # Initialize submodules
  git submodule init
  if [ $? -ne 0 ]; then
    echo "Failed to initialize submodules."
    exit 1
  fi

  # Update submodules
  git submodule update --recursive --remote
  if [ $? -ne 0 ]; then
    echo "Failed to update submodules."
    exit 1
  fi

  echo "Submodules initialized and updated successfully."
}

# Main script execution
update_submodules
