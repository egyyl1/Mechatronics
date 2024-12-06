#include <stdio.h>
#include <stdlib.h>

// Constants
#define VREF 5.0      // Reference voltage
#define ADC_RES 1024  // ADC resolution

// Function prototypes
double adcToVoltage(int adcValue);
double thermistorTemperature(double voltage);
double thermocoupleTemperature(double voltage);

int main() {
    int adcA0, adcA1;
    double voltageA0, voltageA1, tempThermistor, tempThermocouple;

    // Prompt user for ADC values
    printf("Enter ADC value for A0 (thermocouple, 0-1023): ");
    scanf("%d", &adcA0);

    printf("Enter ADC value for A1 (thermistor, 0-1023): ");
    scanf("%d", &adcA1);

    // Convert ADC values to voltages
    voltageA0 = adcToVoltage(adcA0);
    voltageA1 = adcToVoltage(adcA1);

    // Calculate temperatures
    tempThermocouple = thermocoupleTemperature(voltageA0);
    tempThermistor = thermistorTemperature(voltageA1);

    // Display results
    printf("Thermocouple Temperature: %.2f°C\n", tempThermocouple);
    printf("Thermistor Temperature: %.2f°C\n", tempThermistor);

    return 0;
}

// Convert ADC value to voltage
double adcToVoltage(int adcValue) {
    return (adcValue * VREF) / ADC_RES;
}

// Calculate thermistor temperature (example formula, adjust as needed)
double thermistorTemperature(double voltage) {
    // Example: Using the Steinhart-Hart equation or another mapping
    // Adjust coefficients based on sensor's data sheet
    double resistance = (10000 * voltage) / (VREF - voltage);  // Assuming a 10k pull-up resistor
    double tempK = 1.0 / (0.001129148 + (0.000234125 * log(resistance)) + (0.0000000876741 * pow(log(resistance), 3)));
    return tempK - 273.15;  // Convert Kelvin to Celsius
}

// Calculate thermocouple temperature (example formula, adjust as needed)
double thermocoupleTemperature(double voltage) {
    // Example: Linear approximation, adjust as needed
    return (voltage / 0.005);  // Assuming 5 mV/°C
}
