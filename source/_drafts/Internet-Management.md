---
title: Internet Management
tags:
---





[Macos](https://superuser.com/questions/267660/can-someone-please-explain-ifconfig-output-in-mac-os-x/267669#267669)

- lo0: loopback (localhost)
- gif0: Software Network Interface
- stf0: 6to4 tunnel interface
- en0: physical wireless
- en1: Thunderbolt 1
- en2: Thunderbolt 2
- en3: Thunderbolt 3
- en4: Thunderbolt 4
- en5: iBridge / Apple T2 Controller
- en6: Bluetooth PAN
- en8: iPhone USB
- en9: VM network interface
- en10: iPad
- bridge0: Thunderbolt Bridge
- `ap1`: Access Point. This is used if you are using your MacBook as a wireless host where you are sharing its connection.
- `awdl0`: Apple Wireless Direct Link. WIFI p2p connection for things like AirDrop, Airplay, etc. Also used for Bluetooth.
- `llw0`: Low-latency WLAN Interface. Used by the Skywalk system.
- `utun0`: Tunneling interface. Used for VPN connections to tunnel traffic or for software like Back To My Mack.
- `utun1`: Same as utun01



Mac OS X中的`en0`并非Ethernet, 而是WIFi(802.11).

> It's worth keeping in mind that OSX is not Linux, it is basically BSD. And in BSD network interfaces are **named after the device driver that manages the interface**, not necessarily based on the type of device. My guess is that **the same driver supports both built-in WiFi interfaces and wired NICs on Apple computers.**
>
> 即这个en0对应的驱动可能同时支持以太网口和wifi, 因此按en0来命名. 而Linux中是严格按设备命名的, 因此en0一定是以太网口.

![ff3d20725425c59a42ed815f2928000f](/Users/lyk/Library/Containers/com.tencent.qq/Data/Library/Application Support/QQ/nt_qq_e651c6b4d69445f01c18cd3dc38dd6b0/nt_data/Pic/2023-07/Ori/ff3d20725425c59a42ed815f2928000f.png)









# Wi-Fi

https://gainanov.pro/eng-blog/sysad/wifi-cracking/





```sh
brew install aircrack-ng
```



```
sudo ln -s /opt/homebrew/Cellar/aircrack-ng/1.7_1/bin/aircrack-ng /usr/local/bin/aircrack-ng
```





1. Generate a link of the next installed by built-in utility -

    

   airport

    

   for using directly on terminal.

   ```
   sudo ln -s /System/Library/PrivateFrameworks/Apple80211.framework/Versions/Current/Resources/airport /usr/local/bin/airport
   ```

2. Install

    

   hashcat

   ```
   brew install hashcat
   ```

3. Install

    

   hashcat-utils

   . Build from sources. Use git and gcc

   ```
   git clone https://github.com/hashcat/hashcat-utils.git
   cd hashcat-utils/src
   gcc -o cap2hccapx cap2hccapx.c
   sudo mv ./cap2hccapx /usr/local/bin/
   ```

4. Install

    

   hcxtools

   ```
   brew install hcxtools
   ```

5. Install

    

   wireshark

   . We will use a console version -

    

   tshark

   ```
   brew install wireshark
   ```

6. Install [JamWifi](https://github.com/0x0XDev/JamWiFi) app. It is a deauthenticating application in which unwanted clients from a Wi-Fi network have to keep off, jamming and especially their connection will be departed like dust in a second. Download and unzip by [this](http://macheads101.com/pages/downloads/mac/JamWiFi.app.zip) link (or [this](http://macheads101.com/pages/downloads/mac.php)).

7. Test that all tools installed and available. The commands below should success return some help page about itself:

   ```
   airport -h
   aircrack-ng --help
   cap2hccapx -h
   hashcat -h
   hcxhash2cap -h
   tcpdump -h
   tshark -h
   ```

# Bluetooth

https://github.com/toy/blueutil



https://www.hackers-arise.com/networks-basics
