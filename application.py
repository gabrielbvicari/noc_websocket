from flask import Flask, render_template
from flask_socketio import SocketIO, emit

app = Flask(__name__)

app.config['SECRET_KEY'] = 'secretkey'
socketio = SocketIO(app)

@app.route('/')
def hello():
    return render_template('index.html')

def messageReceived():
    print('Message received!')

@socketio.on('noc_generated_event')
def handle_my_custom_event(json):
    print('Received: ' + str(json))
    socketio.emit('noc_generated_response', json, callback = messageReceived())
    

if __name__ == '__main__':
    socketio.run(app, debug = True)