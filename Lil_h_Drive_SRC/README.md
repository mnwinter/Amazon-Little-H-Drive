# Lil H Drive

Small Kiva‑style H‑drive robot using ESP32‑S3 DevKit‑C, DRV8833 motor drivers, and a simple Wi‑Fi web UI.

> Board: **ESP32‑S3 DevKit‑C** (status RGB on **GPIO 48**)  
> Control: Web UI (served from ESP32) — no BLE required

## Features
- Split-file Arduino project (`.ino` + modules)
- Minimal dependency: uses built‑in `WebServer` (no Async libs)
- Web UI served from PROGMEM (no SPIFFS/LittleFS needed)
- REST‑style endpoint: `/api/drive?x=&y=&rot=&lift=` returns JSON
- Clear pin map in `config.h`

## Folder layout
```
Lil_h_Drive/
├─ Lil_h_Drive.ino        # main entry
├─ config.h               # pins, constants, wifi creds
├─ motor_control.h/.cpp   # drive + lift control
├─ web_server.h/.cpp      # http routes + handlers
├─ ui_html.h/.cpp         # index_html (PROGMEM)
├─ LICENSE
└─ .gitignore
```

## Quick start
1. Open `Lil_h_Drive.ino` in Arduino IDE.
2. Select **ESP32S3 Dev Module** (DevKit‑C) and correct COM port.
3. Edit `config.h`:
   - Wi‑Fi SSID / password
   - Pin assignments for your wiring
4. Upload. The serial monitor prints the device IP address.
5. Open the IP in a browser to use the web UI.

## API
- `GET /` — HTML UI
- `GET /api/drive?x=-100..100&y=-100..100&rot=-100..100&lift=-100..100`
  - Returns: `{"ok":true, "x":0, "y":0, "rot":0, "lift":0}`

## Notes
- If your motors spin backwards or axes are swapped, tweak the
  `MOTOR_INVERT_*` flags in `config.h`.
- All logic stubs compile even if you haven’t set pins yet.
