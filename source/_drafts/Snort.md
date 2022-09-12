---
title: Snort
tags: Network Security
categories: Toolkit
---

Snort is a public-domain, open source IDS with hundreds of thousands of existing deployments [Snort 2012; Koziol 2003]. 

To gain some insight into Snort, let’s take a look at an example of a Snort signature:

```
alert icmp $EXTERNAL_NET any -> $HOME_NET any 
(msg:”ICMP PING NMAP”; dsize: 0; itype: 8;)
```





This signature is matched by any ICMP packet that enters the organization’s network ($HOME_NET) from the outside ($EXTERNAL_NET), is of type 8 (ICMP ping), and has an empty payload (dsize = 0). Since nmap (see Section 1.6) generates ping pack- ets with these specific characteristics, this signature is designed to detect nmap ping sweeps. When a packet matches this signature, Snort generates an alert that includes the message “ICMP PING NMAP”.

Snort的社区非常活跃, 收录的Signature非常快而全.
