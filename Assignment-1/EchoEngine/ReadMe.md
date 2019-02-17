# Echo Engine

## How it works

The task of the Echo Engine server is to convert upper case letters to lower case letters and vice versa which are sent from the client to the server. The communication between the server and client is through **Message Queue**. 

The server has a message queue of it's own. This queue is used to take in the requests of the clients. It acts as the *Request Queue*. Each client has it's own queue with which it receives the responses from the server. Therefore on designing a system with 5 clients and 1 server, there are 6 queues created, one for the server and 5 for the clients. 

## How to run

To start the server, run the following commands.
*gcc server.c -o server*

*./server*

To start the clients, run the following commands. Since there are only two clients here, we shall execute both.

*gcc clientA.c -o clientA*

*gcc clientB.c -o clientB*

*./clientA*

*./clientB*

In order to check the working of the Echo Engine, here are few examples that can be tried.

> aBc -->ouput: AbC

> hello ALAN -->ouput: HELLO alan

## Performance Data

The performance data was unable to be computed or even predicted. The results shown by the processor timer which runs in the client program were unreasonable. This could be because of the numerous background processes run inside the kernel. 
