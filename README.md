<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&amp;color=0:00e1ff,100:0055ff&amp;height=200&amp;section=header&amp;text=kde-auto-rotate&amp;fontSize=45&amp;fontAlignY=35&amp;animation=fadeIn&amp;fontColor=ffffff"/>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/-C-A8B9CC?logo=c&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-GNUBash-4EAA25?logo=gnubash&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-Linux-FCC624?logo=linux&amp;logoColor=black&amp;style=for-the-badge"/>
</p>

<p align="center">
  <b>Auto-rotate screen utility for KDE on Linux</b>
</p>

---

## 🐧 Overview

A C program and systemd service that auto-rotates the screen on KDE based on the laptop's physical orientation, using sensor data (accelerometer) and GLib/GIO.

---

## 🛠️ How It Works

```mermaid
flowchart LR
    A[Accelerometer Sensor] --> B[auto-rotate\nC Program]
    B --> C[KDE Screen Rotation]
    D[systemd Service] --> B
```

---

## 🚀 Tech Stack

<img src="https://img.shields.io/badge/-C-A8B9CC?logo=c&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-GNUBash-4EAA25?logo=gnubash&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-GLib-003E7E?logo=glib&amp;logoColor=white&amp;style=for-the-badge"/> <img src="https://img.shields.io/badge/-systemd-0066CC?logo=systemd&amp;logoColor=white&amp;style=for-the-badge"/>

---

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=soft&amp;color=0:00e1ff,100:0055ff&amp;height=100&amp;section=footer&amp;text=rotate%20with%20grace&amp;fontSize=20&amp;fontAlignY=50&amp;fontColor=ffffff"/>
</p>
