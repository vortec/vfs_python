#include "python2.7/Python.h"
#include "python_importer.h"

int python_connect(vfs_handle_struct *handle,
				   const char *service,
				   const char *user);
void python_disconnect(vfs_handle_struct *handle);
int python_mkdir(vfs_handle_struct *handle,
				 const char *path,
				 mode_t mode);
