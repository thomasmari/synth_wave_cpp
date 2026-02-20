# Synthetizer - `src` Directory

This directory contains the main source code for the Synthetizer project.

## Structure

- `main.cpp`         — Entry point of the application
- `ofApp.cpp/h`      — Main application logic (OpenFrameworks app)
- `Keyboard.cpp/h`   — Keyboard input and drawing
- `Oscillo.cpp/h`    — Oscillator (sound generation) logic

## Key Features
- Polyphonic and monophonic audio synthesis
- Real-time audio output and spectrum visualization
- Interactive keyboard and waveform controls
- Multiple oscillator modes: sine, square, saw, piano

## How to Install OpenFrameworks and Set Up the Project

### 1. Install OpenFrameworks

Follow the official instructions for your OS: https://openframeworks.cc/download/
Build the project generator as described in the OpenFrameworks site.

### 2. Create a New OpenFrameworks Project

Use the project generator (GUI or command line) to create a new project, e.g.:
```sh
cd openFrameworks/apps/myApps
./projectGenerator --create ./synthetizer
```

### 3. Copy the `src` Directory

Replace the generated `src` folder in your new project with this one:
```sh
cp -r /path/to/this/src /path/to/openFrameworks/apps/myApps/synthetizer/src
```

## How to Build

From your project directory:
```sh
make
make run
```

## How to Use
- Use the on-screen keyboard or your computer keyboard to play notes.
- Change oscillator mode using the UI toggles.
- Adjust volume and other parameters as needed.

## File Descriptions
- `ofApp.cpp/h`: Handles audio output, drawing, and user interaction.
- `Keyboard.cpp/h`: Manages keyboard state and rendering.
- `Oscillo.cpp/h`: Implements oscillator behavior and sound synthesis.
- `main.cpp`: Standard OpenFrameworks entry point.

## License
MIT License (or specify your license here)

---
For more details, see the main project README or documentation.
