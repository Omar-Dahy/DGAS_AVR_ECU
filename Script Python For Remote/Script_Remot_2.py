import tkinter as tk
import serial
import threading
import json
import time

lighting_toggle_state_1 = False
lighting_toggle_state_2 = False
lighting_toggle_state_3 = False
lighting_toggle_state_4 = False
lighting_toggle_state_5 = False
last_rx = None
last_buttons_high = None
last_buttons_low = None

# 1. Serial connections
ser_arduino = serial.Serial('COM7', 115200, timeout=1)  # Arduino - Read only
ser_stm32 = serial.Serial('COM10', 115200, timeout=1)    # STM32 - Write only

# 2. Send command to STM32
def send_to_stm32(value):
    ser_stm32.write(f"{value}\n".encode('utf-8'))
    print(f"[Python → STM32] Sent: {value}")
    time.sleep(0.1)  # Small delay to ensure STM32 catches command

# 3. Send servo angle correctly (with mode trigger)
def send_servo_angle(angle):
    send_to_stm32(110)      # Activate servo mode
    send_to_stm32(angle)    # Send angle itself
    
def send_motion(value):
    send_to_stm32(120)      #   motion mode

    if value & 2:   
        send_to_stm32(11)
        

    if value & 4:  
        send_to_stm32(7)
        time.sleep(0.1)
        send_to_stm32(130)
        send_to_stm32(8)
        
    else :
         send_to_stm32(1)
         send_to_stm32(130)
         send_to_stm32(7)
         
         


def send_lighting(value):
    global lighting_toggle_state_1, lighting_toggle_state_2, lighting_toggle_state_3, lighting_toggle_state_4, lighting_toggle_state_5 

    if value & 8:
        send_to_stm32(130)
        
        if lighting_toggle_state_1:
            send_to_stm32(6)
        else:
            send_to_stm32(5)
        
        lighting_toggle_state_1 = not lighting_toggle_state_1
        
        
    if value & 1:
        send_to_stm32(130)
        
        if lighting_toggle_state_2:
            send_to_stm32(13)
        else:
            send_to_stm32(14)
        
        lighting_toggle_state_2 = not lighting_toggle_state_2
        
        
    if value & 2:
        send_to_stm32(130)
        
        if lighting_toggle_state_3:
            send_to_stm32(9)
        else:
            send_to_stm32(10)
            send_to_stm32(130)
            send_to_stm32(12)
        
        lighting_toggle_state_3 = not lighting_toggle_state_3
        
        
    if value & 4:
        send_to_stm32(130)
        
        if lighting_toggle_state_4:
            send_to_stm32(11)
        else:
            send_to_stm32(12)
            send_to_stm32(130)
            send_to_stm32(10)
        
        lighting_toggle_state_4 = not lighting_toggle_state_4
        
        
    if value & 16:
        send_to_stm32(130)
        
        if lighting_toggle_state_5:
            send_to_stm32(15)
        else:
            send_to_stm32(16)
        
        lighting_toggle_state_5 = not lighting_toggle_state_5
        
# 4. Read from Arduino continuously in background


def listen_from_arduino():
    global last_rx, last_buttons_high, last_buttons_low

    while True:
        try:
            line = ser_arduino.readline().decode('utf-8').strip()
            if line:
                print(f"[Arduino → Python] Raw: {line}")
                try:
                    packet = json.loads(line)

                    
                    if 'rx' in packet and packet['rx'] != last_rx:
                        send_servo_angle(packet['rx'])
                        #print(f"[Send] New RX Angle: {packet['rx']}")
                        last_rx = packet['rx']

                    
                    if 'buttons_high' in packet and packet['buttons_high'] != last_buttons_high:
                        send_motion(packet['buttons_high'])
                        #print(f"[Send] New Buttons High: {packet['buttons_high']}")
                        last_buttons_high = packet['buttons_high']
                        
                    if 'buttons_low' in packet and packet['buttons_low'] != last_buttons_low:
                        send_lighting(packet['buttons_low'])
                        #print(f"[Send] New Buttons low: {packet['buttons_low']}")
                        last_buttons_low = packet['buttons_low']

                except json.JSONDecodeError:
                    print(f"[Error] Invalid JSON: {line}")
        except Exception as e:
            print(f"[Exception] {e}")



# 5. Background thread for listening
thread = threading.Thread(target=listen_from_arduino, daemon=True)
thread.start()

# 6. GUI
root = tk.Tk()
root.title("STM32 Angle Sender")

tk.Label(root, text="Send Manually to STM32:").pack()

btn_minus30 = tk.Button(root, text="-15", width=10, height=2, command=lambda: send_servo_angle(-15))
btn_0 = tk.Button(root, text="0", width=10, height=2, command=lambda: send_servo_angle(0))
btn_30 = tk.Button(root, text="15", width=10, height=2, command=lambda: send_servo_angle(15))

btn_minus30.pack(pady=2)
btn_0.pack(pady=2)
btn_30.pack(pady=2)

# 7. Exit safely
def on_closing():
    try:
        ser_arduino.close()
        ser_stm32.close()
    except:
        pass
    root.destroy()

root.protocol("WM_DELETE_WINDOW", on_closing)
root.mainloop()