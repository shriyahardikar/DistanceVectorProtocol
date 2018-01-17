Following commands are supported by the program:

- update <server1-ID> <server2-ID> value
Updates the cost of link to the neighbor.

- step
Send routing update to neighbors (triggered/force update)

- packets
Display the number of distance vector packets this server has received since the last invocation of this
information.

- display
Display the current routing table. And the table should be displayed in a sorted order from small ID to
big.

- disable <server-ID>
Disable the link to a given server. Doing this “closes” the connection to a given server with
server-ID.

- crash
Close all connections. This is to simulate server crashes.

Start with command "- server -t <topology-file-name> -i <routing-update-interval>" right after start up of the router to load topology file.