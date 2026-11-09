# AquaSense – Smart Water Quality Monitoring System

## Overview

AquaSense is an IoT-based water quality monitoring system that combines a compact hardware device with a web-based monitoring platform to make everyday water quality assessment more accessible.

The hardware device integrates three sensors — turbidity, pH, and Total Dissolved Solids (TDS) — into a single compact black enclosure. It measures key water quality parameters and displays the readings through an attached LED display.

The accompanying web application provides a detailed interpretation of the collected measurements, information about potential water-related hazards, and location-based water quality visualization through an interactive heatmap. It helps users understand water quality conditions in their surroundings and stay informed about potential concerns.

AquaSense aims to bridge the gap between physical water testing and accessible digital water quality monitoring.

## Key Features

### 1. Multi-Parameter Water Quality Monitoring
- Integrates turbidity, pH, and TDS sensors into a single hardware unit.
- Measures three important indicators of water quality.
- Displays sensor readings directly on an attached LED display.
- Uses a compact enclosure to combine the sensing components into a portable device.

### 2. Multiple Connectivity Options
Implements multiple communication methods for transferring sensor readings to the web application:

- **ESP32 Wi-Fi:** Wireless transmission of sensor readings.
- **Bluetooth:** Wireless data communication.
- **USB:** Wired device connectivity and data transfer.
- **Manual Input:** Allows users to enter water quality measurements directly through the web application.

### 3. Web-Based Water Quality Monitoring
- Provides a centralized dashboard for monitoring water quality measurements.
- Displays turbidity, pH, and TDS readings in an understandable format.
- Provides descriptive insights to help users interpret measured values.
- Presents relevant water quality information and potential hazards.

### 4. Location-Based Water Quality Heatmap
- Visualizes water quality warnings across geographical locations.
- Provides a map-based representation of water quality conditions in the user's surroundings.
- Helps users identify potential water quality concerns in nearby areas.
- Supports location-based awareness of everyday water quality conditions.

### 5. Water Safety Awareness
- Provides informative facts about water quality and contamination.
- Highlights potential water-related hazards.
- Keeps users informed through relevant water safety information.
- Encourages informed decisions regarding everyday water usage.

## Hardware Components

| Component | Purpose |
|---|---|
| Turbidity Sensor | Measures water clarity and suspended particles |
| pH Sensor | Measures the acidity or alkalinity of water |
| TDS Sensor | Estimates the concentration of dissolved solids |
| ESP32 | Supports wireless connectivity and data communication |
| LED Display | Displays water quality measurements |
| Enclosure | Integrates the hardware components into a compact unit |

## System Architecture

AquaSense follows a hardware-to-web application workflow:

1. **Water Sampling:** The device is used to collect measurements from a water sample.
2. **Sensor Measurement:** Turbidity, pH, and TDS sensors measure their respective parameters.
3. **Data Processing:** The hardware processes the collected sensor readings.
4. **Local Display:** The measurements are displayed through the integrated LED display.
5. **Data Transmission:** Readings are transferred to the web application using ESP32 Wi-Fi, Bluetooth, or USB. Manual input is also supported.
6. **Web-Based Analysis:** The application presents the readings along with descriptive water quality insights and hazard information.
7. **Geographical Visualization:** Location-based water quality information is represented through an interactive heatmap.

## Water Quality Parameters

| Parameter | What It Indicates |
|---|---|
| Turbidity | Water clarity and suspended particles |
| pH | Acidity or alkalinity |
| TDS | Estimated concentration of dissolved solids |

Together, these parameters provide useful indicators for preliminary water quality assessment.

## Application and Use Cases

AquaSense is designed to support:

- Preliminary water quality assessment.
- Everyday water quality awareness.
- Monitoring and interpretation of sensor measurements.
- Location-based awareness of potential water quality issues.
- Access to water safety information and contamination-related facts.

## Future Scope

- Integration of additional sensors for detecting specific contaminants.
- Cloud-based storage of historical water quality measurements.
- Long-term water quality trend analysis.
- Expansion of geographical water quality mapping.
- Community-based water quality reporting.
- Automated notifications for abnormal sensor readings.
- Predictive analysis of water quality trends.

## Project Limitations

AquaSense measures turbidity, pH, and TDS, which provide useful but limited information about water quality. These parameters alone cannot establish whether water is safe for drinking or detect all harmful microorganisms, heavy metals, and chemical contaminants.

The device is intended for preliminary monitoring and awareness. Laboratory testing and appropriate certified methods are required to establish drinking water safety.


**AquaSense — Making everyday water quality information accessible through connected hardware and intelligent monitoring.**
