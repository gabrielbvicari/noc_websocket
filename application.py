from os import system
from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import json

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secretkey'
socketio = SocketIO(app)

@app.route('/')
def hello():
    return render_template('index.html')

def messageReceived():
    print('Message received!')

@socketio.on('noc_generated_event')
def nocReceived(json_recv):
    print('Received: ' + str(json_recv))
    socketio.emit('noc_generated_response', json_recv, callback = messageReceived())
    system("./bin/nocsim ./input/testemesh2d.txt " + str(json_recv["topology"]) + " " + str(json_recv["file_output"]) + " " + str(json_recv["num_lines"]) + " " + str(json_recv["num_columns"]))
    json_send = open("./output/output.json")
    out_data = json.load(json_send)
    socketio.emit('noc_generated_result', out_data)
    json_send.close()

if __name__ == '__main__':
    socketio.run(app, debug = True)