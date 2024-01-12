---
title: X Window System
tags:
---

* https://edoras.sdsu.edu/doc/debian/ch-X.html

[X Window 配置介绍](http://cn.linux.vbird.org/linux_basic/0590xwindow_1.php)

https://uit.stanford.edu/service/sharedcomputing/moreX

https://edoras.sdsu.edu/doc/debian/ch-X.html

# X11 Forwarding

https://goteleport.com/blog/x11-forwarding/



X11 forwarding allows you to run graphical applications on a remote Unix/Linux server and have them display on your local machine. Here's how to set up and use X11 forwarding:

## On the Client Side (Your Local Machine)

1. **Install an X Server**:

   - **Windows**: Install an X server like Xming or VcXsrv.
   - **macOS**: Install [XQuartz]().
   - **Linux**: X11 is typically installed by default.

2. Run the X Server.

   * macOS: Run XQuartz.  A window will open but you simply need it running in the background to launch a GUI application once connected to the Grid.

3. **Enable X11 Forwarding in SSH**:

   - When using SSH to connect to the remote server, use the 

     ```
     -X
     ```

      (or 

     ```
     -Y
     ```

     ) option to enable X11 forwarding.

     - `-X`: Enables X11 forwarding with some security restrictions.
     - `-Y`: Enables trusted X11 forwarding with fewer security restrictions (use only if `-X` doesn't work).

   * Example ssh command:

     ```sh
     ssh -X username@remotehost
     ```

     



## On the Server Side (Remote Unix/Linux Server)

1. **Install X11 Apps**:

   - Ensure that the applications you want to run are installed on the remote server.

2. **Configure SSH to Allow X11 Forwarding**:

   - Edit the SSH daemon configuration file, typically found at `/etc/ssh/sshd_config`.

   - Make sure the following lines are included and not commented out:

     ```
     bash
     ```

1. - ```
     X11Forwarding yes
     X11DisplayOffset 10
     ```

   - After making changes, restart the SSH service to apply the new configuration.

## Testing X11 Forwarding

1. **Connect to Your Remote Server**:
   - Use the `ssh` command with `-X` or `-Y` from your local machine to connect to the remote server.
2. **Run a Graphical Application**:
   - After connecting, try running a graphical application from the command line. For example, run `xeyes` or `xclock`.
   - If everything is set up correctly, the application's window should appear on your local machine's screen.

## Security Considerations

- **Use `-X` with Caution**: The `-X` option can expose your local X server to some risk. Only use X11 forwarding with trusted remote servers.
- **Prefer `-Y` for Trusted Connections**: If you trust the remote server and need fewer restrictions, `-Y` can provide a smoother experience but be aware of the potential security implications.

By following these steps, you should be able to set up and use X11 forwarding to run remote graphical applications on your local machine. This can be particularly useful for running software that's only available on Unix/Linux servers or for using resources that aren't available on your local machine.

# Display

The DISPLAY variable is used by X11 to identify your display (and keyboard and mouse). Usually it'll be :0 on a desktop PC, referring to the primary monitor, etc.

If you're using SSH with X forwarding (ssh -X otherhost), then it'll be set to something like localhost:10.0. This tells X applications to send their output, and receive their input from the TCP port 127.0.0.1:6010, which SSH will forward back to your original host.

And, yes, back in the day, when "thin client" computing meant an X terminal, it was common to have several hundred displays connected to the same host.



You are unlikely to get the straight VNC method to work in this specific  environment. Using x11vnc or TigerVNC for OpenGL support in this manner  only works (in my experience) when connecting to the :0 display session, which you are unlikely to have access to if the server is a shared  machine on a campus network.

[VirtualGL](https://www.virtualgl.org/) is another option that does work (in my experience) for normal VNC  sessions. The drawback is that it does not provide OpenGL support for  the entire session but rather individual applications that you run. You  must start the application with the "vglrun" command. Although, it seems like this would suit your case fine.

Note, you may need help from your sysadmin to install and configure  VirtualGL. And this all assumes the host machine has OpenGL capability  at all, either a software implementation via Mesa or an actual GPU.





I'm using [x11vnc](http://www.karlrunge.com/x11vnc/) to gain remote access to whatever the monitor is displaying. x11vnc  talks to the local X11 server and copies the framebuffer from the server to the client via vnc. Since the local X11 server renders everything  with hardware acceleration, I get hardware accelerated OpenGL over VNC,  even with all the cool desktop effects. This is how I start x11vnc:

```
x11vnc -rfbauth ~/.vnc/passwd  -display :0 -forever -bg -repeat -nowf -o ~/.vnc/x11vnc.log
```

I think almost any vnc viewer works, but I'd recommend turbovnc or tigervnc. I tried VirtualGL first, and it works fine, but not for the whole desktop, only for individual OpenGL applications.

It is even possible to change resolution on the display/vnc using xrandr. E.g. like this:

```
xrandr -q (to see available modes and outputs)
xrandr --output DVI-I-0 --mode "1024x768" (change mode on DVI output)
```

(It is possible to add new resolutions if the available modes aren't enough, but that's outside the scope here.)

So now I have a fully OpenGL hardware accelerated and resizable VNC session. 

