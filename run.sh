#!/bin/bash

echo "🚗 Ride Sharing Car Tracker - Flyweight Pattern Demo"
echo "===================================================="
echo ""

# Check if source file exists
if [ ! -f "ride_sharing_cars.cpp" ]; then
    echo "❌ Error: ride_sharing_cars.cpp not found!"
    echo "   Make sure you're in the correct directory."
    exit 1
fi

# Compile if needed
if [ ! -f "ride_sharing_cars" ] || [ "ride_sharing_cars.cpp" -nt "ride_sharing_cars" ]; then
    echo "📦 Compiling application..."
    g++ -std=c++17 -Wall -Wextra -O2 -o ride_sharing_cars ride_sharing_cars.cpp
    
    if [ $? -ne 0 ]; then
        echo "❌ Compilation failed!"
        exit 1
    fi
    echo "✅ Compilation successful!"
    echo ""
fi

echo "🚀 Starting simulation..."
echo "   - Map will be generated in this directory as 'driver_map.html'"
echo "   - Updates every 3 seconds for 30 seconds total"
echo "   - Press Ctrl+C to stop early"
echo ""

# Run the application
./ride_sharing_cars

echo ""
echo "✅ Simulation complete!"
echo "   driver_map.html has been generated in this directory."
echo "   Open it in your browser to see the final driver positions."
