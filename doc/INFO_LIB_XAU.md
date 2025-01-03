---
title: Xau - Sample Authorization Protocol for X
category: Documentation for Developers
layout: default
SPDX-License-Identifier: LGPL-2.1-or-later
---

# A Sample Authorization Protocol for X

The following note describes a very simple mechanism for providing individual
access to an X Window System display.  It uses existing core protocol and
library hooks for specifying authorization data in the connection setup block
to restrict use of the display to only those clients that show that they
know a server-specific key called a "magic cookie".  This mechanism is *not*
being proposed as an addition to the Xlib standard; among other reasons, a
protocol extension is needed to support more flexible mechanisms.  We have
implemented this mechanism already; if you have comments, please send them
to us.

This scheme involves changes to the following parts of the sample release:

    o  xdm
	-  generate random magic cookie and store in protected file
	-  pass name of magic cookie file to server
	-  when user logs in, add magic cookie to user's auth file
	-  when user logs out, generate a new cookie for server

    o  server
	-  a new command line option to specify cookie file
	-  check client authorization data against magic cookie
	-  read in cookie whenever the server resets
	-  do not add local machine to host list if magic cookie given

    o  Xlib
	-  read in authorization data from file
	-  find data for appropriate server
	-  send authorization data if found

    o  xauth [new program to manage user auth file]
	-  add entries to user's auth file
	-  remove entries from user's auth file

This mechanism assumes that the superuser and the transport layer between
the client and the server is secure.


## Description

The sample implementation will use the xdm Display Manager to set up and
control the server's authorization file.  Sites that do not run xdm will
need to build their own mechanisms.

Xdm uses a random key (seeded by the system time and check sum of /dev/kmem)
to generate a unique sequence of characters at 16 bytes long.  This sequence
will be written to a file which is made readable only by the server.  The
server will then be started with a command line option instructing it to use
the contents of the file as the magic cookie for connections that include
authorization data.  This will also disable the server from adding the local
machine's address to the initial host list.  Note that the actual cookie must
not be stored on the command line or in an environment variable, to prevent
it from being publicly obtainable by the "ps" command.

If a client presents an authorization name of "MIT-MAGIC-COOKIE-1" and
authorization data that matches the magic cookie, that client is allowed
access.  If the name or data does not match and the host list is empty,
that client will be denied access.  Otherwise, the existing host-based access
control will be used.  Since any client that is making a connection from a
machine on the host list will be granted access even if their authorization
data is incorrect, sites are strongly urged not to set up any default hosts
using the /etc/X*.hosts files.  Granting access to other machines should be
done by the user's session manager instead.

Assuming the server is configured with an empty host list, the existence of the
cookie is sufficient to ensure there will be no unauthorized access to the
display.  However, xdm will (continue to) work to minimize the chances of
spoofing on servers that do not support this authorization mechanism.  This
will be done by grabbing the server and the keyboard after opening the display.
This action will be surrounded by a timer which will kill the server if the
grabs cannot be done within several seconds.  [This level of security is now
implemented in patches already sent out.]

After the user logs in, xdm will add authorization entries for each of the
server machine's network addresses to the user's authorization file (the format
of which is described below).  This file will usually be named .Xauthority in
the users's home directory; will be owned by the user (as specified by the
pw_uid and pw_gid fields in the user's password entry), and will be accessible
only to the user (no group access).  This file will contain authorization data
for all of the displays opened by the user.

When the session terminates, xdm will generate and store a new magic cookie
for the server.  Then, xdm will shutdown its own connection and send a
SIGHUP to the server process, which should cause the server to reset.  The
server will then read in the new magic cookie.

To support accesses (both read and write) from multiple machines (for use in
environments that use distributed file systems), file locking is done using
hard links.  This is done by creat'ing (sic) a lock file and then linking it
to another name in the same directory.  If the link-target already exists,
the link will fail, indicating failure to obtain the lock.  Linking is used
instead of just creating the file read-only since link will fail even for
the superuser.

## Problems and Solutions

There are a few problems with .Xauthority as described.  If no home directory
exists, or if xdm cannot create a file there (disk full), xdm stores the
cookie in a file in a resource-specified back-up directory, and sets an
environment variable in the user's session (called XAUTHORITY) naming this
file.  There is also the problem that the locking attempts will need to be
timed out, due to a leftover lock.  Xdm, again, creates a file and set an
environment variable.  Finally, the back-up directory might be full.  Xdm,
as a last resort, provides a function key binding that allows a user to log
in without having the authorization data stored, and with host-based access
control disabled.

## Xlib

XOpenDisplay in Xlib was enhanced to allow specification of authorization
information.  As implied above, Xlib looks for the data in the
.Xauthority file of the home directory, or in the file pointed at by the
XAUTHORITY environment variable instead if that is defined.  This required
no programmatic interface change to Xlib.  In addition, a new Xlib routine
is provided to explicitly specify authorization.

	XSetAuthorization(name, namelen, data, datalen)
		int namelen, datalen;
		char *name, *data;

There are three types of input:

	name NULL, data don't care	- use default authorization mechanism.
	name non-NULL, data NULL	- use the named authorization; get
					  data from that mechanism's default.
	name non-NULL, data non-NULL	- use the given authorization and data.

This interface is used by xdm and might also be used by any other
applications that wish to explicitly set the authorization information.

Authorization File

The .Xauthority file is a binary file consisting of a sequence of entries
in the following format:

	2 bytes		Family value (second byte is as in protocol HOST)
	2 bytes		address length (always MSB first)
	A bytes		host address (as in protocol HOST)
	2 bytes		display "number" length (always MSB first)
	S bytes		display "number" string
	2 bytes		name length (always MSB first)
	N bytes		authorization name string
	2 bytes		data length (always MSB first)
	D bytes		authorization data string

The format is binary for easy processing, since authorization information
usually consists of arbitrary data.  Host addresses are used instead of
names to eliminate potentially time-consuming name resolutions in
XOpenDisplay.  Programs, such as xdm, that initialize the user's
authorization file will have to do the same work as the server in finding
addresses for all network interfaces.  If more than one entry matches the
desired address, the entry that is chosen is implementation-dependent.  In
our implementation, it is always the first in the file.

The Family is specified in two bytes to allow out-of-band values
(i.e. values not in the Protocol) to be used.  In particular,
two new values "FamilyLocal" and "FamilyWild" are defined.  FamilyLocal
refers to any connections using a non-network method of connection from the
local machine (Unix domain sockets, shared memory, loopback serial line).
In this case the host address is specified by the data returned from
gethostname() and better be unique in a collection of machines
which share NFS directories.  FamilyWild is currently used only
by xdm to communicate authorization data to the server.  It matches
any family/host address pair.

For FamilyInternet, the host address is the 4 byte internet address, for
FamilyDecnet, the host address is the byte decnet address, for FamilyChaos
the address is also two bytes.

The Display Number is the ascii representation of the display number
portion of the display name.  It is in ascii to allow future expansion
to PseudoRoots or anything else that might happen.

A utility called "xauth" will be provided for editing and viewing the
contents of authorization files.  Note that the user's authorization file is
not the same as the server's magic cookie file.
