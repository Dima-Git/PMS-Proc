sudo insmod calc_proc.ko

echo 124 > /proc/calc_proc_opA
echo "+" > /proc/calc_proc_act
echo 322 > /proc/calc_proc_opB
cat /proc/calc_proc_result

echo 12 > /proc/calc_proc_opA
echo "-" > /proc/calc_proc_act
echo 23 > /proc/calc_proc_opB
cat /proc/calc_proc_result

echo 3 > /proc/calc_proc_opA
echo "*" > /proc/calc_proc_act
echo 1337 > /proc/calc_proc_opB
cat /proc/calc_proc_result

echo 124 > /proc/calc_proc_opA
echo "/" > /proc/calc_proc_act
echo 12 > /proc/calc_proc_opB
cat /proc/calc_proc_result

echo 2 > /proc/calc_proc_opA
echo "/" > /proc/calc_proc_act
echo 0 > /proc/calc_proc_opB
cat /proc/calc_proc_result

echo 2 > /proc/calc_proc_opA
echo "^" > /proc/calc_proc_act
echo 3 > /proc/calc_proc_opB
cat /proc/calc_proc_result

sudo rmmod calc_proc
