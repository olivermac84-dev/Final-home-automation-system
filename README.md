# 🏠 Arduino Smart Home Lighting System

A complete **Arduino Nano–based smart home system** featuring automatic and manual control, motion sensing, light detection, remote operation, and buzzer feedback.

---

## ✨ Features
- ✅ Auto / Manual mode with push-button & IR remote toggle  
- 🌙 Day/Night detection using LDR  
- 🚶 Motion detection with LED indicator  
- 💡 5 controllable room lights (4 rooms + dining)  
- 🔔 Buzzer sounds for system events  
- 🎛️ Remote works in both Auto & Manual modes  
- ⚡ Power-saving logic for night-time operation  
- 💚 Green LED → Auto mode | 💛 Yellow LED → Manual mode  
- 🔵 System LED → blinking when system is ON  

---

## 🧩 Components

| Component | Quantity | Description |
|------------|-----------|-------------|
| Arduino Nano | 1 | Main controller |
| IR Remote + Receiver | 1 | Control lights and mode |
| IR / PIR Motion Sensor | 1 | Detect motion |
| LDR Sensor | 1 | Detect day/night |
| LEDs (Room Lights) | 5 | Room indicators |
| Motion Indicator LED | 1 | Lights up when motion detected |
| Green LED | 1 | Shows Auto mode |
| Yellow LED | 1 | Shows Manual mode |
| System LED | 1 | Blinks to show system ON |
| Buzzer | 1 | Audio feedback |
| Push Button | 1 | Switch Auto/Manual mode |
| Resistors | Several | 220 Ω for LEDs, 10 kΩ for LDR divider |
| Jumper Wires / Breadboard | – | Connections |

---

## ⚙️ Pin Configuration

| Function | Arduino Pin |
|-----------|--------------|
| Motion Sensor Input | D2 |
| Dining LED | D3 |
| Room 2 LED | D4 |
| Room 3 LED | D5 |
| Room 4 LED | D6 |
| Room 5 LED | D7 |
| Mode Button | D8 |
| Buzzer | D9 |
| System LED | D10 |
| IR Receiver | D11 |
| Green (Auto) LED | D12 |
| Yellow (Manual) LED | D13 |
| Motion Indicator LED | D14 (or any free pin) |
| LDR Sensor | A0 |

---

## 🕹️ IR Remote Key Mapping

| Button | Function |
|--------|-----------|
| `0xFF30CF` | Toggle Dining LED |
| `0xFF18E7` | Toggle Room 2 LED |
| `0xFF7A85` | Toggle Room 3 LED |
| `0xFF10EF` | Toggle Room 4 LED |
| `0xFF38C7` | Toggle Room 5 LED |
| `0xFF5AA5` | Toggle Auto / Manual Mode |

> 💡 You can reassign these codes to match your remote.  
> Open the **Serial Monitor** (9600 bps) to read new IR codes.

---

## 🚦 System Behavior

### **AUTO Mode (Green LED ON)**
- System automatically activates at night (based on LDR).  
- On first motion → all lights ON + short beep.  
- On second motion → dining light OFF only + long beep.  
- Motion LED lights up when motion detected.  
- Lights stay ON (not forced off) unless manually toggled.  

### **MANUAL Mode (Yellow LED ON)**
- IR remote toggles each LED independently.  
- Auto rules disabled until mode is switched back.  

---

## 🔊 Buzzer Feedback

| Event | Beep Pattern |
|--------|---------------|
| Power ON | 2 short beeps |
| Button pressed / Mode toggled | 1 short beep |
| Motion detected | 1 short beep |
| Dining light auto-OFF | 1 long beep |
| Day/Night change | 1 short beep |

---

## 🪄 Usage Instructions

1. Upload the Arduino sketch to your Nano.  
2. Wire components as shown in **Pin Configuration**.  
3. Power the Nano (USB / 5 V).  
4. System beeps twice on startup.  
5. Use the push button or IR remote to switch between **Auto** and **Manual**.  
6. In Auto mode, the system works automatically at night.  
7. Observe LED indicators:  
   - 💚 Auto → Green LED ON  
   - 💛 Manual → Yellow
