#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <thread>
#include <chrono>
#include <iomanip>

//
// ============================
// FLYWEIGHT
// ============================
//

class CarsDataFlyWeight
{
private:

    const std::string brand;
    const std::string model;
    const std::string body_type;
    const std::string fuel_type;
    const std::string registration_state;

public:

    CarsDataFlyWeight(
        const std::string& brand,
        const std::string& model,
        const std::string& body_type,
        const std::string& fuel_type,
        const std::string& registration_state)
        :
        brand(brand),
        model(model),
        body_type(body_type),
        fuel_type(fuel_type),
        registration_state(registration_state)
    {
    }

    std::string getInfo() const
    {
        return brand + " " + model +
               " (" + body_type +
               ", " + fuel_type +
               ", " + registration_state + ")";
    }
};

//
// ============================
// FACTORY
// ============================
//

class CarTypeFactory
{
private:

    std::map<std::string, CarsDataFlyWeight*> cars_;

    std::string build_key(
        const std::string& brand,
        const std::string& model,
        const std::string& body_type,
        const std::string& fuel_type,
        const std::string& registration_state)
    {
        return brand + "|" +
               model + "|" +
               body_type + "|" +
               fuel_type + "|" +
               registration_state;
    }

public:

    CarsDataFlyWeight* get_car_type(
        const std::string& brand,
        const std::string& model,
        const std::string& body_type,
        const std::string& fuel_type,
        const std::string& registration_state)
    {
        std::string key =
            build_key(
                brand,
                model,
                body_type,
                fuel_type,
                registration_state);

        if (cars_.find(key) == cars_.end())
        {
            cars_[key] =
                new CarsDataFlyWeight(
                    brand,
                    model,
                    body_type,
                    fuel_type,
                    registration_state);

            std::cout
                << "Created Flyweight: "
                << key
                << std::endl;
        }

        return cars_[key];
    }

    ~CarTypeFactory()
    {
        for (auto& pair : cars_)
        {
            delete pair.second;
        }
    }
};

//
// ============================
// CONTEXT
// ============================
//

class CarInstance
{
public:

    double latitude;
    double longitude;
    bool availability;
    std::string driver;

    CarsDataFlyWeight* intrinsic_cars_data;

    CarInstance(
        const std::string& driver_name,
        double lat,
        double lng,
        bool availability,
        CarsDataFlyWeight* data)
        :
        latitude(lat),
        longitude(lng),
        availability(availability),
        driver(driver_name),
        intrinsic_cars_data(data)
    {
    }
};

//
// ============================
// MAP GENERATION
// ============================
// Generates an interactive HTML map with Leaflet.js
// File is written to current directory:
//   - Local run: Your current directory
//   - Docker with -v: Your mounted directory (appears on host)
//   - Docker without -v: Inside container at /app
//

void generateMapHTML(const std::vector<CarInstance*>& cars)
{
    if (cars.empty())
    {
        std::cout << "No cars to display!" << std::endl;
        return;
    }

    // Calculate center point (average of all positions)
    double center_lat = 0.0, center_lng = 0.0;
    for (const auto& car : cars)
    {
        center_lat += car->latitude;
        center_lng += car->longitude;
    }
    center_lat /= cars.size();
    center_lng /= cars.size();

    // Write to current directory (will be visible in mounted volume)
    std::string filename = "driver_map.html";
    std::ofstream html_file(filename);
    
    if (!html_file.is_open())
    {
        std::cerr << "❌ Failed to create " << filename << std::endl;
        return;
    }
    
    html_file << R"(<!DOCTYPE html>
<html>
<head>
    <title>Ride Sharing - Live Driver Locations</title>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
    <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
    <style>
        body { margin: 0; padding: 0; font-family: Arial, sans-serif; }
        #map { height: 100vh; width: 100%; }
        .driver-marker { 
            font-size: 24px; 
            text-align: center;
        }
        .driver-label {
            background: white;
            border: 2px solid #333;
            border-radius: 5px;
            padding: 5px 10px;
            font-weight: bold;
            box-shadow: 0 2px 5px rgba(0,0,0,0.3);
        }
    </style>
</head>
<body>
    <div id="map"></div>
    <script>
        var map = L.map('map').setView([)" << std::fixed << std::setprecision(6) 
              << center_lat << ", " << center_lng << R"(], 13);
        
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
            maxZoom: 19,
            attribution: '© OpenStreetMap contributors'
        }).addTo(map);

        var carIcon = L.divIcon({
            className: 'driver-marker',
            html: '🚗',
            iconSize: [100, 100],
            iconAnchor: [50, 50]
        });

        var unavailableIcon = L.divIcon({
            className: 'driver-marker',
            html: '🚙',
            iconSize: [100, 100],
            iconAnchor: [50, 50]
        });
)";

    // Add markers for each driver
    for (const auto& car : cars)
    {
        html_file << "        L.marker([" 
                  << std::fixed << std::setprecision(6)
                  << car->latitude << ", " << car->longitude 
                  << "], {icon: " 
                  << (car->availability ? "carIcon" : "unavailableIcon")
                  << "})\n"
                  << "         .bindPopup('<div class=\"driver-label\">"
                  << "<b>" << car->driver << "</b><br>"
                  << (car->availability ? "🟢 Available" : "🔴 Busy") << "<br>"
                  << car->intrinsic_cars_data->getInfo()
                  << "</div>')\n"
                  << "         .bindTooltip('" << car->driver << "', {permanent: true, direction: 'top'})\n"
                  << "         .addTo(map);\n\n";
    }

    html_file << R"(
        // Auto-refresh every 3 seconds
        setTimeout(function() {
            location.reload();
        }, 3000);
    </script>
