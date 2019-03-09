# Database Engine

## How it works

The task of the Database Engine server is to read the contents of the file requested by the client to the server. The 
server along with the files exist in a single directory. The communication between the server and client is through 
**Sockets**. Fork() is used to handle new connections and servicing requests simultaneously. The child process handles 
the servicing of the request by looking up the database, while the parent process deals with new connections via the 
accept() blocking call.

The working of the communication between clients and the server is the same as that mentioned in **Echo Engine**.

## How to run

To start the server, run the following commands. Note that the server is in another directory along with the files.

*cd server_dir*

*gcc server.c -o server*

*./server*

To start the clients, navigate back to previous directory using *cd ..* and run the following.

*gcc client[Name].c -o client[Name]*

*./client[Name]*

Input should be given as follows.

*GET [File_Name].txt*

For example, there is marks.txt file in the server_dir directory. On giving "GET marks.txt" the contents of the file
have to be written from the server to the client through the socket. The output was as follows.

> Hello I am Alan

> How are you?

## Performance Data

The performance data was unable to be made sense of or even predicted. On running the clients on multiple windows,
it was not possible to raise requests parallely. And the time computed by the processor timer was not reasonable and hence
could not come to any conclusion with the data points.

Here is the data collected from the timer used in the client to calculate the time of response from server. The data looks
scattered. The data is collected for different cases - on running single client, two clients and five clients.The data is in 
the order of **microseconds**.

Sl.No | 1 client | 2 clients | 5 clients
------|----------|-----------|----------
1 | 107 | 81 | 97
2 | 57 | 87 | 105
3 | 140 | 50 | 149
4 | 47 | 66 | 158
5 | 94 | 132 | 73
