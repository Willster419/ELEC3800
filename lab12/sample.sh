echo "hello world!"
echo "displaying processes with init"
top -n 1 | grep "init"
cal | sed '1,/19/{s/19/**/g}'

