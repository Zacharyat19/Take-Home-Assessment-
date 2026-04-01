# Device Monitor Dashboard

A desktop application that simulates and visualizes real-time sensor data, including temperature, humidity, and pressure.

## Technology Choice
**Option C: C++ (C++17) with Qt 6 Widgets and Qt Charts**

**Reason for choice:** C++ was selected because it provides strict, deterministic control over memory and object lifecycles, which is highly advantageous when developing for embedded systems or hardware-adjacent applications. The Qt 6 framework was chosen because its Meta-Object System natively enforces a clean decoupling between the underlying data generation and the graphical user interface.

## Build and Run Instructions
This project is built using CMake and requires Qt 6. The following instructions are for a Debian/Ubuntu-based Linux environment (including WSL).

### 1. Install Dependencies
A C++ build environment, the core Qt 6 libraries, and the Qt Charts module are required to compile the application:

    sudo apt update
    sudo apt install build-essential cmake qt6-base-dev libgl1-mesa-dev libqt6charts6-dev

### 2. Compile the Project
Navigate to the root directory of the project (where the `CMakeLists.txt` is located) and generate the build system:

    # Clear any old cache files if rebuilding
    rm -rf CMakeCache.txt CMakeFiles dashboard_autogen

    # Generate build files
    cmake .

    # Compile the executable
    make

### 3. Run the Application
Execute the compiled binary:

    ./dashboard

## Code Architecture
The project is strictly separated into data and presentation layers to maintain modularity. The files are organized into `Inc/` (headers) and `Src/` (implementations) directories.

* **`Sensor` Class (`Inc/Sensor.h`, `Src/Sensor.cpp`):** The data layer. This class acts as the backend hardware simulation. It manages its own internal timer and state. It is entirely agnostic to the UI and broadcasts randomly generated sensor data using mathematical boundaries.
* **`DashboardWindow` Class (`Inc/DashboardWindow.h`, `Src/DashboardWindow.cpp`):** The presentation layer. This class inherits from `QMainWindow` and manages all layout widgets, buttons, dropdowns, and the Qt Chart. It subscribes to the sensor data and updates the visual elements dynamically.
* **`main.cpp`:** The application entry point. It initializes the Qt event loop, allocates the `DashboardWindow`, and executes the application.

## Features Implemented
* **Simulated Sensors:** Generates mock data for Temperature, Humidity, and Pressure.
* **Live Charting:** Displays a scrolling line chart of the last 30 data points using `QtCharts`.
* **Interactive Controls:** Includes a Start/Stop toggle for the simulation, a slider to adjust the warning threshold, and a dropdown menu to dynamically swap which sensor is currently rendered on the chart.
* **Visual Warnings:** Text indicators dynamically change color if the warning threshold is exceeded.

## Design Patterns
* **Observer Pattern:** Used extensively via Qt's Signal and Slot mechanism to decouple the logic and UI. The `Sensor` acts as the Subject, emitting a `dataReady` signal. The `DashboardWindow` acts as the Observer, connecting anonymous lambda slots to update the GUI only when new data arrives.

## Architecture Diagram

    +-------------------+                          +--------------------------+
    |   Data Layer      |      (Observer Pattern)  |   Presentation Layer     |
    |                   |                          |                          |
    |  +-------------+  |      dataReady(value)    |  +--------------------+  |
    |  | Sensor      |--|------- [SIGNAL] -------->|--| DashboardWindow    |  |
    |  | (Temp)      |  |                          |  | - Updates Labels   |  |
    |  +-------------+  |                          |  | - Evaluates Warns  |  |
    |                   |      dataReady(value)    |  | - Manages QChart   |  |
    |  +-------------+  |------- [SIGNAL] -------->|  +--------------------+  |
    |  | Sensor      |  |                          |         |        |       |
    |  | (Humidity)  |  |                          |         v        v       |
    |  +-------------+  |      dataReady(value)    |    [QComboBox] [QSlider] |
    |                   |------- [SIGNAL] -------->|    (Controls)  (Limits)  |
    |  +-------------+  |                          |                          |
    |  | Sensor      |  |                          |                          |
    |  | (Pressure)  |  |                          |                          |
    |  +-------------+  |                          |                          |
    +-------------------+                          +--------------------------+

## Known Issues & Future Improvements
If given more time, the following improvements would be prioritized:
* **Data Export:** Add a feature to record the sensor broadcasts to a standard `.csv` file for external logging and analysis.
* **Unit Testing:** Implement a testing framework like GoogleTest or QtTest to verify the mathematical boundaries and timer execution of the `Sensor` class independent of the GUI.
* **Theming:** Add a toggle to switch the Qt application palette and chart visual theme to a darker mode for better visibility in low-light environments.
