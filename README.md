Rock Paper Scissors Game
This is a simple rock-paper-scissors game implemented using UDP sockets. The server is written in C and the client is written in Python.

How to Run
Server (C)
Compile the server code (server.c) using a C compiler.
Run the compiled executable on the server machine.
Client (Python)
Make sure Python is installed on your system.
Run the client code (client.py) on your machine.
How to Play
The server waits for the client to send their choice (rock, paper, or scissors) over the network.
The server randomly selects its choice.
The server determines the winner based on the choices and sends the result back to the client.
The client displays the result on the screen.
Features
The game uses UDP sockets for communication.
The server handles multiple clients concurrently.
The client can see both their choice and the server's choice, along with the result.
Requirements
Python 3.x
C compiler
Future Improvements
Add error handling for network issues.
Implement a graphical user interface for the client.
