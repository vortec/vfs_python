def debug(text):
    with open('/home/vortec/workspace/vfs_python/log', 'a') as fo:
        fo.write('PYTHON: {}\n'.format(text))

def connect(service='default', user='default'):
    debug('{} has connected to {}.'.format(user, service))
    return True