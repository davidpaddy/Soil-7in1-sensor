from flask import Flask, request, render_template

app = Flask(__name__)

# Global variable to store data
received_data = []

@app.route('/upload', methods=['POST'])
def upload():
    data = request.form
    # Assuming 'data' contains a string like "Electrical Conductivity:65535"
    if 'Electrical Conductivity' in data['data']:
        received_data.clear()  # Clear the existing data
    # Assume all data is valid to be appended
    received_data.append(data)
    print(data)  # For debugging in the console
    return "Data received"

@app.route('/')
def index():
    # Add a flag to indicate to the template whether to display data or not
    clear_data = False
    if received_data and 'Electrical Conductivity' in received_data[-1]['data']:
        clear_data = True
    return render_template('index.html', data=received_data, clear_data=clear_data)

if __name__ == '__main__':
    app.run(debug=True, port=5000)
