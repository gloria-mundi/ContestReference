#!/bin/bash
set -e
cd "$(dirname "$0")"
ulimit -s 4000000
export MALLOC_PERTURB_="$((2#01011001))"
shopt -s lastpipe
export UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1

declare -A cppstandard
cppstandard["string/suffixArray.cpp"]="gnu++20"
cppstandard["other/pbs.cpp"]="gnu++20"
seedmacro=""
compilerflags="-O2"
debugflags="-O2 -fsanitize=address,undefined"

process_awk() {
    awk_file=$(realpath --relative-to="${PWD}" "${1}")
    cpp_file=${awk_file%.awk}
    folder=$(dirname $awk_file)
    #echo "$awk_file"
    mkdir -p "./awk/$folder"
    awk -f "$awk_file" < "../content/$cpp_file" > "./awk/$cpp_file"
}

test_file() {
    file=$(realpath --relative-to="${PWD}" "${1}")
    echo "$file:"

    echo "compiling with sanitizer..."
    std="gnu++17"
    if [[ -v cppstandard[$file] ]]; then
        std=${cppstandard[$file]}
    fi
    g++ -std=$std "$file" -I ./awk/ -I ../content/ $debugflags -Wall -Wextra -Wshadow -Werror -DSANITIZE $seedmacro
    echo "running with sanitizer..."
    timeout --foreground 90s ./a.out
    rm ./a.out

    echo "compiling -O2..."
    std="gnu++17"
    if [[ -v cppstandard[$file] ]]; then
        std=${cppstandard[$file]}
    fi
    g++ -std=$std "$file" -I ./awk/ -I ../content/ $compilerflags -Wall -Wextra -Wshadow -Werror $seedmacro
    echo "running -O2..."
    timeout --foreground 60s ./a.out
    echo ""
    rm ./a.out
}

list_missing() {
    declare -A ignore
    ignore["other/bitOps.cpp"]=1
    ignore["other/pragmas.cpp"]=1
    ignore["other/stuff.cpp"]=1
    ignore["other/timed.cpp"]=1
    ignore["tests/gcc5bug.cpp"]=1
    ignore["tests/precision.cpp"]=1
    ignore["tests/whitespace.cpp"]=1

    total=0
    missing=0

    if [[ ! -v $1 ]]; then
        echo "missing tests:"
    fi
    find ../content/ -type f -name '*.cpp' -print0 | sort -z | while read -d $'\0' file
    do
        total=$((total+1))
        file=${file#../content/}
        if [ ! -f "$file" ] && [[ ! -v ignore["$file"] ]]; then
            missing=$((missing+1))
            if [[ ! -v $1 ]]; then
                echo "  $file"
            fi
        fi
    done
    if [[ -v $1 ]]; then
        covered=$((total-missing))
        coverage=$((100*covered/total))
        echo "REQUIRED=$(( total < 4 ? 0 : total - 4 ))"
        echo "TOTAL=$total"
        echo "COVERED=$covered"
        echo "MISSING=$missing"
    fi
}

coverage() {
    list_missing 1
}

rm -rf ./awk/
find . -type f -path '*.awk' -print0 | sort -z | while read -d $'\0' file
do
    process_awk "$file"
done

if [ "$#" -ne 0 ]; then
    for arg in "$@"
    do
        if [[ $arg == "--awk" ]]; then
            echo "processed all awk files"
        elif [[ $arg == "--missing" ]]; then
            list_missing
        elif [[ $arg == "--coverage" ]]; then
            coverage
        elif [[ $arg == --seed=* ]]; then
            seedmacro="-DSEED=${arg:7}ll"
        elif [[ $arg == "--debug" ]]; then
            debugflags="-g -fsanitize=address,undefined"
        elif [ -d "$arg" ]; then
            dir=$(realpath --relative-to="${PWD}" "$arg")
            find . -type f -path "./${dir}/*.cpp" -not -path './awk/*' -print0 | sort -z | while read -d $'\0' file
            do
                test_file "$file"
            done
        elif [ -f "$arg" ]; then
            test_file "$arg"
        else
            echo "did not recognize: $arg"
            exit 1
        fi
    done
else
    find . -type f -path '*.cpp' -not -path './awk/*' -print0 | sort -z | while read -d $'\0' file
    do
        test_file "$file"
    done
    list_missing
fi

