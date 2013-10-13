# -*- coding: utf-8 -*- 
import xdrlib, sys
import xlrd
import getopt
import glob
import re

language = {}

def init_language():
    language['EN']="english"
    language["Polish"]="polish"
    korean="Korean"
    language[korean]="korean"
    language["French"]="france"
    language["Spanish"]="spanish"
    language["German"]="germany"
    language["Italian"]="italian"
    language["Portuguese"]="portugal"
    language["Japanese"]="japanese"
  
    
def open_excel(file='file.xls'):
    try:
        data=xlrd.open_workbook(file)
        return data
    except Exception,e:
        print str(e)


 
def append_tag(excel_file,output_dir,tag,i,output_file):
    data=open_excel(excel_file)
    table = data.sheets()[0]
    nrows = table.nrows 
    ncols = table.ncols 
    
    for j in range(0,ncols):
        string = str(table.cell(0,j)).encode("utf-8")
        string=string.split("'")[1].split("\\")[0]       
 #       language_file=output_dir+"\\"+language[string]+".php"
        language_file=output_dir+"\\"+language[string]+"\\"+output_file
        print language_file;
        
        string = table.cell(i,j).value.encode("utf-8")
        string = 'define("'+tag+'", "'+string+'");';
        write_file(language_file,string)
    print "append end!\n"

def edit_tag(excel_file,output_dir,tag,output_file):  
    data=open_excel(excel_file)
    table = data.sheets()[0]
    ncols = table.ncols 
    for j in range(0,ncols):
        string = str(table.cell(0,j)).encode("utf-8")
        string=string.split("'")[1].split("\\")[0]       
         #       language_file=output_dir+"\\"+language[string]+".php"
        language_file=output_dir+"\\"+language[string]+"\\"+output_file
        print language_file;
        
        string = table.cell(1,j).value.encode("utf-8")
        string = 'define("'+tag+'", "'+string+'");';
        edit_file(language_file,tag,string)
        print "edit end!\n"

def edit_file(filename,tag,outstring):
    file=open(filename,"r+")
    string=""
    line_list=[]
    for line in file:
        if not line:
            break
        elif line.find(tag)!=-1:
            print "found %r in file %r " %(line,filename)            
            line_list.append(outstring+"\n")
            print string
        else:
            line_list.append(line)
    file.close()
    file=open(filename,"w+")
    for line in line_list:
        file.write(line) 
    file.close()
            
        
    
 
def Usage():
    print 'usage'

def query_file_list(dir,tag):   
    file_list = glob.glob(dir+"\\*.php")
    for file in file_list:
        query_file(file,tag)

def query_inner_folder(dir,file,tag):
    for lan in language:
        #print dir+"\\"+language[lan]+"\\"+file;
        query_file(dir+"\\"+language[lan]+"\\"+file,tag)
    print "query end!"

def query_file(filename,tag):
    file = open(filename)
    lineno = 0
    for line in file:
        lineno+=1
        if not line:
            break       
        elif line.find(tag)!=-1:
            print "found %r in file %r lineno=%d" %(line,filename,lineno)
    file.close()
    
         
def write_file(filename,str):
    file=open(filename,"r+")
    string=""
    line_list=[]
    end_tag = 0
    for line in file:
        if not line:
            break
        elif line.find("?>")!=-1:
            end_tag = 1
        else:
            line_list.append(line)
    file.close()
    file=open(filename,"w+")
    for line in line_list:
        file.write(line)
    file.write(str+"\n")
    if end_tag:
        file.write("?>")
    

def del_tag(filename,tag):
    file=open(filename,"r+")
    string=""
    line_list=[]
    for line in file:
        if not line:
            break
        elif line.find(tag)!=-1:
            print "found %r in file %r " %(line,filename)
        else:
            line_list.append(line)
    file.close()
    file=open(filename,"w+")
    for line in line_list:
        file.write(line) 
    file.close()

def del_tag_list(dir,tag):
    file_list = glob.glob(dir+"\\*.php")
    for file in file_list:
        del_tag(file,tag)            
    print "del end!\n"
    
def del_inner_folder(dir,file,tag):
    for lan in language:
        #print dir+"\\"+language[lan]+"\\"+file;
        #query_file(dir+"\\"+language[lan]+"\\"+file,tag)
        del_tag(dir+"\\"+language[lan]+"\\"+file,tag)      
    print "del end!\n"    
    
def main(argv):
    init_language()
    dir=""
    excel_file=""
    command=""
    output_file=""
 
    try:
        opts,arg=getopt.getopt(argv[1:],'e:ho:f:',['help=', 'excel=', 'output=','output_file='])   
    except getopt.GetoptError, err:     
        Usage()
        sys.exit(2)
    
    for o,a in opts:
        if o in ('-h','--help'):
            print a
        elif o in ('-o','--output'):
            dir = a
            #read_file_list(dir)
   #         write_file(dir+"\\"+"english.php","cl test")
        elif o in ('-e','--excel'):
            excel_file = a
        elif o in ('-f','--file'):
            output_file = a
    while 1:
        command=raw_input("input command(query,append,del,edit) q to quit\n")
        if command=="query":
            tag=raw_input("Query: Please input the tag:\n")
            #query_file_list(dir,tag)
            query_inner_folder(dir,output_file,tag);
            
        elif command=="append":
            line=raw_input("Append: Please input the line number:\n")
            for i in range(1,int(line)+1):
                tag=raw_input("Append: Please input the tag:\n")
                append_tag(excel_file,dir,tag,i,output_file) 
                      
        elif command=="del":
            tag=raw_input("Del: Please input the tag:\n")
            #del_tag_list(dir,tag) 
            del_inner_folder(dir,output_file,tag);
        elif command=="edit":
            tag=raw_input("Edit: Please input the tag:\n")
            edit_tag(excel_file,dir,tag,output_file)
            
        elif command=="q":
            print command
            break
        else:
            break

if __name__=="__main__":
    main(sys.argv)

