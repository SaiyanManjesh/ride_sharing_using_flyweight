# Quick Start Guide

## 📍 Project Location
**Windows Path:** `M:\Personal\learning\projects\ride_sharing_using_flyweight`

**WSL/Linux Path:** `/mnt/m/Personal/learning/projects/ride_sharing_using_flyweight`

---

## 🚀 Running the Application

### Windows (PowerShell)
```powershell
# Navigate to project
cd M:\Personal\learning\projects\ride_sharing_using_flyweight

# Run with script (easiest)
.\run.ps1

# OR compile and run manually
g++ -std=c++17 -Wall -Wextra -O2 -o ride_sharing_cars ride_sharing_cars.cpp
.\ride_sharing_cars.exe
```

### Linux/Mac/WSL
```bash
# Navigate to project
cd /mnt/m/Personal/learning/projects/ride_sharing_using_flyweight

# Run with script (easiest)
chmod +x run.sh
./run.sh

# OR compile and run manually
g++ -std=c++17 -Wall -Wextra -O2 -o ride_sharing_cars ride_sharing_cars.cpp
./ride_sharing_cars
```

---

## 🐳 Docker Commands

### Build Image
```bash
cd M:\Personal\learning\projects\ride_sharing_using_flyweight
docker build -t ride-sharing-app .
```

### Run Container (with volume mount to get HTML file)
**Windows PowerShell:**
```powershell
cd M:\Personal\learning\projects\ride_sharing_using_flyweight
docker run --rm -v ${PWD}:/app ride-sharing-app
```

**Linux/Mac/WSL:**
```bash
cd /mnt/m/Personal/learning/projects/ride_sharing_using_flyweight
docker run --rm -v $(pwd):/app ride-sharing-app
```

The `driver_map.html` will appear in your current directory!

---

## 📂 Generated Files

After running, you'll find:
- `driver_map.html` - Interactive map with real-time driver positions
- `ride_sharing_cars.exe` (Windows) or `ride_sharing_cars` (Linux) - Compiled binary

---

## 🌐 Viewing the Map

1. Run the application (see above)
2. The map will try to auto-open in your browser
3. If not, manually open `driver_map.html` from the project directory
4. The map refreshes every 3 seconds for 30 seconds total

---

## 📖 Full Documentation

See [README.md](README.md) for complete documentation including:
- Design pattern explanation
- Customization options
- Architecture details
- Troubleshooting guide
- Contributing guidelines
