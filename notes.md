#### NOTES

Been able to improvisingly call the API so that it kinda works. `nmcli` was of the problem on getting NULL on `getDnsServers()` on `init()`. The `PCPP_LOG_DEBUG` has not been used, instead relied on just just print out to stdout. Don't know how to see results on that, where `PCPP_LOG_ERROR` seems to be loud about messages. [see where the warnings go to, maybe a log file?]

A string is translated into `IPv4Address`, into some kind of int buffer in memory. Should trace the c'structor futher understanding. 

### TODOs 

* add operator= to the constructor of IpAddress.
