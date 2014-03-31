bar-software
============

This free software aims at providing a simple way of managing a bar : it will deal with stocks, consumers, accounting and will include a permissions system. This is currently a project in development which for ENSTA Paristech's bar.

sqlite3 is used to manage de database. You can manage it by using SqLite Manager on firefox.
logs are crypted to system_files. Only the program can uncrpyt them (or a similar algorithm you may create ...)
Think to save logs and bar.db on a usb key or a cloud, it might be usefull if your HDD die. The system requires no config : swap the bar.db to get new database. Same with log files.
login on the software are made to stay the same all the time and be the login of the guy/lady at ENSTA. The software will search picture of the customer at resources/photos/login.jpg make sure the login are not entered with fun, name is done for that, and the pictures (of 3w2 per example) are inserted in the right folder (by default they're titled login.jpg on 3w2).
login will be usefull for barmen/barwomen to log in and do some stuff (so don't change your login !)

F1 brings you to searchbar
F2 brings you to searchresults
you can navigate with up and down arrows
Ctrl+Enter select en entry on focus (account or product)
Enter validates the cart
