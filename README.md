# pinpad

QT frontend for [Nitrokey](https://github.com/nitrokey) enhanced [glorytun](https://github.com/pfect/glorytun) project (changes are in stable branch). Allows you to [start tunnel(s)](https://github.com/pfect/systemd-glorytun) and load key(s) directly from Nitrokey PRO2 device.

With this approach you don't have to store glorytun keys to file system and you can have out of band key exchange with Nitrokey. Systemd scripts provides Tunnel-In-Tunnel (TiT) functionality and it's useful with VPS based glorytun installations where you cannot trust VPS, assuming hostile party has access to file system of any given VPS provider.

![main window](https://github.com/pfect/pinentry/blob/main/doc/mainwindow.png)

## System components

Following picture illustrates dependencies for implementation. 

![system-components](https://github.com/pfect/pinentry/blob/main/doc/glorytun-setup-2.png)

Please note that this is work in progress and documentation is sparse.

## Links

* [systemd scripts for glorytun](https://github.com/pfect/systemd-glorytun)
* [glorytun with nitrokey support](https://github.com/pfect/glorytun)
* [libnitrokey](https://github.com/Nitrokey/libnitrokey)
* [The password hash Argon2, winner of PHC](https://github.com/P-H-C/phc-winner-argon2)
* [pinentry QT user interface](https://github.com/pfect/pinentry)
* [Nitrokey Pro 2 hardware](https://www.nitrokey.com/)

