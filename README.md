# This project solve keyboard-transform and ssh-hosts probelms. Description of each problem is in docs directory.
Keyboard-transform:

It is C++ project. It has following projects:
- Tranform --> This is static lib
- MyTransform --> This is console problem that using Transform as static lib. This executable is executed by following command:
   MyTranform.exe "Hello" "H" "V" "-1"
 - TestTransform -> This is gtest (google test) unit test case. Just run executable and it will show result of 7 test cases.
 
 It took me 3 hours to do this problem include test cases.
 Complexity for this problem is O(mn) where m is number of commands and n is length of input value.
 
 ssh-hosts:
 
Solution to this problem is in python script. It is under script folder. Following are the commands:

python ssh-host -h hosts.txt -k developer-key.txt

Very basic testing done using CentOS 7. Ran the script on Window remotely ssh to Linux server. I am sure there might be some bugs, but
at least this will provide you an idea of what I am trying to do and how.
