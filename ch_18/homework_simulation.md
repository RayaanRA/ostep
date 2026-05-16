## Homework (Simulation)

In this homework, you will use a simple program, which is known as
paging-linear-translate.py, to see if you understand how simple
virtual-to-physical address translation works with linear page tables. See
the README for details.

Questions

>1. Before doing any translations, let’s use the simulator to study how
linear page tables change size given different parameters. Compute
the size of linear page tables as different parameters change. Some
suggested inputs are below; by using the -v flag, you can see how
many page-table entries are filled. First, to understand how linear
page table size changes as the address space grows, run with these
flags:  
• -P 1k -a 1m -p 512m -v -n 0  
• -P 1k -a 2m -p 512m -v -n 0  
• -P 1k -a 4m -p 512m -v -n 0  

The page table size is equal to the address space divided by the page size.

>2. Then, let’s understand how linear page table size changes as page
size grows. Before running any of these, try to think about the 
expected trends. How should page-table size change as the address
space grows? As the page size grows? Why not use big pages in
general?  
• -P 1k -a 1m -p 512m -v -n 0  
• -P 2k -a 1m -p 512m -v -n 0  
• -P 4k -a 1m -p 512m -v -n 0  

Since page table size = address space / page size, a larger page size results in a smaller page table size. Big pages can be wasteful when not used.

>3. Now let’s do some translations. Start with some small examples,
and change the number of pages that are allocated to the address
space with the -u flag. What happens as you increase the 
percentage of pages that are allocated in each address space?   
• -P 1k -a 16k -p 32k -v -u 0  -> u = 0, none valid  
• -P 1k -a 16k -p 32k -v -u 25  
• -P 1k -a 16k -p 32k -v -u 50  
• -P 1k -a 16k -p 32k -v -u 75  
• -P 1k -a 16k -p 32k -v -u 100 

• `-P 1k -a 16k -p 32k -v -u 50`   :
```
Page tables 1, 2, 5, 8, 11, 13, 14 are not valid.  
16 pages represented by 14 bits, top 4 = VPN  
0x00003385 -> 11 0011 1000 0101, VPN 12 with offset 11 1000 0101 = 0x385 
PT 12 = 0x8000000f, PFN = 0xF, PA + (0xF << 10) | 0x385 = 0x3F85
```

>4. Now let’s try some different random seeds, and some different (and
sometimes quite crazy) address-space parameters, for variety. Which
of these parameter combinations are unrealistic? Why?  
• -P 8k -a 32k -p 1m -v -s 2  
• -P 1m -a 256m -p 512m -v -s 3

The second one has a very large page size.  

>5. Use the program to try out some other problems. Can you find the
limits of where the program doesn’t work anymore? For example,
what happens if the address-space size is bigger than physical memory?

The program does not allow an address space larger than physical memory, but could happen through demand paging.  
