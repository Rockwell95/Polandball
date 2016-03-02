for d in */;
do
  #.................... FOR ADMIN TESTS .......................................
  for a_file in $d/admin/expected\ output/dummy.txt;
  do
    echo "====================="
    echo "$a_file"
    a_file_base="${a_file##*/}"
    echo "$a_file_base"
    size=$((${#a_file}-4));
    echo "$size"
    output_t=$(echo $a_file_base | cut -c 1-$size)
    echo "$output_t"
    out_file="$output_t"_o.txt
    echo "$out_file"
    
    rm $a_file
    echo "$a_file has been deleted"
  done
  #.................... FOR STANDARD TESTS .......................................
done
