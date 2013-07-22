kiss-toy-car
=============


The guts of this is a finite state machine (FSM) that I wrote to control a behavior based robot car, written in the KISS-C programming language (which is basically GNU C plus some specialized libraries). Robot behaviors correspond to machine states and input from sensor and buttons correspond to events.

The FSM is represented with an if/else tree, which could end up being unmaintainable if it had to handle more than a handful of states and events. I chose this approach because it would be easier to explain the robot’s logic to the middle school students involved in the project and quicker to write, given the tight deadline. 
