import serial
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# CHANGE COM PORT IF NEEDED
arduino = serial.Serial('COM10', 9600)

# wait for Arduino reset
time.sleep(2)

x_data = []
y_data = []

fig, ax = plt.subplots()

def update(frame):

    try:
        line = arduino.readline().decode('utf-8').strip()

        print("Received:", line)

        distance = float(line)

        x_data.append(len(x_data))
        y_data.append(distance)

        ax.clear()
        ax.plot(x_data, y_data)

        ax.set_xlabel("Time")
        ax.set_ylabel("Distance (cm)")
        ax.set_title("Ultrasonic Sensor")

    except Exception as e:
        print("Error:", e)

ani = FuncAnimation(
    fig,
    update,
    interval=100,
    cache_frame_data=False
)

plt.show()

arduino.close()