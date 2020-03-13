### Smart Dustbin
Realtime Monitoring of Dustbin waste using realtime database of Firebase

### Motivation
To Create awareness of cleanliness and Punctuality of cleaning of dustbin on a regular basis it is quite necessary to have a system that is
continously monitoring the status of these dustbins and sending alert to concerned authorities.

### How it is done
An IOT solution has been developed for this purpose.We have used an NodeMcu coded using Arduino Ide.Ultrasonic Sensor, Weighing sensor have
been used.The NodeMcu is continously sending data collected by the other sensors to a firebase realtime database. From Firebase it is going 
to an Android Application. Whenever the dustbin exceeds its threshold value an alert is generated and is represented in the Application.
