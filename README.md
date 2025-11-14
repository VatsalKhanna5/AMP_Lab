# 🛰️ Pro Arduino Sensor Dashboard

[![Python](https://img.shields.io/badge/Python-3.9%2B-blue.svg)](https://www.python.org/downloads/)
[![Streamlit](https://img.shields.io/badge/Streamlit-1.30%2B-red.svg)](https://streamlit.io)
[![Plotly](https://img.shields.io/badge/Plotly-5.15%2B-purple.svg)](https://plotly.com/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE.md)

> A responsive, real-time web dashboard to monitor, visualize, and analyze live temperature and humidity data streamed directly from an Arduino.



---

## ✨ Key Features

* **🔴 Live Data Streaming:** Real-time serial communication between an Arduino Uno and a Streamlit web app using `pySerial`.
* **📊 Responsive Dashboard:** A beautiful, responsive interface built with Streamlit that looks great on both desktop and mobile.
* **📈 2D & 3D Visualizations:**
    * **Live 2D Plots:** Fast-updating line charts for temperature and humidity over time.
    * **Interactive 3D Plot:** A stunning Plotly 3D scatter plot visualizing Time, Temperature, and Humidity. The path is color-coded by temperature (blue-to-red) for at-a-glance analysis.
* **💡 Hardware-Level Indicators:** Three on-device LEDs (Blue, Green, Red) instantly show the current humidity level (Low, Medium, High).
* **🧠 Real-Time Analysis:** A dynamic "Interpretation" panel that gives plain-English insights based on the current environmental conditions.
* **⚙️ Configurable Sidebar:** A clean sidebar for navigation and full control over application settings:
    * Change Serial Port
    * Adjust Baud Rate
    * Control Data History Length
    * Set Plot Refresh Intervals
* **📋 Data Reporting:** A separate "Data Report" page with a full, sortable data log and descriptive statistics (mean, std, min, max) for your sensor data.

---

## 🛠️ Tech Stack & Hardware

| Category | Technology |
| :--- | :--- |
| **Hardware** | Arduino Uno R3, DHT11 Sensor, 3x LEDs (Blue, Green, Red), 3x 220Ω Resistors |
| **Backend/Comms** | Python, `pySerial` |
| **Frontend/Dashboard**| `Streamlit`, `streamlit-autorefresh` |
| **Data & Plotting** | `Pandas`, `Plotly` |

---

## 🔌 Hardware Setup

Before running the software, wire your components as follows.

| Component | Pin | Connects To |
| :--- | :--- | :--- |
| **DHT11** | VCC / + | Arduino `5V` |
| | Data | Arduino `Digital Pin 8` |
| | GND / - | Arduino `GND` |
| **Blue LED** | Long Leg (+) | Arduino `Digital Pin 11` |
| | Short Leg (-) | 220Ω Resistor ➡️ `GND` |
| **Green LED** | Long Leg (+) | Arduino `Digital Pin 12` |
| | Short Leg (-) | 220Ω Resistor ➡️ `GND` |
| **Red LED** | Long Leg (+) | Arduino `Digital Pin 13` |
| | Short Leg (-) | 220Ω Resistor ➡️ `GND` |



---

## 🚀 Getting Started

Follow these steps to get your dashboard running.

### 1. Prerequisites
* An Arduino IDE to upload the code to your board.
* Python 3.9 or newer.

### 2. Arduino Setup
1.  Open your `arduino_code.ino` file in your Arduino IDE.
2.  Make sure you have the required libraries installed (`DHT sensor library` by Adafruit).
3.  Connect your fully-wired Arduino to your computer.
4.  Select the correct Board (Arduino Uno) and Port.
5.  Click **Upload**.

### 3. Python Environment Setup
1.  **Clone this repository:**
    ```bash
    git clone https://github.com/VatsalKhanna5/AMP_Lab
    cd AMP_Lab
    ```
2.  **Create and activate a virtual environment:**
    ```bash
    # Windows
    python -m venv venv
    .\venv\Scripts\activate
    
    # macOS / Linux
    python3 -m venv venv
    source venv/bin/activate
    ```
3.  **Install the required libraries:**
    ```bash
    pip install streamlit pyserial pandas plotly streamlit-autorefresh
    ```
    *Note: You may need to run `pip install --upgrade plotly` to get the latest 3D plot features.*

### 4. Run the Dashboard
1.  Make sure your Arduino is plugged in.
2.  Find your Arduino's serial port (e.g., `COM8` on Windows, `/dev/ttyUSB0` on Linux).
3.  Run the Streamlit app:
    ```bash
    streamlit run app.py
    ```
4.  Your browser will open to the app. In the sidebar, **enter the correct Serial Port** and enjoy your live dashboard!

---

## 💡 Future Improvements

This project has a great foundation. Here are some ideas to take it even further:
* **Upgrade Sensor:** Replace the DHT11 with a **BME280** (adds Barometric Pressure) or **BME680** (adds Air Quality/VOC).
* **Go Wireless:** Use an **ESP32** or **ESP8266** instead of an Arduino to send data over Wi-Fi, removing the serial cable.
* **Persistent Logging:** Save data to a **SQLite database or CSV file** to analyze long-term trends.
* **Alerts:** Add email or push notifications for when temperature/humidity crosses a critical threshold.
