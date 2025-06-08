import matplotlib.pyplot as plt
import numpy as np
import re

# === CONFIGURATION ===
Is = 1e-12     # A
n = 1.0        # Ideality factor
Vt = 0.02585   # V

# === LOAD OPERATING POINT FROM FILE ===
with open("dioda_output.txt", "r") as file:
    content = file.read()

vd_match = re.search(r"Tegangan Dioda \(Vd\)\s*=\s*([\d.]+)", content)
id_match = re.search(r"Arus Dioda \(Id\)\s*=\s*([\d.eE+-]+)", content)

if not vd_match or not id_match:
    print("Could not find Vd or Id in the output file.")
    exit()

Vd_op = float(vd_match.group(1))
Id_op = float(id_match.group(1))

# === PLOT ===
Vd = np.linspace(0, 0.8, 500)
Id = Is * (np.exp(Vd / (n * Vt)) - 1)

plt.figure(figsize=(8, 5))
plt.plot(Vd, Id * 1000, label='Karakteristik Dioda', color='blue')  # Convert A to mA
plt.plot(Vd_op, Id_op * 1000, 'ro', label='Titik Kerja')            # Operating point

# === ANNOTATION ===
plt.annotate(f"Titik Kerja\nVd = {Vd_op:.3f} V\nId = {Id_op*1000:.3f} mA",
            xy=(Vd_op, Id_op * 1000),
            xytext=(Vd_op + 0.05, Id_op * 1000),
            arrowprops=dict(arrowstyle='->'))

plt.title("Kurva I-V Dioda dan Titik Kerja")
plt.xlabel("Tegangan Dioda Vd (Volt)")
plt.ylabel("Arus Dioda Id (mA)")
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("img/iv_curve.png")
plt.show()
