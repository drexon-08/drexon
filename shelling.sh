#!/bin/bash

DB="student.db"

while true
do
    echo "====================================="
    echo "   STUDENT DATABASE MANAGEMENT"
    echo "====================================="
    echo "1. Create Database"
    echo "2. Insert Record"
    echo "3. Search Record"
    echo "4. Delete Record"
    echo "5. Display Records"
    echo "6. Modify Record"
    echo "7. Exit"

    echo -n "Enter your choice: "
    read ch

    case $ch in

    1)
        touch $DB
        echo "Database Created Successfully."
        ;;

    2)
        echo -n "Enter Roll No: "
        read roll

        if grep -q "^$roll|" $DB 2>/dev/null
        then
            echo "Record already exists."
        else
            echo -n "Enter Name: "
            read name

            echo -n "Enter Class: "
            read class

            echo -n "Enter Marks: "
            read marks

            echo "$roll|$name|$class|$marks" >> $DB
            echo "Record Inserted Successfully."
        fi
        ;;

    3)
        echo -n "Enter Roll No to Search: "
        read roll

        if grep "^$roll|" $DB
        then
            echo "Record Found."
        else
            echo "Record Not Found."
        fi
        ;;

    4)
        echo -n "Enter Roll No to Delete: "
        read roll

        if grep -q "^$roll|" $DB
        then
            grep -v "^$roll|" $DB > temp
            mv temp $DB
            echo "Record Deleted Successfully."
        else
            echo "Record Not Found."
        fi
        ;;

    5)
        echo "-------------------------------------"
        echo "Roll | Name | Class | Marks"
        echo "-------------------------------------"

        if [ -s $DB ]
        then
            cat $DB
        else
            echo "Database Empty."
        fi
        ;;

    6)
        echo -n "Enter Roll No to Modify: "
        read roll

        if grep -q "^$roll|" $DB
        then
            grep -v "^$roll|" $DB > temp

            echo -n "Enter New Name: "
            read name

            echo -n "Enter New Class: "
            read class

            echo -n "Enter New Marks: "
            read marks

            echo "$roll|$name|$class|$marks" >> temp
            mv temp $DB

            echo "Record Modified Successfully."
        else
            echo "Record Not Found."
        fi
        ;;

    7)
        echo "Thank You!"
        exit
        ;;

    *)
        echo "Invalid Choice!"
        ;;
    esac

done