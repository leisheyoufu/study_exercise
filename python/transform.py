# Used to tranfrom directory and content information
import os
import shutil
import errno
import sys


IGNORE_DIRS = ['.git', 'test', 'locale', '.idea', 'doc']
IGNORE_FILES = ['.gitignore']

SRC_PATTERN = 'old'
DST_PATTERN = 'target'

def delete_if_exists(path, remove=os.unlink):
    try:
        remove(path)
        #os.system('rmdir "%s"' % path)
    except OSError as e:
        if e.errno != errno.ENOENT:
            raise


def rename_dir(path):
    dirs = []
    dirs.append(path)
    while (len(dirs) > 0):
        d = dirs.pop()
        for sub in os.listdir(d):
            if sub in IGNORE_DIRS:
                continue

            p = os.path.join(d, sub)
            if os.path.isdir(p):
                if sub.startswith(SRC_PATTERN):
                    newsub = "%s%s" % (DST_PATTERN, sub[3:])
                    np = os.path.join(d, newsub)
                    delete_if_exists(np, remove=shutil.rmtree)
                    os.rename(p, np)
                    dirs.append(np)
                else:
                    dirs.append(p)


def rename_file(dir, filename):
    f = os.path.join(dir, filename)
    if os.path.isfile(f) and f.endswith('pyc'):
        os.remove(f)

    if os.path.isfile(f) and filename.startswith(SRC_PATTERN):
        newsub = "%s%s" % (DST_PATTERN, filename[3:])
        nf = os.path.join(dir, newsub)
        delete_if_exists(nf)
        os.rename(f, nf)


def rename_content(dir, filename):
    f = os.path.join(dir, filename)
    lines = []
    with open(f, 'r+') as fd:
        for line in fd.readlines():
            line = line.replace(SRC_PATTERN, DST_PATTERN)
            lines.append(line)

    with open(f, 'w+') as fd:
        fd.writelines(lines)


def rename(path, func):
    dirs = []
    dirs.append(path)
    while (len(dirs) > 0):
        d = dirs.pop()

        for sub in os.listdir(d):
            if os.path.isdir(os.path.join(d, sub)):
                if sub in IGNORE_DIRS:
                    continue
                dirs.append(os.path.join(d, sub))

            if os.path.isfile(os.path.join(d, sub)):
                if sub in IGNORE_FILES:
                    continue
                func(d, sub)


if __name__ == '__main__':
    path = sys.argv[1]
    path = os.path.realpath(path)
    if not os.path.exists(path) or not os.path.isdir(path):
        raise

    rename_dir(path)
    rename(path, rename_file)
    rename(path, rename_content)