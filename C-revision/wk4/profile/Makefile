.PHONY: all clean report report-tree

clean:
	rm -rf output.svg perf.* stackdata.* main.out

all: stackdata.folded
	./FlameGraph/flamegraph.pl ./stackdata.folded > output.svg

output.svg: stackdata.folded
	./FlameGraph/flamegraph.pl ./stackdata.folded > output.svg

stackdata.folded: stackdata.perf
	./FlameGraph/stackcollapse-perf.pl stackdata.perf > stackdata.folded

stackdata.perf: perf.data
	sudo perf script > stackdata.perf

report-tree: perf.data
	sudo perf report -n --stdio

report: perf.data
	sudo perf report

perf.data: main.out
	sudo perf record -F 100 -g ./main.out

main.out: main.c
	gcc -ansi -Wall -pedantic -o main.out main.c