</body>
</html>)";

    html_file.close();
    
    std::cout << "\n🗺️  Map saved to: " << filename << " (in current directory)" << std::endl;
    
    // Try to open in browser (will silently fail in Docker/headless environments)
    static bool first_open = true;
    if (first_open)
    {
#ifdef _WIN32
        std::cout << "Opening in browser..." << std::endl;
        system("start driver_map.html 2>nul");
#elif __APPLE__
        std::cout << "Opening in browser..." << std::endl;
        system("open driver_map.html 2>/dev/null");
#else
        // Check if we can open a browser (not in Docker/headless)
        int result = system("command -v xdg-open >/dev/null 2>&1");
        if (result == 0)
        {
            std::cout << "Opening in browser..." << std::endl;
            system("xdg-open driver_map.html 2>/dev/null &");
        }
        else
        {
            std::cout << "💡 Running in Docker? Open driver_map.html from your mounted directory!" << std::endl;
        }
#endif
        first_open = false;
    }
}

//
// ============================
// REAL-TIME SIMULATION
// ============================
//

void updateDriverPosition(CarInstance* car, std::mt19937& rng)
{
    std::uniform_real_distribution<> lat_drift(-0.005, 0.005);
    std::uniform_real_distribution<> lng_drift(-0.005, 0.005);
    
    car->latitude += lat_drift(rng);
    car->longitude += lng_drift(rng);
    
    // Randomly toggle availability
    std::uniform_int_distribution<> avail_dist(0, 10);
    if (avail_dist(rng) > 7)
    {
        car->availability = !car->availability;
    }
}

void displayCarStatus(const std::vector<CarInstance*>& cars)
{
    std::cout << "\n=== Live Driver Positions ===\n";
    std::cout << std::fixed << std::setprecision(4);
    
    for (const auto& car : cars)
    {
        std::cout
            << (car->availability ? "🟢 " : "🔴 ")
            << car->driver
            << " -> "
            << car->intrinsic_cars_data->getInfo()
            << " @ ("
            << car->latitude
            << ", "
            << car->longitude
            << ")"
            << std::endl;
    }
}

//
// ============================
// MAIN
// ============================
//

int main()
{
    // Random number generator for simulation
    std::random_device rd;
    std::mt19937 rng(rd());
    
    CarTypeFactory factory;

    //
    // Create Flyweights
    //

    auto swift =
        factory.get_car_type("Maruti", "Swift", "Hatchback","Petrol", "KA");

    auto i20 =
        factory.get_car_type("Hyundai", "i20", "Hatchback", "Diesel", "KA");
    
    auto xuv300 =
        factory.get_car_type("Mahindra", "XUV300", "SUV", "Diesel", "KA");

    //
    // Create Instances with initial positions in Bangalore
    //

    std::vector<CarInstance*> cars;

    cars.push_back(
        new CarInstance("Driver_A", 12.9716, 77.5946, true, swift));

    cars.push_back(
        new CarInstance("Driver_B", 12.9352, 77.6245, true, swift));

    cars.push_back(
        new CarInstance("Driver_C", 13.0358, 77.5970, false, i20));
    
    cars.push_back(
        new CarInstance("Driver_D", 12.9698, 77.6480, true, xuv300));
    
    cars.push_back(
        new CarInstance("Driver_E", 12.9279, 77.6271, true, i20));

    std::cout << "\n Ride Sharing App - Real-Time Driver Tracking\n";
    std::cout << "================================================\n";
    
    //
    // Real-time simulation loop
    //
    
    int update_count = 0;
    const int max_updates = 10; // Run for 10 updates (30 seconds)
    
    while (update_count < max_updates)
    {
        // Display current status
        displayCarStatus(cars);
        
        // Generate and open map in browser
        generateMapHTML(cars);
        
        std::cout << "⏱️  Update " << (update_count + 1) 
                  << "/" << max_updates 
                  << " (Next update in 3 seconds...)\n";
        std::cout << "Press Ctrl+C to stop\n";
        std::cout << "----------------------------------------\n";
        
        // Wait 3 seconds
        std::this_thread::sleep_for(std::chrono::seconds(3));
        
        // Update all driver positions
        for (auto& car : cars)
        {
            updateDriverPosition(car, rng);
        }
        
        update_count++;
    }
    
    std::cout << "\nSimulation complete!\n";

    //
    // Cleanup
    //

    for (auto car : cars)
    {
        delete car;
    }

    return 0;
}