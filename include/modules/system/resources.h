#pragma once
#include <string>

namespace sys_resources {
    struct ResourceInfo {
        long disk_total;
        long disk_used;
        long disk_free;
        int disk_percent_used;
        long inode_total;
        long inode_used;
        int inode_percent_used;
        long io_read_bytes;
        long io_write_bytes;
        long io_read_ops;
        long io_write_ops;
    };
    
    ResourceInfo getResourceInfo();
    long getDiskTotal();
    long getDiskUsed();
    long getDiskFree();
    int getDiskPercentage();
    long getIOReadBytes();
    long getIOWriteBytes();
    long getIOReadOps();
    long getIOWriteOps();
}
