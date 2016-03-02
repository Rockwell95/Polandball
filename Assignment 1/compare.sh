for d in */;
do
  #.................... FOR ADMIN TESTS .......................................
  for a_file in $d/admin/expected\ output/*;
  do
    echo "====================="
    # echo "$a_file"
    a_file_base="${a_file##*/}"
    # echo "$a_file_base"
    size=$((${#a_file}-4));
    # echo "$size"
    output_t=$(echo $a_file_base | cut -c 1-$size)
    # echo "$output_t"
    out_file="$output_t"_o.txt
    # echo "$out_file"

    DIFF=$(diff $d/admin/expected\ output/$a_file_base $d/admin/actual\ output/$out_file)
    if [[ $DIFF = "" ]]; then
      echo "$a_file_base and $out_file are the same, test passed"
      #statements
    else
      echo "$a_file_base and $out_file are not the same, test failed"
      printf "$a_file_base\n\n$DIFF\n\n=======================\n" >> failedtests.txt
    fi
  done
  #.................... FOR STANDARD TESTS .......................................
  for s_file in $d/standard/expected\ output/*;
  do
    echo "====================="
    # echo "$s_file"
    s_file_base="${s_file##*/}"
    # echo "$s_file_base"
    size=$((${#s_file}-4));
    # echo "$size"
    output_t=$(echo $s_file_base | cut -c 1-$size)
    # echo "$output_t"
    out_file="$output_t"_o.txt
    # echo "$out_file"

    DIFF=$(diff $d/standard/expected\ output/$s_file_base $d/standard/actual\ output/$out_file)
    if [[ $DIFF = "" ]]; then
      echo "$s_file_base and $out_file are the same, test passed"
      #statements
    else
      echo "$s_file_base and $out_file are not the same, test failed"
      printf "$s_file_base\n\n$DIFF\n\n=======================\n" >> failedtests.txt
    fi
  done
done
