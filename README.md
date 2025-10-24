## ⚙️ How the System Works

The Smart Home Lighting System is designed to operate in two intelligent modes: **Auto Mode** and **Manual Mode**.  
Both modes can be switched using the **push button** or **IR remote**.

---

### 🟢 AUTO MODE (Green LED ON)
Auto mode enables **automatic light and motion control** using the LDR and IR proximity sensor.

#### 🌙 Night Detection (LDR)
- The LDR monitors ambient light level.
- When light level is low (nighttime), the system becomes active.
- During the day, all auto functions pause to save power.

#### 🚶 Motion Detection (IR Proximity Sensor)
- When motion is detected at night, all lights turn **ON** (first detection).
- When motion is detected again, only the **Dining Room LED** turns **OFF** (second detection).
- A **motion indicator LED** (red) lights up while motion is present.
- Buzzer gives a short beep when motion is detected.

#### 💡 Auto Light Rules
| Event | Action |
|--------|--------|
| First motion detected (night) | Turn ON all lights + short beep |
| Second motion detected (night) | Turn OFF dining light + long beep |
| No motion | Keep other lights ON |
| Daytime | System ignores motion (power saving) |

#### 🔋 Power Saving
- System LED blinks to show the system is alive.
- LDR automatically disables unnecessary night logic during daytime.
- No motion = minimal energy use.

---

### 🟡 MANUAL MODE (Yellow LED ON)
Manual mode allows **full control through the IR remote**.

#### 🎛️ Remote Control
Each remote button toggles individual lights:
| Button Code | Function |
|--------------|-----------|
| `0xFF30CF` | Toggle Room 1 |
| `0xFF18E7` | Toggle Room 2 |
| `0xFF7A85` | Toggle Room 3 |
| `0xFF10EF` | Toggle Room 4 |
| `0xFF38C7` | Toggle Dining |
| `0xFF5AA5` | Switch between Auto / Manual |

- Lights stay in their current state until toggled again.
- No automatic behavior in this mode.

---

### 🔔 BUZZER FEEDBACK SUMMARY
| Event | Sound |
|--------|--------|
| Power ON | Two short beeps |
| Mode Change | One short beep |
| Motion Detected | One short beep |
| Dining Light Auto OFF | One long beep |
| Day/Night Transition | One short beep |

---

### 🔵 SYSTEM INDICATORS
| Indicator | Function |
|------------|-----------|
| Blue LED | System ON (blinking) |
| Green LED | Auto Mode Active |
| Yellow LED | Manual Mode Active |
| Red LED | Motion Detected |

---

### 🧠 Overall Logic Flow
1. System powers ON → buzzer beeps twice → System LED blinks.  
2. LDR checks light → decides if day or night.  
3. If night → IR proximity sensor becomes active.  
4. When motion detected:
   - First trigger → all lights ON.
   - Second trigger → dining OFF.
5. IR remote or button can switch modes anytime.  
6. Manual mode allows individual control of each light.  
7. Auto mode resumes when toggled back.

---

### 🪄 Example Scenario
- At night, the system is in **Auto mode**.  
- You walk into the room → **all lights turn ON**.  
- You move again → **only dining light turns OFF**.  
- In the morning, the system detects daylight → **auto functions pause**.  
- You can always switch to **Manual mode** via button or remote for full control.

---

This system blends **automation, manual flexibility, and smart feedback** for an energy-efficient, responsive home lighting experience.
