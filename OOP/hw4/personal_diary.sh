#!/bin/bash

# 检查参数数量
if [ $# -lt 1 ]; then
    echo "Usage: $0 <command> [options]"
    echo "Available commands: pdadd, pdlist, pdshow, pdremove"
    exit 1
fi

# 读取日记文件到内存
diary_file="diary.txt"
diary_content=$(cat "$diary_file")

# 根据用户指定的命令调用相应的程序
case "$1" in
    pdadd)
        echo "**********Personal Diary**********"
        echo "Adding a new diary entry..."
        echo "Specific instructions as below"
        echo "**********************************"
        ./pdadd 
        echo "**********************************"
        echo "Checking the diary content after adding..."
        echo "**********************************"
        ./pdlist
        ;;
    pdlist)
        echo "**********Personal Diary**********"
        echo "Enter the date (year month day) to show the diary entry: "
        echo "Enter the begin date (year month day) to show the diary entry: "
        read begin_year begin_month begin_day
        echo "Enter the end date (year month day) to show the diary entry: "
        read end_year end_month end_day
        echo "The above params will be used as the command line parameters to show the diary entry."
        echo "**********************************"
        ./pdlist "$begin_year" "$begin_month" "$begin_day" "$end_year" "$end_month" "$end_day"
        ;;
    pdshow)
        echo "**********Personal Diary**********"
        echo "showing a diary entry..."
        echo "Instructions as below"
        echo "**********************************"
        ./pdshow
        ;;
    pdremove)
        echo "**********Personal Diary**********"
        echo "removing a diary entry..."
        echo "Instructions as below"
        echo "**********************************"
        ./pdremove
        ;;
    *)
        echo "Error: Invalid command specified"
        echo "Available commands: pdadd, pdlist, pdshow, pdremove"
        exit 1
        ;;
esac

exit 0
