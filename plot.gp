data = "bench_sort.txt"

set title "merge sort os"
set term png enhanced font "Times_New_Roman,12"
set output 'merge sort os.png'
set xlabel 'epoch'
set ylabel 'time(nsec)'


plot data using 1 with lines title "recursive", \
 data using 2 with lines title "head-tail", \
 data using 3 with lines title "interval", \

# plot data using 1 with lines title "v1", \
#  data using 2 with lines title "v2", \
