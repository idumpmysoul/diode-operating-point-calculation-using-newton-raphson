# Diode Operating Point Calculation using Newton-Raphson in C

This project calculates the **operating point** (titik kerja) of a nonlinear diode circuit using the **Newton-Raphson method**. The diode equation is nonlinear due to the exponential relationship between current and voltage, and this tool solves it iteratively with user-defined parameters.

## Circuit Diagram

![Circuit](img/circuit.png)

We are testing using basic nonlinier diode circuit with custom variable that you input to the program.

## How to Compile

Compile using GCC with math library:

```bash
gcc dioda_operating_point.c -o dioda -lm
````

## How to Run

After compiling:

```bash
./dioda
```

The program will prompt for these inputs:

* `Vin` – Input voltage (in volts)
* `R` – Resistance (in ohms)
* `Is` – Saturation current (in amperes)
* `n` – Ideality factor (dimensionless, usually between 1 and 2)
* `Vt` – Thermal voltage (in volts, typically \~0.02585 V at room temperature)

## Input Format Notes

| Parameter | Description            | Example        |
| --------- | ---------------------- | -------------- |
| Vin       | Input voltage (V)      | `5.0`          |
| R         | Resistance (Ω)         | `1000`         |
| Is        | Saturation current (A) | `1e-12`        |
| n         | Ideality factor        | `1.0` or `1.5` |
| Vt        | Thermal voltage (V)    | `0.02585`      |

**Note:** Is must be entered in scientific notation, e.g., `1e-12`.

## Example Test Cases

### Test Case 1 – Common Silicon Diode

| Parameter | Value   |
| --------- | ------- |
| Vin       | 5.0     |
| R         | 1000    |
| Is        | 1e-12   |
| n         | 1.0     |
| Vt        | 0.02585 |


### Test Case 2 – Lower Supply Voltage

| Parameter | Value   |
| --------- | ------- |
| Vin       | 3.3     |
| R         | 1000    |
| Is        | 1e-12   |
| n         | 1.0     |
| Vt        | 0.02585 |


## Output

The program prints the operating point and iteration log to the terminal and also saves the final result to:

```
dioda_output.txt
```

## Project Report

See the full project report and analysis in the following PDF (only available in Bahasa Indonesia):

[ProyekUAS\_2306161883\_Abednego.pdf](./ProyekUAS_2306161883_Abednego.pdf)

## License

MIT License
