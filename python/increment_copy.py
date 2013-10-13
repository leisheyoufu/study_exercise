# -*- coding: utf-8 -*-
"""
Created on Mon Sep 30 09:08:47 2013

@author: ChengLong
"""

import os 
import os.path 
import shutil 
import time,  datetime
import glob

"""
 statinfo1 = os.stat("includes/modules/pages/info_check/header_php.php")
    statinfo2 = os.stat("includes/modules/pages/checkout_complete_payment/header_php.php")    
    x = time.localtime(statinfo1.st_mtime)
    x = time.strftime('%Y-%m-%d %H:%M:%S',x)
    print x
    print time.localtime(statinfo2.st_mtime)
   # shutil.copytree("includes","includes_backup")
"""


class FilePath(object):
    def __init__(self,parent,filename):
        self.parent = parent
        self.filename = filename   

def init_mfile_path(root,src_dir,modify_tm):
    os.chdir(root)
    mpath_list=[]
    
    modify_stamp = time.mktime(time.strptime(modify_tm,'%Y-%m-%d %H:%M:%S'))
    for parent,dirnames,filenames in os.walk(src_dir):
        for filename in filenames:
            file_info = os.stat(os.path.join(parent,filename))
            if(file_info.st_mtime > modify_stamp):            
                path = FilePath(parent,filename)
                mpath_list.append(path)
    
    return mpath_list
    
   
    

def cp_mfile(mpath_list,todir):
    if( os.path.exists(todir) == False):
        os.makedirs(todir)
        
    for p in mpath_list:
        to_parent = os.path.join(todir,p.parent)
        
        if(os.path.exists(to_parent) == False):
              os.makedirs(to_parent)
        src_full_name = os.path.join(p.parent,p.filename)
        to_full_name = os.path.join(todir,src_full_name)
        print "copy file %s to %s" %(src_full_name,to_full_name)
        shutil.copyfile(src_full_name,to_full_name)
        
              


def query_file_list(dir):   
    file_list = glob.glob(dir)
   # os.makedirs("backup/"+dir)
    for file in file_list:
        #shutil.copytree(file,"backup/"+file)
        print file


def main(argv):
    mpath_list =  init_mfile_path("D:/WorkSpace/git-vela","includes","2013-09-30 00:00:00")   
    cp_mfile(mpath_list,"d:/backup")
if __name__=="__main__":
    main(sys.argv)
