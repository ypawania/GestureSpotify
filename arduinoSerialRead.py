##Click on Run without debugging to run. 
##First upload arduino code. close arduino ide. restart vscode.
##run without debugging

import base64
from urllib.parse import urlencode
import webbrowser
import serial
import requests
import config

client_id = config.CLIENT_ID
client_secret = config.CLIENT_SECRET

auth_headers = {
    "client_id": client_id,
    "response_type": "code",
    "redirect_uri": "http://localhost:7777/callback",
    "scope": "user-modify-playback-state"
}
webbrowser.open("https://accounts.spotify.com/authorize?" + urlencode(auth_headers))
code = input("Enter code: ")

##ENTER THE URL LINK. DONT INCLUDE THE PART BEFORE 'code='

encoded_credentials = base64.b64encode(client_id.encode() + b':' + client_secret.encode()).decode("utf-8")

token_headers = {
    "Authorization": "Basic " + encoded_credentials,
    "Content-Type": "application/x-www-form-urlencoded"
}

token_data = {
    "grant_type": "authorization_code",
    "code": code,
    "redirect_uri": "http://localhost:7777/callback"
}

r = requests.post("https://accounts.spotify.com/api/token", data=token_data, headers=token_headers)
token = r.json()["access_token"]
user_headers = {
    "Authorization": "Bearer " + token,
    "Content-Type": "application/json"
}



ser = serial.Serial(port='COM5', baudrate=9600)

while True:
    if ser.in_waiting > 0:
        message = ser.readline().decode().strip()

        if message == '1':
            print("paused")
            pause_response = requests.put('https://api.spotify.com/v1/me/player/pause', headers=user_headers)
            ser.write(b'RESET\n')
        if message == '2':
            print("resumed")
            resume_response = requests.put('https://api.spotify.com/v1/me/player/play', headers=user_headers)
            ser.write(b'RESET\n')
        if message == '3':
            print("next song")
            next_response = requests.put('https://api.spotify.com/v1/me/player/next', headers=user_headers)
            ser.write(b'RESET\n')
        if message == '4':
            print("previous song")
            prev_response = requests.put('https://api.spotify.com/v1/me/player/previous', headers=user_headers) 
            ser.write(b'RESET\n')
