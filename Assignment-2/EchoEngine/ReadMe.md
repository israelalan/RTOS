# Echo Engine 

## How it works

The task of the Echo Engine server is to convert upper case letters to lower case letters and vice versa which are sent from the client to the server. The communication between the server and client is through **Sockets**.  

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

The performance data was unable to be made sense of or even predicted. The results shown by the processor timer which runs in the client program were unreasonable. This could be because of the numerous background processes run inside the kernel. 

Here is the timing data received from the clients. The time was calculated from when the request was sent from the client to the time until the response from server came back. The time was computed for different cases - on running single client, two clients and five clients. The data in the table is is the order of **microseconds**. 

Sl.No | 1 client | 2 clients | 5 clients
------|----------|-----------|----------
1 | 65 | 165 | 62
2 | 29 | 85 | 67
3 | 25 | 64 | 59
4 | 78 | 50 | 71
5 | 34 | 47 | 33
