def debug(text):
    with open('/tmp/samba.log', 'a') as fo:
        fo.write('PYTHON: {}\n'.format(text))

def connect(service='default', user='default'):
    debug('{} has connected to {}.'.format(user, service))
    return True

def mkdir(path):
    debug('Create dir: {}'.format(path))
    return True

def rmdir(path):
    debug('Remove dir: {}'.format(path))
    if path == 'dont_touch_this':
        return False
    return True

def create_file(path):
    debug('Create file: {}'.format(path))
    if path == 'bad_file':
        return False
    return True

def rename(source, target):
    debug('Rename file: {} -> {}'.format(source, target))
    if target == 'bad_file':
        return False
    return True

def unlink(path):
    debug('Unlink: {}'.format(path))
    if path == 'mc_hammer':
        return False
    return True
