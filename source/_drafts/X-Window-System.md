---
title: X Window System
tags:
---

* https://edoras.sdsu.edu/doc/debian/ch-X.html



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
