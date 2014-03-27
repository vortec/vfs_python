def debug(text):
    with open('/home/vortec/workspace/vfs_python/log', 'a') as fo:
        fo.write('{}\n'.format(text))

def connect(service='aaaaa', user='xxxx'):
    debug('{} has connected.'.format(user))
