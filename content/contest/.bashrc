alias cmp='g++ -Wall -Wconversion -Wfatal-errors -g \
  -std=gnu++17 -fsanitize=undefined,address'
xmodmap -e 'clear lock' -e 'keycode 66=less greater' #caps = <>

test() {
        cmp $1.cpp -o $1
        for i in $1*.in; do
                echo '===TEST===';
                cat $i;
                echo '===OUT===';
                ./$1 < $i;
                echo; echo;
        done
}

