#!/bin/bash
## Reference https://stackoverflow.com/questions/2464760/modify-config-file-using-bash-script
function config_set() {
  local file=$1
  local key=$2
  local val=${@:3}

  ensureConfigFileExists "${file}"

  # create key if not exists
  if ! grep -q "^${key}=" ${file}; then
    # insert a newline just in case the file does not end with one
    printf "\n${key}=" >> ${file}
  fi

  chc "$file" "$key" "$val"
}

function ensureConfigFileExists() {
  if [ ! -e "$1" ] ; then
    if [ -e "$1.example" ]; then
      cp "$1.example" "$1";
    else
      touch "$1"
    fi
  fi
}

function chc() { gawk -v OFS== -v FS== -e 'BEGIN { ARGC = 1 } $1 == ARGV[2] { print ARGV[4] ? ARGV[4] : $1, ARGV[3]; next } 1' "$@" <"$1" >"$1.1"; mv "$1"{.1,}; }

# Usage: local myvar="$(config_get file var)"
function config_get() {
    local conf_file=$1
    local key=$2
    val="$(config_read_file ${conf_file} "${key}")";
    if [ "${val}" = "__UNDEFINED__" ]; then
        val="$(config_read_file ${conf_file}.example "${key}")";
    fi
    printf -- "%s" "${val}";
}
function config_read_file() {
    (grep -E "^${2}=" -m 1 "${1}" 2>/dev/null || echo "VAR=__UNDEFINED__") | head -n 1 | cut -d '=' -f 2-;
}
