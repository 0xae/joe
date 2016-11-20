joe
=====
a small interpreted (for now) programming language
designed for writing networking, kernel and event stuff code.

start
====
    # apt-get install libreadline-dev
    $ cd joe && make
    $ ./joe


status
=====
joe is not even close to a alpha release yet
i just posted the code here to rest my soul.
The only things he can do now, is parse strings, integers and
a compound data structure literal - table.

Here is the ouput of valgrind (this project is really fucked up)

        ayrton@zeus ~/D/R/l/p/joe> valgrind  ./joe
        ==9654== Memcheck, a memory error detector
        ==9654== Copyright (C) 2002-2013, and GNU GPL'd, by Julian Seward et al.
        ==9654== Using Valgrind-3.10.0 and LibVEX; rerun with -h for copyright info
        ==9654== Command: ./joe
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400F38: joe_new_table (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DDE: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654048 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400F2F: joe_new_table (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DDE: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400E9F: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DEF: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654198 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DEF: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
==9654== Conditional jump or move depends on uninitialised value(s)
        ==9654==    at 0x400F08: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DEF: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400FD5: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DEF: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654198 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400DEF: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400E9F: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E00: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654248 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E00: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
==9654== Conditional jump or move depends on uninitialised value(s)
        ==9654==    at 0x400F08: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E00: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400FD5: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E00: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654248 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E00: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400E9F: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E11: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x56542e8 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E11: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
==9654== Conditional jump or move depends on uninitialised value(s)
        ==9654==    at 0x400F08: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E11: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400FD5: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E11: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x56542e8 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E11: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2
        ==9654==    at 0x400E9F: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E22: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==  Address 0x5654398 is 0 bytes after a block of size 8 alloc'd
        ==9654==    at 0x4C28C20: malloc (vg_replace_malloc.c:296)
        ==9654==    by 0x400E96: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E22: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
==9654== Conditional jump or move depends on uninitialised value(s)
        ==9654==    at 0x400F08: joe_new_string (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400FCC: joe_new_error (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x400E22: joe_init (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654==    by 0x4016F9: main (in /home/ayrton/Development/Research/learning/projects/joe/joe)
        ==9654== 
        ==9654== Invalid write of size 2


