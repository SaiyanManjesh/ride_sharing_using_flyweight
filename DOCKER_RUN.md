# Docker Quick Reference

## 🚀 Run with Interactive Map (Recommended)

This mounts your current directory into the container so the HTML map file appears on your host machine.

### Windows (PowerShell)
```powershell
docker build -t ride-sharing-app .
docker run --rm -v ${PWD}:/app ride-sharing-app
```

### Linux/Mac (Bash)
```bash
docker build -t ride-sharing-app .
docker run --rm -v $(pwd):/app ride-sharing-app
```

### What happens:
1. Container runs the simulation (binary is in `/usr/local/bin`)
2. Working directory is `/app` 
3. Your current directory is mounted to `/app`
4. `driver_map.html` is created in `/app` (the working directory)
5. **The file appears in your flyweight directory immediately!** 🎉
6. The file updates every 3 seconds - just refresh your browser!

---

## 📂 File Locations

| Location | Description |
|----------|-------------|
| **Inside Container** | `/app/driver_map.html` |
| **On Your Machine** | `./driver_map.html` (your current directory) |

---

## 💡 Tips

- **Keep the browser tab open** and refresh to see updated positions
- **Or use auto-refresh extension** in your browser
- The simulation runs for 30 seconds (10 updates × 3 seconds)
- You'll see console output showing driver positions each update

---

## 🐛 Troubleshooting

**Q: I don't see driver_map.html on my machine**
- Make sure you used the `-v` flag to mount the volume
- Check you're in the right directory when you run the docker command
- Windows users: Use PowerShell, not CMD

**Q: The browser shows "sh: xdg-open: not found"**
- This is normal! Docker containers don't have browsers
- Just open the `driver_map.html` file manually from your current directory

**Q: The map doesn't update in my browser**
- The file updates every 3 seconds
- Refresh your browser manually, or the page will auto-reload

---

## 🎯 Example Session

```bash
PS M:\Personal\learning\projects\ride_sharing_using_flyweight> docker build -t ride-sharing-app .
[+] Building 45.2s (12/12) FINISHED

PS M:\Personal\learning\projects\ride_sharing_using_flyweight> docker run --rm -v ${PWD}:/app ride-sharing-app

🚗 Ride Sharing App - Real-Time Driver Tracking
================================================

=== Live Driver Positions ===
🟢 Driver_A -> Maruti Swift (Hatchback, Petrol, KA) @ (12.9716, 77.5946)
🟢 Driver_B -> Maruti Swift (Hatchback, Petrol, KA) @ (12.9352, 77.6245)

🗺️  Map saved to: driver_map.html (in current directory)
💡 Running in Docker? Open driver_map.html from your mounted directory!
```

**Then open `driver_map.html` in your browser!** 🎉
