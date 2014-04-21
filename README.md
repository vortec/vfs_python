vfs_python
==========

An experimental Samba module which lets you control execution of Samba actions in your own Python script.

Installation
------------
You must have the Python headers installed (python-dev) and the Samba sourcecode lying around.

Clone this repository, then compile as follows:

    ./configure --enable-debug --enable-developer --with-samba-source=/path/to/samba/source3
    make

Copy / symlink the resulting `vfs_python.so` to `/usr/local/samba/lib/vfs/python.so` (or wherever your VFS modules are).

In your smb.conf, enable vfs_python per share:

    [myshare]
    path = /tmp
    vfs objects = python
    python:script = /path/to/your/handler.py
    
and make sure that the script path is valid.

The Python code
-------------------
Take a look at [the `handler.py`](https://github.com/vortec/vfs_python/blob/master/handler.py) to see how it looks like and which Samba calls are supported at the moment (hint: not too many).

When a user performs an action, the corresponding Python function will be called. You can either allow or deny that action by returning a boolean.

The Python script will be imported every time a user connects and is valid for the duration of the connection.
