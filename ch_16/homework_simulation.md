## Homework (Simulation)

This program allows you to see how address translations are performed
in a system with segmentation. See the README for details.

Questions

>1. First let’s use a tiny address space to translate some addresses. Here’s
a simple set of parameters with a few different random seeds; can
you translate the addresses?
• segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512
-L 20 -s 0
• segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512
-L 20 -s 1
• segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512
-L 20 -s 2

1.  
```
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x0000006c (decimal:  108) --> PA or segmentation violation?
  VA  1: 0x00000061 (decimal:   97) --> PA or segmentation violation?
  VA  2: 0x00000035 (decimal:   53) --> PA or segmentation violation?
  VA  3: 0x00000021 (decimal:   33) --> PA or segmentation violation?
  VA  4: 0x00000041 (decimal:   65) --> PA or segmentation violation?
  ```
  SEG0 valid VA: 0-19    
  SEG1 (492-512) valid VA: 108-127  
  0: SEG1, valid, address 0x1ec  
  1: SEG1, segmentation violation  
  2: SEG0, segmentation violation  
  3: SEG0, segmentation violation  
  4: SEG1, segmentation violation    

  2.
  ```
  ARG seed 1
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 20

Virtual Address Trace
  VA  0: 0x00000011 (decimal:   17) --> PA or segmentation violation?
  VA  1: 0x0000006c (decimal:  108) --> PA or segmentation violation?
  VA  2: 0x00000061 (decimal:   97) --> PA or segmentation violation?
  VA  3: 0x00000020 (decimal:   32) --> PA or segmentation violation?
  VA  4: 0x0000003f (decimal:   63) --> PA or segmentation violation?
  ```
  SEG0 valid VA: 0-19  
  SEG1 valid VA: 108-127  
  0: SEG0, valid, address 0x00000011  
  1: SEG1, valid, address 0x1ec  
  2: SEG1, segmentation violation  
  3: SEG0, segmentation violation  
  4: SEG0, segmentation violation

>2. Now, let’s see if we understand this tiny address space we’ve 
constructed (using the parameters from the question above). What is
the highest legal virtual address in segment 0? What about the 
lowest legal virtual address in segment 1? What are the lowest and
highest illegal addresses in this entire address space? Finally, how
would you run segmentation.py with the -A flag to test if you
are right?

Highest legal virtual address in segment 0: 19  
Lowest legal virtual address in segment 1: 108  
Lowest and highest illegal address in entire space: 20-107   
`python3 ./segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 1 -A 19,108,20,107 -c`

>3. Let’s say we have a tiny 16-byte address space in a 128-byte physical
memory. What base and bounds would you set up so as to get
the simulator to generate the following translation results for the
specified address stream: valid, valid, violation, ..., violation, valid,
valid? Assume the following parameters:
• segmentation.py -a 16 -p 128
-A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
--b0 ? --l0 ? --b1 ? --l1 ?

`python3 ./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2 -c`

>4. Assume we want to generate a problem where roughly 90% of the
randomly-generated virtual addresses are valid (not segmentation
violations). How should you configure the simulator to do so?
Which parameters are important to getting this outcome?

Make the segments big enough so that most VAs will translate. The limits of
the segments and the virtual space size are important.

>5. Can you run the simulator such that no virtual addresses are valid?
How?

Make the segment limit equal to zero.