# Ride Sharing Car Tracker - Flyweight Pattern

A real-time ride-sharing application demonstrating the **Flyweight Design Pattern** in C++. Track multiple drivers on an interactive map with minimal memory footprint by sharing common car data across instances.


## What is the Flyweight Pattern?

The **Flyweight Pattern** is a structural design pattern that minimizes memory usage by sharing common data among multiple objects. Instead of storing identical data in each object, the pattern separates:

- **Intrinsic State** (shared): Data that's common across objects (car brand, model, type)
- **Extrinsic State** (unique): Data that varies per object (driver name, GPS location, availability)

### Real-World Analogy

Imagine a ride-sharing company with 1000 drivers using 50 different car models. Instead of storing complete car specifications for each of the 1000 drivers, we create 50 flyweight objects (one per car model) and share them across all drivers. This reduces memory usage dramatically!

## Features

- **Real-time Simulation**: 5 drivers with live position tracking
- **GPS Updates**: Positions update every 3 seconds
- **Interactive Map**: Beautiful HTML map using Leaflet.js and OpenStreetMap
- **Status Tracking**: Available (green) / Busy (red) indicators
- **Memory Efficient**: Demonstrates flyweight pattern benefits
- **Docker Support**: Run anywhere with minimal dependencies
- **No API Keys**: Uses free OpenStreetMap tiles

## Preview

The app generates an interactive map showing:
- 🚗 Car icons for available drivers
- 🚙 Different icons for busy drivers  
- Driver names displayed above each vehicle
- Click any car to see driver details and car information
- Auto-refreshing map (every 3 seconds)

## Quick Start

### Option 1: Run with Scripts (Easiest!)

**Linux/Mac:**
```bash
chmod +x run.sh
./run.sh
```


The script will compile automatically (if needed), run the simulation, and open the map in your browser!

### Option 2: Manual Compilation (Recommended for Learning)

**Requirements:** C++ compiler with C++17 support

**Compile:**
```bash
g++ -std=c++17 -Wall -Wextra -O2 -o ride_sharing_cars ride_sharing_cars.cpp
```

**Run:**
```bash
./ride_sharing_cars              # Linux/Mac
.\ride_sharing_cars.exe          # Windows
```

The map will auto-open in your browser and refresh every 3 seconds!

### Option 3: Run with Docker (No Installation Required!)

**Build the image (first time only):**
```bash
docker build -t ride-sharing-app .
```

**Run with volume mount:**


Linux/Mac:
```bash
docker run --rm -v $(pwd):/app ride-sharing-app
```

The `driver_map.html` file will appear **in your current directory**. Open it in your browser!

See [DOCKER_RUN.md](DOCKER_RUN.md) for detailed Docker instructions and troubleshooting.

---

## What You'll See

### Console Output
```
Ride Sharing App - Real-Time Driver Tracking
================================================

=== Live Driver Positions ===
🟢 Driver_A -> Maruti Swift (Hatchback, Petrol, KA) @ (12.9716, 77.5946)
🟢 Driver_B -> Maruti Swift (Hatchback, Petrol, KA) @ (12.9352, 77.6245)
🔴 Driver_C -> Hyundai i20 (Hatchback, Diesel, KA) @ (13.0358, 77.5970)

🗺️  Map saved to: driver_map.html (in current directory)
Opening in browser...

⏱Update 1/10 (Next update in 3 seconds...)
```

### Interactive Map
- Car icons for available drivers (green)
- Different icon for busy drivers (red)
- Driver names displayed above each car
- Click any car to see driver details and car information
- Map auto-refreshes every 3 seconds to show updated positions

## How It Works

### Flyweight Pattern Benefits

The Flyweight pattern separates data into:

**Intrinsic State (Shared):**
- Car brand, model, body type, fuel type, registration state
- Stored once in `CarsDataFlyWeight` objects
- Managed by `CarTypeFactory`

**Extrinsic State (Unique per instance):**
- Driver name, GPS coordinates, availability
- Stored in `CarInstance` objects
- Changes frequently in real-time

**Memory Savings:** Instead of duplicating car data for each driver, we share flyweight objects. For example, both Driver_A and Driver_B use the same Swift flyweight object.

### Code Structure

```cpp
CarsDataFlyWeight      // Stores shared car properties (intrinsic state)
CarTypeFactory         // Creates and manages flyweight objects  
CarInstance            // Stores driver data (extrinsic state) + reference to flyweight
updateDriverPosition() // Simulates real-time GPS movement
generateMapHTML()      // Creates interactive HTML map with Leaflet.js
displayCarStatus()     // Shows driver positions in console
```

