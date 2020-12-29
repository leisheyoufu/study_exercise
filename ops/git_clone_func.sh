#/bin/bash
## Refence openstack devstack
set -ex
function git_clone {
    local git_remote=$1
    local git_dest=/opt/leisheyoufu/$2
    local git_ref=$3
    local orig_dir
    orig_dir=$(pwd)
    echo "git clone $git_remote $git_dest"
    # If our branch name is a gerrit style refs/changes/...
    if [[ ! -d $git_dest ]]; then
        git clone $git_remote $git_dest
    fi
    if [[ -z "$git_ref" ]]; then
        echo "git ref is not specified, use master as default"
        git_ref=master
    fi
    cd $git_dest
    git fetch $git_remote $git_ref && git checkout FETCH_HEAD
    # print out the results so we know what change was used in the logs
    cd -
    git show --oneline | head -1
    cd $orig_dir
}