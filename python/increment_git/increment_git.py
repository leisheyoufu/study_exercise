# -*- coding: utf-8 -*-
"""
Created on Mon Sep 30 13:28:12 2013

@author: ChengLong
"""

import os 
import os.path 
import shutil
import sys
import subprocess
import time

mouth = {}
mouth['Jan'] = 1
mouth['Feb'] = 2
mouth['Mar'] = 3
mouth['Apr'] = 4
mouth['May'] = 5
mouth['Jun'] = 6
mouth['Jul'] = 7
mouth['Aug'] = 8
mouth['Sep'] = 9
mouth['Oct'] = 10
mouth['Nov'] = 11
mouth['Dec'] = 12


class GitLog(object):
    def __init__(self,commit='',author='',date=''):
        self.commit = commit
        self.author = author
        self.date = date

def get_author_name(author_line):
    author_seg = author_line.split()
    author_name =''
    count = author_seg.__len__()
    i=1
    while(i<count-1):
        author_name+=author_seg[i]
        i+=1
    return author_name


def git_command(cmd,para=''):
    popen = subprocess.Popen(cmd+' '+para,stdout=subprocess.PIPE)
    return popen.stdout.read().split('\n')

def git_log_command():
    result = git_command("git log")
    count = result.__len__()
    i = 0
    log_list = []
    while i < count:
        if result[i].startswith("commit") and ( result[i+1].startswith("Author") or result[i+1].startswith("Merge")):
            if(result[i+1].startswith("Merge")):
                hash = result[i].split()[1]
                date_seg = result[i+3].split()
                author = get_author_name(result[i+2])
                s = str(date_seg[5])+'-'+str(mouth[date_seg[2]])+'-'+date_seg[3]+' '+date_seg[4];
                log_item = GitLog(hash,author,s)
                log_list.append(log_item)
                i+=4
            else:
                hash = result[i].split()[1]
                date_seg = result[i+2].split()
                author = get_author_name(result[i+1])
                s = str(date_seg[5])+'-'+str(mouth[date_seg[2]])+'-'+date_seg[3]+' '+date_seg[4];
                log_item = GitLog(hash,author,s)
                log_list.append(log_item)
                i+=3
        else:
            i+=1
    return log_list

def get_diff_hash_from_loglist(log_list,start_date,end_date):
    hash_code = ['','']
    select1 =GitLog()
    select2 =GitLog()
    start_diff = 9999999
    end_diff = 9999999
    for log in log_list:
       # user input the time scope which is bigger than log time scope
        if( datetime_timestamp(log.date) - datetime_timestamp(start_date) <0 and
            datetime_timestamp(start_date) - datetime_timestamp(log.date)  < start_diff ):
            hash_code[0] = log.commit
            start_diff = datetime_timestamp(start_date) - datetime_timestamp(log.date)

        if(  datetime_timestamp(end_date) - datetime_timestamp(log.date) > 0 and
             datetime_timestamp(end_date) - datetime_timestamp(log.date) < end_diff):
            hash_code[1] = log.commit
            end_diff = datetime_timestamp(end_date) - datetime_timestamp(log.date)

    return hash_code

def datetime_timestamp(dt):
    time.strptime(dt, '%Y-%m-%d %H:%M:%S')
    s = time.mktime(time.strptime(dt, '%Y-%m-%d %H:%M:%S'))
    return int(s)

# copy the file as the same as the path tree
def cp_files(file_list,todir):
    if( os.path.exists(todir) == False):
        os.makedirs(todir)
    for p in file_list:
        if(p !=''):
            to_parent = os.path.join(todir,os.path.split(p)[0])
            if(os.path.exists(to_parent) == False):
                print to_parent
                os.makedirs(to_parent)
            src_full_name = os.path.join(os.path.split(p)[0],os.path.split(p)[1])
            to_full_name = os.path.join(todir,src_full_name)
            print "copy file %s to %s" %(src_full_name,to_full_name)
            shutil.copyfile(src_full_name,to_full_name)

def main(argv):
    if argv.__len__() < 4:
        print "please input the diff hash \n"

    basepath = 'd:/WorkSpace/'
    topath = 'd:/backup'
    os.chdir(basepath)
    start_date = argv[1] + ' '+ argv[2]
    end_date = argv[3] + ' ' + argv [4]


    #cmd = 'git diff --name-only '
    #para = argv[1]+ ' '+ argv[2]
    log_list = git_log_command()
    hash_code = get_diff_hash_from_loglist(log_list,start_date,end_date)
    # hash code is like 55d0f033338af58c5f35a4b742658b9a128aad5e  0f2ff8e11742c25046c3097af4936571f4255e6e
    file_list = git_command("git diff --name-only ",hash_code[0]+' '+ hash_code[1])
    cp_files(file_list,topath)

if __name__=="__main__":
      main(sys.argv)


