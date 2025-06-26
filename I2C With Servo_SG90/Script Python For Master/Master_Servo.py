import tkinter as tk
import serial

# Initialize serial port
ser = serial.Serial('COM10', 115200, timeout=1)

def send_value(value):
    # Send value as bytes with newline for safety
    ser.write(f"{value}\n".encode('utf-8'))

# Create main window
root = tk.Tk()
root.title("STM32 Angle Sender")

# Create buttons
btn_0 = tk.Button(root, text="0", width=10, height=2, command=lambda: send_value(0))
btn_90 = tk.Button(root, text="90", width=10, height=2, command=lambda: send_value(90))
btn_180 = tk.Button(root, text="180", width=10, height=2, command=lambda: send_value(180))

# Pack buttons
btn_0.pack(pady=5)
btn_90.pack(pady=5)
btn_180.pack(pady=5)

# Run the interface
root.mainloop()

# Close serial port after closing the window
ser.close()