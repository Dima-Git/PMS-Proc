sudo insmod calc_proc.ko
echo 124 > /proc/calc_proc_opA
echo "+" > /proc/calc_proc_act
echo 322 > /proc/calc_proc_opB
cat /proc/calc_proc_result
sudo rmmod calc_proc
