#!/bin/bash

# Initialize counters for total real, user, and system time for both executables.
total_real_opt=0
total_user_opt=0
total_sys_opt=0

total_real_nonopt=0
total_user_nonopt=0
total_sys_nonopt=0

# Number of runs
runs=100
echo "\nNumber of runs: $runs\n"

for i in $(seq 1 $runs); do 
  # Run the opt_out command and capture the times.
  output_opt=$(/usr/bin/time -f "Real: %e\nUser: %U\nSys: %S" ./opt_out 2>&1)
  real_time_opt=$(echo "$output_opt" | grep "Real" | awk '{print $2}')
  user_time_opt=$(echo "$output_opt" | grep "User" | awk '{print $2}')
  sys_time_opt=$(echo "$output_opt" | grep "Sys" | awk '{print $2}')

  # Run the nonopt_out command and capture the times.
  output_nonopt=$(/usr/bin/time -f "Real: %e\nUser: %U\nSys: %S" ./nonopt_out 2>&1)
  real_time_nonopt=$(echo "$output_nonopt" | grep "Real" | awk '{print $2}')
  user_time_nonopt=$(echo "$output_nonopt" | grep "User" | awk '{print $2}')
  sys_time_nonopt=$(echo "$output_nonopt" | grep "Sys" | awk '{print $2}')

  # Add to totals for opt_out
  total_real_opt=$(echo "$total_real_opt + $real_time_opt" | bc)
  total_user_opt=$(echo "$total_user_opt + $user_time_opt" | bc)
  total_sys_opt=$(echo "$total_sys_opt + $sys_time_opt" | bc)

  # Add to totals for nonopt_out
  total_real_nonopt=$(echo "$total_real_nonopt + $real_time_nonopt" | bc)
  total_user_nonopt=$(echo "$total_user_nonopt + $user_time_nonopt" | bc)
  total_sys_nonopt=$(echo "$total_sys_nonopt + $sys_time_nonopt" | bc)
done

# Calculate averages for opt_out
avg_real_opt=$(echo "scale=3; $total_real_opt / $runs" | bc)
avg_user_opt=$(echo "scale=3; $total_user_opt / $runs" | bc)
avg_sys_opt=$(echo "scale=3; $total_sys_opt / $runs" | bc)

# Calculate averages for nonopt_out
avg_real_nonopt=$(echo "scale=3; $total_real_nonopt / $runs" | bc)
avg_user_nonopt=$(echo "scale=3; $total_user_nonopt / $runs" | bc)
avg_sys_nonopt=$(echo "scale=3; $total_sys_nonopt / $runs" | bc)

# Print averages for both executables
echo "Average Real, User, Sys Time for opt_out:\nReal: $avg_real_opt seconds\nUser: $avg_user_opt seconds\nSys: $avg_sys_opt seconds\n"

echo "Average Real, User, Sys Time for nonopt_out:\nReal: $avg_real_nonopt seconds\nUser: $avg_user_nonopt seconds\nSys: $avg_sys_nonopt seconds\n"