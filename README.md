# AetherX

All code for this project is within Core/src. Detailed description coming soon

**Sensors:**

* LM61 - Temperature
* DHT20 - Relative humidity and temperature
* OPT101 - Light intensity at 650nm wavelength
* MAX9814 - Microphone with signal output

# TODO:
**General**
* Finish KiCad schematic (additional filtering for components)
* Update BOM
* Design and construct PCB

**Software**
* ADC internal voltage reference
* Get RTC working
* Standby mode (3 button presses?)
* Re-do reading functions with ADC rank (only do readings when displayed)
* Signal processing for MAX9814 (frequency data via FFT, sound level in dB)

**Future Work**
* Wireless daughter boards (STM32WB55, 3D print sphere case?)
* Data logging (>24hrs)