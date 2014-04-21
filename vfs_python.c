#include "include/includes.h"
#include "../lib/util/tevent_unix.h"
#include "../lib/util/tevent_ntstatus.h"

#include "vfs_python.h"
#include "commands.h"


static struct vfs_fn_pointers vfs_python_fns = {
		.connect_fn = python_connect,
		.disconnect_fn = python_disconnect,
		.mkdir_fn = python_mkdir
};

#define vfs_python_init samba_init_module

NTSTATUS vfs_python_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION,
							"python",
							&vfs_python_fns);
}
