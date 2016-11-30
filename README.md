# Keylog
# Server
The testing process should begin by running the server process. It is important to do this first, as when the client begins it will look for it's receiver. We chose to put the server function in a separate folder to represent the separation between the the client and server processes. In a real world scenario, this server would be run a different, remote, machine, started before the malware took root, and awaiting a connection. For the sake of testing, we have specified the path to be on the same machine.
Run the makefile in the server folder
Run the server function
# Keylogger
The client code is all included in the main directory
Begin by running the makefile for the keylogger, compiling the c code
To run on the virtual machine use: 
sudo ./log /dev/input/event2 

# Notes
On restart the client will bootstrap. However because the server is on the same machine, it will not find a server to output to.This is an issue with testing but would work if the server-client machines were separated. 



