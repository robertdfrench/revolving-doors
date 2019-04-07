# Setup OpenIndiana on VirtualBox
*From zero to Illumos in ten minutes*

### Install Virtualbox
[Download Virtualbox](https://www.virtualbox.org/wiki/Downloads) for whatever
platform you are running on your workstation. Click through the installation
wizard. You will likely need to give your permission to trust software written
by Oracle. The irony...

### Download OpenIndiana
[Download OpenIndiana](https://www.openindiana.org/download/). I suggest the
minimal install, as that takes up the least space. The rest of this guide will
walk you through setting up what packages you need to run the lessons.

### Create a VM
Within virtualbox, create a new VM named 'openindiana':

* Type: *Solaris*
* Version: *Oracle Solaris 11 (64-bit)*

#### RAM
The recommended memory is fine, or even less: we will use very little for these
lessons.

#### Storage
A default-sized, dynamically allocated virtual disk will be fine. We won't
hardly use any disk resources.

#### Boot Disc
Under *Settings > Storage*, you should see a storage device under the main SATA
controller named 'Empty': this is your virtual optical drive. We will attach the
OpenIndiana iso that we just downloaded here so that our machine can boot up.

### Install OpenIndiana
Boot the machine and begin the install. I'll leave it up to you to accept the
default suggestions, and create a user with a sensible password. After the
install, we'll configure SSH so you can log in from your workstation instead of
having to do the doors tutorial on VirtualBox's sortof-awkward virtual console.
