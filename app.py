import serial
import requests
import time

# Function to establish a serial connection
def connect_to_serial(port, baud_rate):
    try:
        ser = serial.Serial(port, baud_rate, timeout=1)
        print(f"Connected to {port}")
        return ser
    except serial.SerialException as e:
        print(f"Error connecting to {port}: {e}")
        time.sleep(10)  # Wait for a while before trying to reconnect
        return None

# Parse incoming serial data
def parse_data(data):
    try:
        parts = data.split(',')
        return {p.split(':')[0].strip(): p.split(':')[1].strip() for p in parts}
    except ValueError as e:
        print(f"Data parsing error: {e}")
        return {}

# The main loop
def main_loop(ser):
    while True:
        try:
            if ser.in_waiting:
                line = ser.readline().decode('utf-8').strip()
                if line:  # Make sure there's data to parse
                    data = parse_data(line)
                    if data:  # Ensure data is not empty
                        response = requests.post('http://localhost:5000/upload', data={'data': line})
                        print(response.text)
        except serial.SerialException as e:
            print(f"Serial error: {e}")
            ser.close()
            time.sleep(10)
            ser = connect_to_serial('COM7', 9600)
            if ser is None:
                break
        except requests.exceptions.RequestException as e:
            print(f"Network error: {e}")
            time.sleep(5)
        except Exception as e:
            print(f"An unexpected error occurred: {e}")
            time.sleep(5)

# Initial attempt to connect to the serial port
ser = connect_to_serial('COM7', 9600)

# Start the main loop if the serial connection was successful
if ser is not None:
    main_loop(ser)
else:
    print("Failed to connect to the serial port. Exiting.")


# In[7]:





# In[ ]:




