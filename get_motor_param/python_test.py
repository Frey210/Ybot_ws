import serial
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

ser = serial.Serial('COM3', 9600)  # Sesuaikan port serial

target_pwms = np.arange(0, 501, 10)
speeds = []
min_command_value = None

for target_pwm in target_pwms:
    ser.write(str(target_pwm).encode())
    data = ser.readline().decode().strip().split(',')
    speed = float(data[0])
    speeds.append(speed)
    
    if len(data) > 1:
        min_command_value = int(data[1])

ser.close()

# Buat grafik
plt.plot(target_pwms, speeds, marker='o')
plt.xlabel('PWM Value')
plt.ylabel('Speed (Encoder Counts)')
plt.title('PWM vs Speed')
plt.grid()

# Regresi linier untuk mendapatkan gradien
slope, intercept, _, _, _ = linregress(target_pwms, speeds)
print("Gradien (Slope):", slope)
print("Minimum Command Value for Motor to Start Moving:", min_command_value)

plt.show()
