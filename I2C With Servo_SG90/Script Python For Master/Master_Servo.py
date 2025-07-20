import tkinter as tk
import serial
import threading

#  1. Serial connections
ser_arduino = serial.Serial('COM7', 115200, timeout=1)      # Arduino - Read only
ser_stm32 = serial.Serial('COM10', 115200, timeout=1)     # STM32 - Write only

# 2. Send angle to STM32
def send_to_stm32(value):
    message = f"{value}\n"
    ser_stm32.write(message.encode('utf-8'))
    print(f"[Python → STM32] Sent: {message.strip()}")

#  3. Read from Arduino continuously in background
def listen_from_arduino():
    while True:
        try:
            line = ser_arduino.readline().decode('utf-8').strip()
            if line:
                print(f"[Arduino → Python] Received: {line}")
                if line.isdigit():
                    send_to_stm32(line)
        except Exception as e:
            print(f"Error: {e}")

#  4. Start reading thread
thread = threading.Thread(target=listen_from_arduino, daemon=True)
thread.start()

#  5. Optional: Manual GUI for testing
root = tk.Tk()
root.title("STM32 Angle Sender")

tk.Label(root, text="Send Manually to STM32:").pack()

btn_0 = tk.Button(root, text="0", width=10, height=2, command=lambda: send_to_stm32(0))
btn_90 = tk.Button(root, text="90", width=10, height=2, command=lambda: send_to_stm32(90))
btn_180 = tk.Button(root, text="180", width=10, height=2, command=lambda: send_to_stm32(180))

btn_0.pack(pady=2)
btn_90.pack(pady=2)
btn_180.pack(pady=2)

#  6. Handle closing safely
def on_closing():
    try:
        ser_arduino.close()
        ser_stm32.close()
    except:
        pass
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()
