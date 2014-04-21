#include "include/includes.h"
#include "../lib/util/tevent_unix.h"
#include "../lib/util/tevent_ntstatus.h"
#include "python2.7/Python.h"

#include "commands.h"
#include "python_importer.h"

int python_connect(vfs_handle_struct *handle,
						  const char *service,
						  const char *user)
{
	int success = 1;

	PyObject *py_func = get_func(handle, "connect");
	if (py_func != NULL)
	{
		PyObject *py_ret = PyObject_CallFunction(py_func, "ss", service, user);
		success = PyObject_IsTrue(py_ret);
		Py_DECREF(py_ret);
	}

	if (success == 1)
	{
		return SMB_VFS_NEXT_CONNECT(handle, service, user);
	}
	else
	{
		return -1;
	}
}

void python_disconnect(vfs_handle_struct *handle)
{
	SMB_VFS_NEXT_DISCONNECT(handle);
}


int python_mkdir(vfs_handle_struct *handle,
						const char *path,
						mode_t mode)
{
	int success = 1;

	PyObject *py_func = get_func(handle, "mkdir");
	if (py_func != NULL)
	{
		PyObject *py_ret = PyObject_CallFunction(py_func, "s", path);
		success = PyObject_IsTrue(py_ret);
		Py_DECREF(py_ret);
	}

	if (success == 1)
	{
		return SMB_VFS_NEXT_MKDIR(handle, path, mode);
	}
	else
	{
		return -1;
	}
}
