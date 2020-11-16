all: test_multimap cfs_sched

test_multimap: multimap.h test_multimap.cc
	g++ -Wall -Werror -o test_multimap test_multimap.cc -pthread -lgtest

cfs_sched: multimap.h cfs_sched.cc
	g++ -Wall -Werror -o cfs_sched cfs_sched.cc

cpplint:
	/home/cs36cjp/public/cpplint/cpplint cfs_sched.cc

clean:
	rm -rf *o test_multimap cfs_sched
