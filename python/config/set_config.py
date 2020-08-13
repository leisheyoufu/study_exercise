from __future__ import print_function
import sys
import os

def render_properties_file(path, key, val):
    lines = []
    with open(path, 'r+') as f:
        content = f.read()
    for line in content.split('\n'):
        if line.startswith('#'):
            lines.append(line)
            continue
        arrays = line.strip().split('=')
        if len(arrays) >=2 and arrays[0].strip() == key:
            line = '{key}={val}'.format(key=key, val=val)
        
        lines.append(line)
    
    with open(path, 'w+') as f:
        f.write('\n'.join(lines))

def render_yaml_file(path, key, val):
    import yaml
    with open(path) as f:
        data = yaml.load(f, Loader=yaml.FullLoader)
    temp = key.split('.')
    temp_data = data
    for k in temp[:-1]:
        if not k in temp_data:
            print("Error key %s not in config" % k)
            sys.exit(1)
        temp_data = temp_data[k]
    if not temp[-1] in temp_data:
        print("key %s not in config" % temp[-1])
        sys.exit(1)
    temp_data[temp[-1]] = val
    with open(path, 'w+') as f:
        yaml.dump(data, f)

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Format, set_config.py <file> <key> <value>", file=os.stderr)
        sys.exit(1)
    path = sys.argv[1]
    key = sys.argv[2]
    val = sys.argv[3]
    if path.endswith('.conf') or path.endswith('properties'):
        render_properties_file(path, key, val)
    elif path.endswith('yaml') or path.endswith('yml'):
        render_yaml_file(path, key, val)