### Real-Time Simulation

1. App creates 5 driver instances with initial positions in Bangalore
2. Every 3 seconds:
   - Driver positions update (simulate movement)
   - Availability status randomly toggles
   - New HTML map is generated
   - Map auto-refreshes in browser
3. Runs for 10 updates (30 seconds total)

## Customization

Edit `ride_sharing_cars.cpp`:

**Change update frequency:**
```cpp
std::this_thread::sleep_for(std::chrono::seconds(3));  // Change 3 to your value
```

**Add more drivers:**
```cpp
cars.push_back(
    new CarInstance("Driver_F", 12.9500, 77.6000, true, swift));
```

**Adjust movement range:**
```cpp
std::uniform_real_distribution<> lat_drift(-0.005, 0.005);  // Adjust values
```

**Run longer:**
```cpp
const int max_updates = 10;  // Change to run more/fewer updates
```

**Change car icon size:**
```cpp
iconSize: [100, 100],  // Width, Height in pixels
```

## Files Generated

- `driver_map.html` - Interactive map (auto-generated, updates every 3 seconds)
- `ride_sharing_cars` or `ride_sharing_cars.exe` - Compiled binary

## Requirements

**For local compilation:**
- C++17 compatible compiler (g++, clang++)
- Standard library with threading support

**For Docker:**
- Docker installed and running
- No other dependencies needed!

## Design Pattern: Flyweight

This demonstrates the **Flyweight structural pattern**, which minimizes memory use by sharing common data among multiple objects.

**Perfect for scenarios with:**
- Many similar objects
- Most object state can be made extrinsic (movable outside the object)
- Memory optimization is important
- Immutable shared state

**Real-world applications:**
- Text editors (character formatting)
- Game development (particle systems, terrain tiles)
- UI frameworks (shared style objects)
- This ride-sharing app (shared car specifications)

## Troubleshooting

**Map doesn't open automatically:**
- Manually open `driver_map.html` from this directory
- Make sure your default browser is set

**Compilation errors:**
- Ensure you have C++17 support: `g++ --version`
- Update compiler if needed

**Docker "no such file or directory":**
- Make sure you're in the `ride_sharing` directory
- Rebuild the image: `docker build -t ride-sharing-app .`
- Use volume mount: `docker run --rm -v $(pwd):/app ride-sharing-app`

**Map shows old data:**
- The file updates every 3 seconds
- Refresh your browser tab (F5)
- Or wait for auto-refresh

---

## 📂 Project Structure

```
ride_sharing_using_flyweight/
├── ride_sharing_cars.cpp    # Main application code (450+ lines)
├── Dockerfile                # Multi-stage Docker build  
├── .dockerignore            # Excludes generated files from image
├── README.md                # This file - complete documentation
├── DOCKER_RUN.md            # Detailed Docker guide
├── run.sh                   # Linux/Mac run script
├── run.ps1                  # Windows PowerShell run script
├── driver_map_demo.html     # Static demo preview
└── driver_map.html          # Generated by app (real-time data)
```

## Architecture & Pattern Implementation

### Memory Efficiency Example

**Without Flyweight Pattern:**
```
Driver_A: {brand: "Maruti", model: "Swift", type: "Hatchback", fuel: "Petrol", state: "KA", ...}
Driver_B: {brand: "Maruti", model: "Swift", type: "Hatchback", fuel: "Petrol", state: "KA", ...}
Driver_C: {brand: "Hyundai", model: "i20", type: "Hatchback", fuel: "Diesel", state: "KA", ...}
Driver_D: {brand: "Mahindra", model: "XUV300", type: "SUV", fuel: "Diesel", state: "KA", ...}
Driver_E: {brand: "Hyundai", model: "i20", type: "Hatchback", fuel: "Diesel", state: "KA", ...}

Total: 5 drivers × 5 strings = 25 string objects
```

