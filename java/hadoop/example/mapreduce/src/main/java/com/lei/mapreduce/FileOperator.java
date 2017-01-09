package com.lei.mapreduce;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.FileUtil;
import org.apache.hadoop.fs.Path;

import java.io.*;


public class FileOperator{
    private FileSystem fs;
    private FileOperator(FileSystem fs) {
        this.fs = fs;
    }
    public void generate(Path path) throws IOException {
        OutputStream out = fs.create(path, true);
        out.write("Hello World\n Hello hdfs\n".getBytes());
        out.close();
    }

    public boolean rename(Path dst, Path src) throws IOException {
        return fs.rename(src, dst);
    }

    public void read(Path path) throws IOException {
        InputStream in = fs.open(path);
        InputStreamReader isr = new InputStreamReader(in);
        BufferedReader reader = new BufferedReader(isr);
        String str;
        while((str = reader.readLine()) != null) {
            System.out.println(str);
        }
    }

    public void list(Path path) throws IOException {
        FileStatus[] status = fs.listStatus(path);
        Path[] listedPaths = FileUtil.stat2Paths(status);
        for (Path p : listedPaths) {
            System.out.println(p);
        }
    }

    public static void main(String[] args) throws Exception {
        Configuration conf=new Configuration();
        FileSystem hdfs=FileSystem.get(conf);
        FileOperator fop = new FileOperator(hdfs);
        Path src = new Path("/tmp/hdfs_test/file01.txt");
        Path dst = new Path("/tmp/hdfs_test/file02.txt");
        fop.generate(src);
        System.out.println("List dirs in /tmp/hdfs_test ******");
        fop.list(new Path("/tmp/hdfs_test"));
        System.out.println("**********************************");
        boolean isRename=fop.rename(dst, src);
        String result=isRename?"success":"failed";
        System.out.println("Rename " + src.getName() +" to " + dst.getName() + " " + result);
        fop.read(dst);
    }
}