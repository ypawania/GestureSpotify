# GestureSpotify
Control your music using gestures.

4 types of gestures can be used to resume, pause, skip and rewind music. 

A custom algoritm detects gestures converts distance-time measurements from the ultrasonic sensor to read them as gestures. The gestures can be at abritrary distance from the sensor, and an arbtirary speed, as long as they're the right action. 

The mode can be changed so gestures can be used for different actions, such as changing the music volume instead.

The system consists of an ultrasonic sensor connected to an Arduino, which is where the custom gesture dection algorithm runs locally. This communicates with a laptop via serial using a custom communication protocol, where spotify api calls are made.