**With Flyweight Pattern:**
```
Flyweight_Swift: {brand: "Maruti", model: "Swift", type: "Hatchback", fuel: "Petrol", state: "KA"}
Flyweight_i20: {brand: "Hyundai", model: "i20", type: "Hatchback", fuel: "Diesel", state: "KA"}
Flyweight_XUV300: {brand: "Mahindra", model: "XUV300", type: "SUV", fuel: "Diesel", state: "KA"}

Driver_A: {name: "Driver_A", lat: 12.97, lng: 77.59, available: true, car_ref: Flyweight_Swift}
Driver_B: {name: "Driver_B", lat: 12.93, lng: 77.62, available: true, car_ref: Flyweight_Swift}
Driver_C: {name: "Driver_C", lat: 13.03, lng: 77.59, available: false, car_ref: Flyweight_i20}
Driver_D: {name: "Driver_D", lat: 12.96, lng: 77.64, available: true, car_ref: Flyweight_XUV300}
Driver_E: {name: "Driver_E", lat: 12.92, lng: 77.62, available: true, car_ref: Flyweight_i20}

Total: 3 flyweight objects + 5 lightweight instances = 15 string objects (40% reduction!)
```

### Code Components

| Component | Purpose | Code Reference |
|-----------|---------|----------------|
| **CarsDataFlyWeight** | Stores intrinsic state (shared car data) | `class CarsDataFlyWeight` |
| **CarTypeFactory** | Creates and manages flyweight instances | `class CarTypeFactory` |
| **CarInstance** | Stores extrinsic state (driver-specific data) | `class CarInstance` |
| **generateMapHTML()** | Renders interactive Leaflet.js map | Line ~175 |
| **updateDriverPosition()** | Simulates GPS updates | Line ~285 |
| **displayCarStatus()** | Console output formatter | Line ~305 |
| **main()** | Orchestrates simulation loop | Line ~325 |

## 🐳 Docker Multi-Stage Build Explained

The Dockerfile uses a multi-stage build for optimal size:

```dockerfile
Stage 1: Builder (gcc:12-bullseye - ~1.2GB)
  ├── Compiles C++ with static linking
  └── Produces standalone binary

Stage 2: Runtime (alpine:3.19 - ~5MB)
  ├── Copies only the binary
  ├── Final image ~10MB total!
  └── No build tools, minimal attack surface
```

**Benefits:**
- 99% size reduction compared to single-stage
- No `apt-get update` on every build
- Secure - only contains the binary
- Fast startup and deployment

## Learning Outcomes

By exploring this project, you'll learn:

1. **Design Patterns**
   - When and why to use Flyweight
   - Separating intrinsic vs extrinsic state
   - Factory pattern for object management

2. **C++ Best Practices**
   - Modern C++17 features
   - Memory management with smart patterns
   - Threading and real-time simulation
   - File I/O and HTML generation

3. **DevOps Skills**
   - Multi-stage Docker builds
   - Volume mounts and data persistence
   - Cross-platform deployment

4. **Data Visualization**
   - Leaflet.js integration
   - Real-time map updates
   - Interactive UI design

## Real-World Applications

The Flyweight pattern is crucial in:

### Gaming
- **Particle Systems**: Share texture/sprite data
- **Terrain Rendering**: Reuse tile graphics
- **NPC Management**: Share behavior trees

### Text Editors
- **Character Formatting**: Share font/style objects
- **Syntax Highlighting**: Reuse token styles

### Networking
- **Connection Pools**: Share connection objects
- **Message Queues**: Reuse message templates

### CAD/Graphics Software
- **Geometric Primitives**: Share shape definitions
- **Material Libraries**: Reuse texture/shader data

### Enterprise Applications
- **Database ORMs**: Share entity metadata
- **Caching Systems**: String interning

## Contributing

Contributions are welcome! Here are some ideas:

- [ ] Add more car types and manufacturers
- [ ] Implement different map styles/themes
- [ ] Add route planning between drivers
- [ ] Create a REST API for real-time updates
- [ ] Add WebSocket support for live streaming
- [ ] Implement driver matching algorithm
- [ ] Add traffic simulation
- [ ] Create mobile app version

**To contribute:**
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## Further Reading

### Design Patterns
- [Flyweight Pattern - Refactoring Guru](https://refactoring.guru/design-patterns/flyweight)
- [Gang of Four Design Patterns Book](https://en.wikipedia.org/wiki/Design_Patterns)
- [Head First Design Patterns](https://www.oreilly.com/library/view/head-first-design/0596007124/)

### Technologies Used
- [Leaflet.js Documentation](https://leafletjs.com/) - Interactive mapping library
- [OpenStreetMap](https://www.openstreetmap.org/) - Free map tiles and data
- [Docker Multi-Stage Builds](https://docs.docker.com/build/building/multi-stage/)
- [C++17 Features](https://en.cppreference.com/w/cpp/17)

### Similar Projects
- Uber/Lyft driver tracking systems
- Fleet management applications
- Real-time logistics visualization
