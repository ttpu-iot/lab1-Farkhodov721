[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/vXLQl-Px)
# IoT 2025 - Lab 1 Template

You need to finish following 6 exercises

Configuration:
- RED - D15
- Green - D4
- Blue - D22
- Yellow - D23
- button - D14
- light sensor - D33



## 1) Blink RED LED
- Turn **RED (D15)** ON for 500 ms, then OFF for 500 ms in a loop.  
- Serial: Print `RED ON` / `RED OFF` whenever it changes.

---

## 2) Button toggles GREEN
- Press **BUTTON (D14)** to toggle **GREEN (D4)**.  
- Serial: Print `GREEN=1` or `GREEN=0` only when the state changes.

---

## 3) Read light sensor
- Every 500 ms, read **LIGHT (D33)** using `analogRead()`.  
- Serial: Print the raw value, e.g. `raw=1835`.

---

## 4) Light sensor -> LED band
- Read **LIGHT (D33)** and turn ON exactly one LED based on value (0–4095):  
  - 0–1023 → **BLUE (D22)**  
  - 1024–2047 → **GREEN (D4)**  
  - 2048–3071 → **YELLOW (D23)**  
  - 3072–4095 → **RED (D15)**  
- Serial: Print `band=BLUE/GREEN/YELLOW/RED`.

---

## 5) Snapshot on button
- Do nothing until **BUTTON (D14)** is pressed.  
- On press, read **LIGHT (D33)** once and print `snapshot=xxxx`.  
- Flash **YELLOW (D23)** for 100 ms to acknowledge (change 100ms if needed)

---

## 6) Minimal serial control
- If serial receives a character:  
  - `'B'` → turn **BLUE (D22)** ON  
  - `'b'` → turn **BLUE (D22)** OFF  
- Serial: Print `BLUE=1` or `BLUE=0` after each command.

